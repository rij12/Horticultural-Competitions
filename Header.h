/* 
 * File:   Header.h
 * Author: Richard Price-Jones 
 * 
 * Created on 03 December 2015, 15:00
 * Contains function Prototypes. 
 */

#define NAME_MAX_LENGTH  60
#define POST_ADDRESS_MAX_LENGTH  80
#define PHONE_NUMBER_MAX_LENGTH  15
#define INCHES_TO_FEET 12
#define MAX_LINE_LENGTH 80

char title_of_competition [MAX_LINE_LENGTH];
char date_of_competition [MAX_LINE_LENGTH];

typedef struct node_bst {
    char name[NAME_MAX_LENGTH];
    char postal_address[POST_ADDRESS_MAX_LENGTH];
    char phone_number[PHONE_NUMBER_MAX_LENGTH];
    int competitor_id;
    float cucumber_length;
    float carrot_length;
    float runner_bean_length;
    struct node_bst * right;
    struct node_bst * left;
} Node;

Node * rootptr = NULL;
void get_input_data();
float convert_to_inchs(int feet, float inches);
void bst_insert(Node** root, Node* new_node);
int get_size(Node* new_node);
int get_feet(float total_inches);
float get_inches(float total_inches);
float get_total(Node *node);

void print_node(Node *node);
void print(Node *node);
/*Task 2*/
void inorder(Node * node, void (*pointer_to_function)(Node*node));
void print_address_menu();
void print_address(Node* node);
void task_two(Node * rootptr);