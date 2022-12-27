#include<stdio.h>
#include<stdlib.h>
#include"header.h"

void design()
{
        for(int i = 0 ; i <30 ; i++)
                printf("*");

        printf("\n");
}


int main()
{
        system("clear");
        seller_Details *seller_root = NULL;
        buyer_Details *buyer_root = NULL;
        product_details *product_root = NULL;

        bidding_details *Bidding_root = NULL;
        bidding_details Bidding_Data = {0};
        int ch;

        design() ;
        printf("Welcome To Auction System\n");
        design() ;

        seller_root  =  file_to_list(seller_root);

        if(seller_root != NULL)
                seller_root->link =  product_registration(product_root);
        buyer_root   =  registration_buyer(buyer_root);


        while(1)
        {
                //system("clear");
                design() ;
                printf("1) Admin\n");
printf("2) Buyer\n");
                printf("3) Seller\n");
                printf("4) Transactions\n");
                printf("5) Exit\n");
                design() ;
                scanf("%d",&ch);

                switch(ch)
                {
                        case 1:
                                admin(seller_root , buyer_root);
                                break;
                        case 2:

                                //printf("rec :: %p\n",Bidding_root);


                                buyer_root = buyer(buyer_root,seller_root,seller_root->link);
                                break;
                        case 3:
                                seller_root = seller(seller_root , product_root);
                        //      printf("seller  %p\n",seller_root->link);
                                break ;
                        case 4:
                                Bidding_root = biding_histroy_extraction_from_file(Bidding_root);
                                display_bidding_price(Bidding_root);
                                saving_tranction_into_file(Bidding_root);
                                break;
                        case 5:
                                exit(0);
                                break ;
                }


        }

}