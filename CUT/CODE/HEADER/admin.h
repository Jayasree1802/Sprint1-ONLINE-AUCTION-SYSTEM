#include<stdio.h>

typedef struct admin_data
{
	
	char user_name[BUFFER_SIZE];
	char pswd[BUFFER_SIZE];
	
	
	struct admin_data *next ;
}admin_data;


void admin(seller_Details *, buyer_Details *);
int admin_login();
admin_data read_admin_file(admin_data );

product_details *add_product_to_list(product_details *);


void block_sller(seller_Details *);
void list_sller();
void block_buyer(buyer_Details *);
void list_buyer();
