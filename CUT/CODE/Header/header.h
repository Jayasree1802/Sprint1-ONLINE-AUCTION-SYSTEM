#include<stdio.h>
#define BUFFER_SIZE 1000

//Defining macros for admin 

#define MANAGE_SELLER 1
#define MANAGE_BUYER 2
#define MANAGE_PRODUCTS 3
#define EXIT 0
#define BLOCK_SELLER 1
#define DISPLAY_SELLER_LIST 2
#define BLOCK_BUYER 1
#define LIST_BUYER 2
#define ADD_PRODUCTS 1
#define REMOVE_PRODUCTS 2
#define MODIFY_PRODUCTS 3


//struct seller_Details to store attributes for entity seller
typedef struct seller_Details
{
        int id;
        char name[30];
        char emailId[50];
        long int phoneNo;
        char panNo[10];
        char password[20];
        int buyer_id_request[10];
        int buyer_request_amount[10];
        char buyer_name[30];
        int count;
        int buyer_id_sell ;
        int status;
        struct product_details *link;
        struct seller_Details *next;
}seller_Details;

//struct product_Details to store attributes for entity product

typedef struct product_details
{
	int product_id ;
	char product_name[20];
	char product_details[30];
	int product_price;
        int seller_id ;
	
	struct product_details *next;
}product_details;

//struct buyer_Details to store attributes for entity buyer

typedef struct buyer_Details
{
        int id;
        char name[30];
        char emailId[50];
        long int phoneNo;
        char panNo[10];
        int product_id[10];
         char password[20];
        int price[10];
    	int count ;
    	int status ;
    	 
        struct buyer_Details *next;
        
}buyer_Details;

//struct admin_data to store attributes for entity admin

typedef struct admin_data
{
	
	char user_name[BUFFER_SIZE];
	char pswd[BUFFER_SIZE];
	
	
	struct admin_data *next ;
}admin_data;

//functions of seller 
seller_Details *  price_check(product_details * ,seller_Details *);
seller_Details *create_lisr_of_seller(seller_Details *,seller_Details);
seller_Details *file_to_list(seller_Details *);
seller_Details seller_extraction_from_file(char * , seller_Details );
void design() ;

//Functions of seller

seller_Details *seller(seller_Details * , product_details *);
seller_Details *login_seller(seller_Details *,char * , char *);
void check_the_buyer_request(seller_Details *);
seller_Details * login(seller_Details *);
int new_registration_to_file();

//functions of product

product_details *product_registration(product_details *);
product_details data_extraction_from_buffer(char * , product_details , int *);
product_details *create_list_for_product(product_details * , product_details);
product_details *delete_product(product_details * ,int);
product_details * modify_product_details(product_details * ,int,seller_Details *);
void display_product(product_details *);
void adding_produt_into_file();
void save_product_info_file(product_details *);
void adding_the_product_into_file(int);
int alpha_validator(char *);
int password_validation(char *);
void history_display();

//functions of buyer

buyer_Details *buyer(buyer_Details * , seller_Details *,product_details *);
buyer_Details *registration_buyer(buyer_Details *);
buyer_Details *buyer_login(buyer_Details *,char * , char *);
void writing_buyer_info_to_file();
buyer_Details data_extraction_from_buyer_file(char * ,buyer_Details);
buyer_Details *create_list_buyer(buyer_Details * , buyer_Details);
void display(seller_Details *);
void auction_for_product(product_details * , seller_Details * , buyer_Details *);
product_details *get_the_product_detail(product_details * ,int);
void display_buyer(buyer_Details *);

//functions of admin menu

void admin(seller_Details *, buyer_Details *);
int admin_login();
admin_data read_admin_file(admin_data );
product_details *add_product_to_list(product_details *);
void block_sller(seller_Details *);
void list_sller();
void block_buyer(buyer_Details *);
void list_buyer();
