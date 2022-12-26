#include<stdio.h>
#include<string.h>
#include"header.h"


/*This Fuction is for Auction of products
*parameter::seller root
*return type:: void
*/
void auction_for_product(product_details *prod_root , seller_Details *seller_root , buyer_Details *buyer_root)
{
	seller_Details *sller_id = NULL;
	int product_amount ; 
	int check_flag = 0;
	char ch ;
	char *transcation = "biding_histry.txt";
	FILE *fptr = NULL ;
	fptr = fopen(transcation,"a+");    // File is opening in read,write mode
	if(fptr == NULL)
	{	
		printf("%s opening is failed\n",transcation);
		return ;
	}
	sller_id = price_check(prod_root , seller_root );  //Function calling
	if((sller_id)!= NULL)
	{
		printf("enter the amount\n");
		scanf("%d",&product_amount);
		if(product_amount >= prod_root->product_price )
		{
		  sller_id->buyer_id_request[sller_id->count] = prod_root->product_id;
		  sller_id->buyer_request_amount[sller_id->count++] = prod_root->product_price ;
		  strcpy(sller_id->buyer_name , prod_root->product_name);
		 fprintf(fptr,"%d,%d,%d,%d,%d\n",buyer_root->id ,prod_root->product_id,sller_id->id,prod_root->product_price ,product_amount); //Writing a data into file
		 fclose(fptr);// File is closed
		}
		else
		{
			while(1)
			{
				sller_id->buyer_id_request[sller_id->count] = prod_root->product_id;
				sller_id->buyer_request_amount[sller_id->count++] = prod_root->product_price ;
				strcpy(sller_id->buyer_name , prod_root->product_name);
				fprintf(fptr,"%d,%d,%d,%d,%d\n",buyer_root->id ,prod_root->product_id,sller_id->id,prod_root->product_price ,product_amount); // writing a data into file
				printf("enter y to continue biding\n");
				printf("enter n to exit the biding\n");
				scanf(" %c",&ch);
				if(ch == 'y' ||ch == 'Y' )
				{
					printf("enter the amount \n");
					scanf("%d",&product_amount);
					if(product_amount >= prod_root->product_price )
					{
					        sller_id->buyer_id_request[sller_id->count] = prod_root->product_id;
						sller_id->buyer_request_amount[sller_id->count++] = prod_root->product_price ;
						strcpy(sller_id->buyer_name , prod_root->product_name);
						fprintf(fptr,"%d,%d,%d,%d,%d\n",buyer_root->id ,prod_root->product_id,sller_id->id,prod_root->product_price ,product_amount);
						fclose(fptr);
						break;
					}
					else
					{
						sller_id->buyer_id_request[sller_id->count] = prod_root->product_id;
						sller_id->buyer_request_amount[sller_id->count++] = prod_root->product_price ;
						strcpy(sller_id->buyer_name , prod_root->product_name);
						fprintf(fptr,"%d,%d,%d,%d,%d\n",buyer_root->id ,prod_root->product_id,sller_id->id,prod_root->product_price ,product_amount);
					}
				}//if ends here
			}//while ends here		
		}//else ends here	
	}//if ends here
}



/*This Fuction is for checking the price of user enterd
*parameter::q
*return type:: seller_Details *q
*/
seller_Details * price_check(product_details *p , seller_Details *q)
{
	product_details *p = seller_root ;
	
	while(p!=NULL)
	{
		if(p->seller_id == q->id)
		{
			return q;
		}
	        p = p->next ;
	}
	return NULL;
}



/*This Fuction is for displaying information
*parameter:: character pointer
*return type:: void as it returns character pointer
*/
void display_info(char *buffer)
{
        int index = 0;
	char *piece ;
	piece = strtok(buffer,",");
	while(piece !=NULL)
	{
	  if(index  == 0)
		{
			printf("buyer-id %s,",piece);
			index =1;	
		}
		else if(index == 1)
		{
			printf("product-id %s,",piece);
			index =2;
		}
		else if(index == 2)
		{
			printf("seller-id %s,",piece);
			index =3;
		}
		else if(index == 3)
		{
			printf("product price %s,",piece);
			index =4;
		}
		else if(index == 4)
		{
			printf("biding price %s\n",piece);
			index = 5;
		}
                piece = strtok(NULL,",");
	}//while ends here
}



/*This Fuction is for displaying History
*parameter::No parameter returns 
*return type:: void as it returns nothing
*/
void history_display()
{
	char *str = "biding_histry.txt";
	char buffer[100];
	int index = 0;
	FILE *fptr = fopen(str ,"r"); // File is opening in read mode
	if(fptr == NULL)
	{
		printf("%s file is not found \n",str);
	}
	else
	{
		while(!feof(fptr))
		{
		   if(!(fgets(buffer,100,fptr)))
			{
				//printf("file is empty\n");
				break ;
			}
			else 
			{	
			display_info(buffer);//function call
			}
		}//while ends here
		fclose(fptr); // file is closed
	}//else ends here
}
