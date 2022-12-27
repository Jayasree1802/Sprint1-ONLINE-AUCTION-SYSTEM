#include<stdio.h>
#include<stdlib.h>
#include"header.h"

// This function is used for getting the design at output
void design()
{
	for(int i = 0 ; i <30 ; i++)
		printf("*");
	printf("\n");
}

// This is the main menu of auction system for to choose by the entered input

int main()
{
        seller_Details *seller_root = NULL;
	buyer_Details *buyer_root = NULL;
	product_details *product_root = NULL;
	int ch;
	design() ;
	printf("Welcome To Auction System\n");
	design() ;
	
	while(1)
	{
		design() ;
		printf("1) Admin\n");
		printf("2) Buyer\n");
		printf("3) Seller\n");
		printf("4) Exit\n");
		design() ;
		scanf("%d",&ch);
		
		switch(ch)
		{
			case ADMIN: 
				if(seller_root != NULL && seller_root->link  != NULL) 
					admin(seller_root , buyer_root);
				else 
					printf("seller and product are not listed\n");
				break;
			case BUYER: 
				if(seller_root != NULL && seller_root->link  != NULL) 
					buyer_root = buyer(buyer_root,seller_root,seller_root->link);
				else 
					printf("seller and product are not listed\n");
				break ;
			case SELLER: 
				seller_root = seller(seller_root , product_root);
				printf("seller  %p\n",seller_root->link);
				break ;
			case EXIT:
				exit(0); 
				break ;
		}
	}	
}
