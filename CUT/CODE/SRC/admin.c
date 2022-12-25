#include<stdio.h>
#include<string.h>
#include"prototype.h"
#include"buyer_prototype.h"
#include"admin_prototype.h"

void admin(seller_Details *seller_root , buyer_Details *buyer_root)
{
	int ch , exit_flag = 0 , p_id = 0 , seller_id = 0 , exit_flag_1 = 0;
	design();
	if(admin_login())
	{
		printf("Well Come To Admin\n");
		design();
		while(1)
		{
			printf("1) Manage seller \n");
			printf("2) Manage buyer\n");
			printf("3) Manage products\n");
			printf("4) Back to main menu\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					printf("1) Block seller\n");
					printf("2) List seller\n");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1: 
							block_sller(seller_root);
							break;
						case 2: 
							display(seller_root);
							break;
					}
					break;
				case 2: 
					printf("1) Block buyer\n");
					printf("2) List buyer\n");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1: 
							block_buyer(buyer_root);
							break;
						case 2: 
							display_buyer(buyer_root);
							break;
					}
					break ;
				case 3: 
					printf("1) Add product \n");
					printf("2) Remove products\n");
					printf("3) modify product\n");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1: 
							printf("seller_root->link %p\n",seller_root->link );
							add_product_to_list(seller_root->link );	
							break ;
						case 2:
							if(seller_root->link != NULL)
							{
								printf("enter the product id\n");
								scanf("%d",&p_id);
								//printf("sending  %p\n",product_root);
								seller_root->link = delete_product(seller_root->link ,p_id );
								save_product_info_file(seller_root->link);
							}
							else
								printf("product list is empty\n");
							break;
						case 3:
							if(seller_root->link != NULL)
							{
								printf("enter the product id\n");
								scanf("%d",&p_id);
								printf("enter seller-id \n");
								seller_root->link = modify_product_details(seller_root->link ,p_id,seller_root);
								save_product_info_file(seller_root->link);
							}
							else
							printf("product list is empty\n");
								break;
					}
					case 4: 
					exit_flag = 1;
					
			}
		if(exit_flag == 1)
			break;	
		}	
			
		
	}	
	
}

int admin_login()
{

	admin_data admin_root ;
	
	int admin_pswd_flag = 0 , count = 0;
	
	char user[BUFFER_SIZE] , password[BUFFER_SIZE];
	
	admin_root = read_admin_file(admin_root);
	while(1)
	{
		while(1)
		{
			printf("enter the usr name \n");
			getchar();
			fgets(user , 20 , stdin);
			user[strlen(user)-1] = '\0';
			if(alpha_validator(user) == 1)
				break;
			else
				printf("please enter only characters\n");
		}
		
		LOOP:
			printf("enter the password\n");
			scanf("%s",password);
			if(password_validation(password) == 1)
			{
				break;
			}
			else
			{
				count ++ ;
				printf("please enter correct format\n");
				goto LOOP;
			}
			
			
		if(strcmp(admin_root.user_name ,user ) == 0)
		{
			if(strcmp(admin_root.pswd ,password ) == 0)
			{
				
				return 1;
			}
		}
		else 
		{
			admin_pswd_flag++;
			printf("please enter correct Password \n");
		}
		
		if(admin_pswd_flag == 3)
		{
			printf("Too many attempts please try again\n");
			return 0;
		}
		
	}
}	

admin_data read_admin_file(admin_data source)
{
	char *str = "admin_info.txt";
	
	FILE *fptr = NULL ;
	char *piece ;
	char buffer[BUFFER_SIZE];
	int index = 1;
	fptr = fopen(str,"r");
	
	if(fptr == NULL)
	{
		printf("%s file opening error\n",str);
	}	
	else 
	{
		while(!feof(fptr))
		{
		
			if(!(fgets(buffer,BUFFER_SIZE,fptr)))
			{
				//printf("string reading is fail\n");
				break ;
			}
			else 
			{
				piece = strtok(buffer,",");
				while(piece !=NULL)
				{
					
					//printf("str :%s\n",piece);
					if(index == 1)
					{
						strcpy(source.user_name ,piece );
						source.user_name[strlen(source.user_name)] = '\0';
						index = 2;	
					}
					else if(index == 2)
					{
						strcpy(source.pswd ,piece );
						source.pswd[strlen(source.pswd)-1] = '\0';
					}
					piece = strtok(NULL,",");
				}
			}	
			
		}
	}
return source ;	
}	
product_details *add_product_to_list(product_details *source)
{
	
		product_details data ;
		char *str  = "product_info.txt";
		FILE *fptr = NULL;
		
		fptr = fopen(str,"a");
		if(fptr == NULL)
		{
			printf("%s file is not found please check\n",str);
			return NULL;
		}
		
		printf("enter the product name\n");
		getchar();
		fgets(data.product_name , 30 , stdin);
		data.product_name[strlen(data.product_name)-1] = '\0';
		
		
		
		printf("enter the product-id \n");
		scanf("%d",&data.product_id);
		
		printf("enter the product details\n");
		getchar();
		fgets(data.product_details , 30 , stdin);
		data.product_details[strlen(data.product_details)-1] = '\0';
		
		printf("enter the product price\n");
		scanf("%d",&data.product_price);
		
		printf("enter end date in format of DD-MM-YYYY\n");
		scanf("%d-%d-%d",&data.end_date[0],&data.end_date[1],&data.end_date[2]);
		
		printf("enter the seller -id\n");
		scanf("%d",&data.seller_id);
		
		
		fprintf(fptr,"%d,%d,%s,%s,%d,%d-%d-%d\n",data.seller_id,data.product_id ,data.product_name,data.product_details,data.product_price,data.end_date[0],data.end_date[1],data.end_date[2]);
		
		fclose(fptr);
		source = create_list_for_product(source , data);
		
	return source ;	
}
void block_sller(seller_Details *source)
{
	seller_Details	*p = source ;
	
	int id ;
	printf("enter the sller id\n");
	scanf("%d",&id);
	
	while(p!= NULL)
	{
		if(p->id == id)
		{
			p->status = 1;
			
			printf("%s,%d is blocked successfully\n",p->name,p->id );
		}
		
		p = p->next ;
	}
}
void block_buyer(buyer_Details *source)
{
	buyer_Details	*p = source ;
	
	int id ;
	printf("enter the buyer id\n");
	scanf("%d",&id);
	
	while(p!= NULL)
	{
		if(p->id == id)
		{
			p->status = 1;
			
			printf("%s,%d is blocked successfully\n",p->name,p->id );
		}
		
		p = p->next ;
	}
}
void list_buyer()
{

}
