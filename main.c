/* 
 * File:   main.c
 * Author: Richard Price-Jones
 * Created on 30 November 2015, 16:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Header.h"

/*Reads in all the information from file, then parses information. */
void get_input_data() {
    FILE *fileptr;
    char file_name [100];
    int feet_tmp;
    float inches_tmp;
    int id = 0;
    
    printf("Enter the file you like to select: ");
    scanf("%s",file_name);
    fileptr = fopen(file_name, "r");
    
      /*Ensure we can read from the file*/
    if (fileptr == NULL) {
        printf("ERROR: Can not open file!\n");
        exit(EXIT_FAILURE);
    }/*File is open successfully*/
    else {
        /*title and date are unique, so outside of the loop */
        fscanf(fileptr, "%[a-zA-Z .]\n", title_of_competition);
       
        fscanf(fileptr, "%[a-zA-Z0-9 .]\n", date_of_competition);
        
                
       do{
           
            Node *new_node = malloc(sizeof (Node));
            
            if (!new_node) {
                printf("ERROR: Memory could not be allocated\n");
                exit(EXIT_FAILURE);
            }

            fscanf(fileptr, "%79[a-zA-Z ]\n", new_node ->name);
            fscanf(fileptr, "%79[a-zA-Z0-9,.- ]\n", new_node ->postal_address);
            fscanf(fileptr, "%79[a-zA-Z0-9 ]\n", new_node ->phone_number);
           
            fscanf(fileptr, "%d %f\n", &feet_tmp, &inches_tmp);
            new_node->cucumber_length = convert_to_inchs(feet_tmp,inches_tmp);
           
            fscanf(fileptr, "%d %f\n", &feet_tmp, &inches_tmp);
            new_node->carrot_length = convert_to_inchs(feet_tmp,inches_tmp);
            
            fscanf(fileptr, "%d %f\n", &feet_tmp, &inches_tmp);
            new_node->runner_bean_length = convert_to_inchs(feet_tmp,inches_tmp);
            
            id++;
            new_node->competitor_id = id;
            
            bst_insert(&rootptr, new_node);
 /* Keeping getting all of the data until you hit the end of the file.*/
        }while (!feof(fileptr));
        
    }
    fclose(fileptr);
}

/* Takes feet and inches of a and converts into just inches. 
     @param int feet
     @param float inches
     @return total_inches
 */
float convert_to_inchs(int feet, float inches) {
    int static FEET_INTO_INCHES = 12;
    float total_inches = feet * FEET_INTO_INCHES;
    return total_inches + inches;
}

/*Understanding of BST tree was drawn from the C in a nut shell, pages 170-181
 *Inserts  a new node into the Binary search tree, which is stored recursively. 
 *@param rootptr - Points to the root of the tree
 *@param new_node - pointer to the new node about to be added to the tree. 
 */
void bst_insert(Node** rootptr, Node* new_node) {
    
    Node *tmp;
    
    /*Ensures when recursive called if the node is empty then create */
    if (*rootptr == NULL) {
        
        tmp = new_node;
        *rootptr = tmp;
    } else {
        /*Here we check if the node that has been inserted is smaller
         *than it's parent node. If it's not smaller
         *than we it must be larger or equal*/
        if (get_size(new_node) < get_size((*rootptr))) {
            bst_insert((&(*rootptr)->left), new_node);
        }else {
            bst_insert((&(*rootptr)->right), new_node);
        }
    }
}

/*This function take two node and compares their total length
 * and the return largest Node. 
 *@param point to the root pointer
 *@prarm pointer to the current node. 
 */
int get_size(Node *new_node) {

    int total_length = new_node->carrot_length + new_node->cucumber_length +
            new_node->runner_bean_length;

    return total_length;
}

/*This function recursively prints, prints out all the node in the BST Tree.
 *@param node - a pointer to the node to be printed.
 */
void print(Node *node) {

    if (node == NULL) {
        return;
    }
    print(node->left);
    print_node(node);
    print(node->right);
}

/*  THis function print the header of the Menu.
 *
 * @parm node - a pointer to the root node, used to print out all the nodes,
 * this is used in part 1. 
 */

void print_menu(Node *node) {

    printf("Competition: %s \t Date: %s \n ", title_of_competition, 
            date_of_competition);
    printf("%-10s", "Name");
    printf("%-19s", "Competitor number");
    printf("%-13s", "Cucumber");
    printf("%-14s", "Carrot");
    printf("%-15s", "Runner Bean");
    printf("%s\n", "Total Length");
    printf("==============================================="
            "=========================================\n");
    /*Used for part one*/        
    //print(node);
}

/* This function prints a node, with the required format.
 * @param node - a point to a node to be printed. 
 */
void print_node(Node *node) {


    printf("%-20s", node->name);
    printf("%-7d", node->competitor_id);
    printf(" %dft in %.1f\t",get_feet(node->cucumber_length),
            get_inches(node->cucumber_length));
    printf(" %dft in %.1f\t",get_feet(node->carrot_length),
            get_inches(node->carrot_length));
    printf(" %dft in %.1f\t",get_feet(node->runner_bean_length),
            get_inches(node->runner_bean_length));
    printf(" %dft in %.1f\n",get_feet(get_total(node)),
            get_inches(get_total(node)));

}

/*@param node -a pointer to node.
 *@return total_sum - combined length of passed pointer node.
 */
float get_total(Node *node) {

    float total_sum = node->carrot_length + node->cucumber_length +
    node->runner_bean_length;

    return total_sum;

}
/*@param node - a pointer to node.
 *@return return_feet - feet of pointer node.  
 */
int get_feet(float total_inches) {

    int return_feet = total_inches / 12;
    return return_feet;
}

/*@param node - a pointer to node.
 *@return return_inches - inches of pointer node.  
 */
float get_inches(float total_inches) {
    int tmp = total_inches / 12;
    total_inches = total_inches - tmp * 12;
    return total_inches;
}

/*Part 2 START*/

/*
 *@param node - a pointer to a node that is to be printed.
 *@param void (*pointer_to_function)(Node *node) - a point to a function,
 *  which takes a point to a node as parameter.   
 */
void inorder(Node * node, void (*pointer_to_function)(Node *node)){
    
    if (node != NULL){
        
        inorder((node)->left,pointer_to_function);
        pointer_to_function(node);
        inorder((node)->right,pointer_to_function);
        
    }
}

void print_address_menu(){

     printf("\nCompetition: %s \t Date: %s \n", title_of_competition, 
            date_of_competition);
     printf("Competitor Contact Details.\n");
   
    }
/*@param node - a pointer to a node, which is used to get the contact information
 * for printing.*/
void print_address(Node* node){
    
    
    printf("\nCompetitor: %s \n", node->name);
    printf("Postal Address: %s\n", node->postal_address);
    printf("Telephone: %s\n", node->phone_number);
}
/*This function controls the functionality for part 2 of the assignment
 *this is removed from part one.
 * Prints out Task 2.
 *@param rootptr - a pointer to the root of the BST. 
 */
void task_two(Node * rootptr){
    
   print_menu(rootptr);
   inorder(rootptr,print_node);
    
   print_address_menu();
   inorder(rootptr,print_address);

}
/* END Part 2 */

int main(int argc, char** argv) {
    get_input_data();
    /*PART 1 */
   // print_menu(rootptr);
    /*PART 2 */
    task_two(rootptr);
    
    return (EXIT_SUCCESS);
}