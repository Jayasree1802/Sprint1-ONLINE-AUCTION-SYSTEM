#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"header.h"

int ans_check()
{
        char ch ;
        loop:
        printf("enter y to continue biding\n");
        printf("enter n to exit the biding\n");
        scanf(" %c",&ch);
        if(ch == 'y' ||ch == 'Y' )
        {
                return 1;
        }
        else if(ch == 'n' ||ch == 'N')
                return 0;
        else
        {
                printf("please enter correct format\n");
                goto loop;
        }

}
void auction_for_product(product_details *prod_root , seller_Details *seller_root , buyer_Details *buyer_root)
{
        seller_Details *sller_id = NULL;
        int product_amount = 0 , count =0 ;
        int check_flag = 0;
        char ch ;
        char *transcation = "biding_histry.txt";

        FILE *fptr = NULL ;

        fptr = fopen(transcation,"a+");
        if(fptr == NULL)
        {
                printf("%s opening is failed\n",transcation);
                return ;
}

        printf("------------WellCome to Auction ----------\n");

        printf("\n");

        printf("Product price %d\n",prod_root->product_price);

        while(1)
        {
                if(count <= 10)
                {
                        if(check_flag == 0)
                        {
                                printf("enter the amount\n");
                                scanf("%d",&product_amount);
                                count++;
                        }
                        else
                        {
                                if(ans_check())
                                {
                                        printf("enter the amount\n");
                                        scanf("%d",&product_amount);
                                        count++;
                                }
                                else
                                {
                                        fclose(fptr);
                                        return;
                                }
                        }

                        if(product_amount >= prod_root->product_price )
                        {
                                if(check_flag == 0)
                                {
                                        fprintf(fptr,"%d,%d,%d,%d,%d,",buyer_root->id ,prod_root->product_id,seller_root->id,prod_root->product_price ,product_amount);
                                        check_flag = 1 ;
                                }
else
                                {
                                        fprintf(fptr,"%d,",product_amount);
                                }
                        }
                        else
                        {
                                printf("Prdoucr Base Price is %d \n",prod_root->product_price);
                                printf("Please enter amount greater than the base price\n");
                        }

                }
                else
                {
                        printf("maximus auction limit is done \n");
                        printf("THANK YOU\n");
                }

        }

}


seller_Details * price_check(product_details *p , seller_Details *q)
{
        int count =0 ;
        seller_Details *find_best[10];
        int index = 0;

        while(q!=NULL)
        {
                printf("Sellers are %d and product %d \n",q->id, p->seller_id);
                if(index <= 10)
                {
                        if(p->seller_id == q->id)
                        {
                                printf("test product seller :%d  and searching seller id %d\n",p->seller_id ,q->id );
                                find_best[index++] =  q;
count++;
                        }

                        q = q->next ;
                }
                else
                        break;
        }


        return NULL;
}
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
        }
}
void history_display()
{
        char *str = "biding_histry.txt";

        char buffer[100];
        int index = 0;
        FILE *fptr = fopen(str ,"r");

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
                                //printf("str : %s\n",buffer);
                                display_info(buffer);


                        }
                }
fclose(fptr);
        }

}


bidding_details *biding_histroy_extraction_from_file(bidding_details *Bidding_root)
{


        char *str = "biding_histry.txt";
        char buffer[100];
        int index = 0 , count = 0;
        bidding_details Bidding_Data =  {0};
        char *piece ;

        FILE *fptr = fopen(str ,"r");

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
                                count = 0;

                                if(count <= 15)
                                {
                                        piece = strtok(buffer,",");
while(piece !=NULL)
                                        {

                                                piece[strlen(piece)] = '\0';

                                                Bidding_Data.bidding_data[count] = atoi(piece);
                                                //printf("data : %d\n",Bidding_Data.bidding_data[count]);

                                                piece = strtok(NULL,",");

                                                count++ ;
                                        }
                                }
                                else
                                        break;
                        }

                        Bidding_Data.bidding_data[15] = count ;

                                for(int i = 0 ; i < 5 ;i++)
                                        Bidding_Data.result[i] = Bidding_Data.bidding_data[i];

                                        Bidding_Data.result[4] = finding_the_largest_bidding_price(Bidding_Data);
                                //printf("biggest number is %d\n",Bidding_Data.result[4] = finding_the_largest_bidding_price(Bidding_Data));
                                if(Bidding_root != NULL)
                                        Bidding_root = check_for_best_price_by_buyer(Bidding_root,Bidding_Data );
                                else
                                        Bidding_root = create_bidding_list(Bidding_root , Bidding_Data);


                                //printf("biding :: address %p \n",Bidding_root);
                }
     }

//printf("sending bidding :: address %p \n",Bidding_root);

     return Bidding_root;
}


int  finding_the_largest_bidding_price(bidding_details Bidding_Data)
{

        int large =  0;

        for(int i = 4 ; i < Bidding_Data.bidding_data[15] ; i++)
        {
                if(large < Bidding_Data.bidding_data[i] )
                        large = Bidding_Data.bidding_data[i] ;
                else
                        continue;
        }

        return large ;

}

bidding_details *create_bidding_list(bidding_details *source ,  bidding_details Bidding_Data)
{

        if(source == NULL)
        {
                source = (bidding_details *) calloc(1,sizeof(bidding_details));

                  for(int i  = 0 ; i < 5 ; i++)
                        source->result[i] = Bidding_Data.result[i];

                source->next = NULL;
        }
        else
        {
                bidding_details *p = source ;
                bidding_details *temp = (bidding_details *) calloc(1,sizeof(bidding_details));


                  for(int i  = 0 ; i < 5 ; i++)
                        temp->result[i] = Bidding_Data.result[i];

                while(p->next != NULL)
{
                        p = p->next ;

                 }

                p->next = temp ;
                temp->next = NULL ;

        }

        return source ;
}

void display_bidding_price(bidding_details *p)
{

                //printf("display receoved address is %p\n",p);
                while(p!=NULL)
                {
                        printf("Buyer-id::%d,Product-id ::%d,Seller-id::%d,base price::%d best price %d\n",p->result[0],p->result[1],p->result[2],p->result[3] , p->result[4]);
                        p = p->next;
                }
}


bidding_details *check_for_best_price_by_buyer(bidding_details *source  , bidding_details Data)
{
        bidding_details *p = source ;

                int check_flag = 0;
                while(p!=NULL)
                {
                        if(p->result[1] == Data.result[1] && p->result[0] == Data.result[0] )
                        {
                                check_flag  = 1;
                                if(p->result[4]  < Data.result[4])
                                p->result[4] = Data.result[4];
                        }

p=p->next;
                }


                if(check_flag == 0)
                        return create_bidding_list(source ,Data );
                else
                        return source ;

}

void saving_tranction_into_file(bidding_details *bidding_root )
{
        bidding_details *p = bidding_root ;

        char *info[5] = {"Buyer-ID","Product-Id","Seller-ID" ,"Base-Price","Bidding-Price"};
        char *str = "tranction_history.txt";
        char ch = '-';
        FILE *fptr = fopen(str , "a");
        if(fptr == NULL)
        {
                printf("%s file is not open\n",str);
        }
        else
        {       while(p!= NULL)
                {
                        fprintf(fptr,"%s%c%d,%s%c%d,%s%c%d,%s%c%d.%s%c%d\n",info[0],ch,p->result[0],info[1],ch,p->result[1],info[2],ch,p->result[2],info[2],ch,p->result[3],info[4],ch,p->result[4]);
                        p=p->next;
                }

                fclose(fptr);
        }
}







