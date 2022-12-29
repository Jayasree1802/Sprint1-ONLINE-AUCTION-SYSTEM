//header file
#include<stdio.h>

//macros for admin menu

#define MANAGE_SELLER 1
#define MANAGE_BUYER 2
#define MANAGE_PRODUCTS 3
#define BLOCK_SELLER 1
#define BLOCK_BUYER  1
#define LIST_SELLER  2
#define LIST_BUYER   2
#define ADD_PRODUCTS  1
#define REMOVE_PRODUCTS 2
#define MODIFY_PRODUCTS 3
#define EXIT 0

//structure of admin data

typedef struct admin_data
{
	char user_name[BUFFER_SIZE];
	char pswd[BUFFER_SIZE];
	struct admin_data *next ;
	
}admin_data;

//functions for admin

void admin(seller_Details *, buyer_Details *);
int admin_login();
admin_data read_admin_file(admin_data );
product_details *add_product_to_list(product_details *);
void block_sller(seller_Details *);
void list_sller();
void block_buyer(buyer_Details *);
void list_buyer();
