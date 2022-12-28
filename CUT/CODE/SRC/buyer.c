//definition file of buyer
#include"header.h"
#include<unistd.h>
#include<stdlib.h>




/*******************************************************************************************
**
**  FUNCTION NAME   : save_to_file
**  DESCRIPTION     : In this function it stores the data of the buyer in a file
**  RETURN          :  No Return 
**  PARAMETERS      : Structure buyer_Details variable Source
*******************************************************************************************/
void save_to_file(buyer_Details *source)
{
        FILE *fptr = NULL ;
        char *buyer_file = "buyer_Details.txt" ;
        buyer_Details *p = source ;

        fptr = fopen(buyer_file,"w");
        if(fptr == NULL)
        {
                printf("file open error\n");
        }
        else
        {
                while(p!=NULL)
                {
                        for(int i = 0 ; i < p->count ; i++)
                                fprintf(fptr,"%d,%s,%s,%ld,%s,%s,%d,%d\n",p->id,p->name,p->emailId ,p->phoneNo , p->panNo,p->password ,p->product_id[i] ,p->price[i] );

                        p = p->next;
                }
        }

        fclose(fptr);
}



/*******************************************************************************************
**
**  FUNCTION NAME   : display_buyer
**  DESCRIPTION     : In this function the buyer details are displayed
**  RETURN          :  No Return 
**  PARAMETERS      : Structure buyer_Details variable Source
*******************************************************************************************/
void display_buyer(buyer_Details *source)
{
        buyer_Details *p = source  ;
        int ch ;
        printf("1) For Availabel Buyer's\n");
    //  printf("2) Blocked Buye's");
        scanf("%d",&ch);
        if(ch == 1)
        {
                while(p!=NULL)
                {
              
                        if(p->status != 1)
                                printf("%d,%s,%s,%ld,%s,%s\n",p->id,p->name,p->emailId ,p->phoneNo , p->panNo,p->password );
                        p = p->next;
                }
        }
        else if(ch == 2)
        {
                while(p!=NULL)
                {
                        if(p->status == 1)
                                printf("%d,%s,%s,%ld,%s,%s\n",p->id,p->name,p->emailId ,p->phoneNo , p->panNo,p->password );
                        p = p->next;
                }
        }
}



/*******************************************************************************************
**
**  FUNCTION NAME   : display_productlis
**  DESCRIPTION     : In this function the products that are displayed to buyer to buy
**  RETURN          :  No Return 
**  PARAMETERS      : Structure product_Details with structure variable Seller_root
*******************************************************************************************/
void display_productlis(product_details *seller_root)
{
        product_details *p = seller_root ;

        while(p!= NULL)
        {

                        printf("%d,%d,%s,%s,%d,%d-%d-%d\n",p->seller_id,p->product_id ,p->product_name,p->product_details,p->product_price,p->end_date[0],p->end_date[1],p->end_date[2]);

                        p = p->next;
        }

}



/*******************************************************************************************
**
**  FUNCTION NAME   : buyer
**  DESCRIPTION     : In this function it is the menu for the buyer module
**  RETURN          :  Return source
**  PARAMETERS      : Structure buyer_Details variable Source,Structure seller_Details with variable seller_root, structure product_details with variable product root 
*******************************************************************************************/
buyer_Details *buyer(buyer_Details *source , seller_Details *seller_root , product_details *product_root)
{
        system("clear");
        int ch , exit_flag = 0 , prod_id = 0 , num = 0;
        char buyer_name[30] , buyer_pswd[30] ,choice;
        buyer_Details *buyer_id = NULL ;
        seller_Details *sller_id  = NULL ;
design() ;
        printf("well come to buyer\n");
        design() ;
        if(seller_root == NULL)
        {
                printf("No sellers are avialable\n");
                return NULL;

        }
        while(1)
        {
                design() ;
                printf("1) Registration\n");
                printf("2) Login\n");
                printf("3) Disply \n");
                printf("4) Biding history\n");
                printf("5) exit\n");
                design() ;
                if(source==NULL)
                        source = registration_buyer(source);
                scanf("%d",&ch);

                switch(ch)
                {
                        case 1:
                                writing_buyer_info_to_file();
                                source=NULL;
                                source = registration_buyer(source);
                                break ;

                        case 2:
                                printf("enter the name \n");
                                getchar();
                                fgets(buyer_name, 30 , stdin);
                                buyer_name[strlen(buyer_name)-1] = '\0';
                                printf("enter the password \n");
                                //scanf("%s",buyer_pswd);
                                strcpy(buyer_pswd,getpass("enter password: "));
                                if((buyer_id = buyer_login(source,buyer_name,buyer_pswd)) != NULL)
                                {
                                        printf("%s is loged in succsfully\n",buyer_id->name);
                                        design() ;

                                        printf("enter y to see the avilable products\n");
                                        scanf(" %c",&choice);
                                        if(choice == 'y' || choice == 'Y')
                                        {
                                                display_productlis(product_root);

                                                printf("enter y to buy a product\n");
                                                scanf(" %c",&choice);

                                                if(choice == 'y' || choice == 'Y')
                                                {
                                                        printf("plese select the product-id\n");
                                                        scanf("%d",&prod_id);

                                                        prod_details = get_the_product_detail(product_root ,prod_id);
                                                        sller_id = get_the_seller_dwtails_for_product(prod_details ,prod_id , seller_root);

                                                        if(prod_details == NULL)
                                                        {
                                                                printf("product-id is not found\n");
                                                        }
                                                        else
                                                        {
                                                                //printf("product %s\n",prod_details->product_name);
                                                                auction_for_product(prod_details ,sller_id , buyer_id );
                                                        }
                                                }
                                                else
                                                        printf("Thank you\n");
                                        }

                                }
                                else
                                {
                                 printf("%s buyer is not found\n",buyer_name);
                                }
                                break ;
                        case 3:
                                display_buyer(source);
                                break;
                        case 4:
                                history_display();
                                break;
                        case 5:
                                exit_flag = 1;
                                break;
                }

                if(exit_flag == 1)
                        break;
        }
return source ;
}



/*******************************************************************************************
**
**  FUNCTION NAME   : registration_buyer
**  DESCRIPTION     : It is the function for the registration of buyer  
**  RETURN          :  Return source
**  PARAMETERS      : Structure buyer_Details variable Source
*******************************************************************************************/
buyer_Details *registration_buyer(buyer_Details *source)
{

        char *str = "buyer_info.txt" ;
        char buffer[BUFFER_SIZE];
        FILE *fptr = NULL ;
        buyer_Details buyer_data;

        fptr = fopen(str,"r");

        if(fptr == NULL)
        {
                printf("file opening is failed\n");
                return NULL;
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
                                        buyer_data = data_extraction_from_buyer_file(buffer , buyer_data);
                                                source = create_list_buyer(source , buyer_data);
                        }
                }
        }
return source;
}



/*******************************************************************************************
**
**  FUNCTION NAME   : buyer_login
**  DESCRIPTION     : It is the function for buyer login into the application
**  RETURN          : No Return 
**  PARAMETERS      : Structure buyer_Details variable Source, username and password
*******************************************************************************************/
buyer_Details *buyer_login(buyer_Details *source,char *user_name , char *pswd)
{
        buyer_Details *p = source ;

        if(source == NULL)
        {
                printf("buyer list is empty \n");
                return NULL;
        }
        int flag = 0 ;
        while(p != NULL)
        {
                if(strcmp(p->name ,user_name) == 0 )
                {
                        if(strcmp(p->password , pswd )== 0)
                        {
                                flag = 1;
                                if(p->status == 1)
                                {
                                        printf("%s and %d is blokced\n",user_name ,p->id);
                                        return NULL;

                                }
return p ;
                        }

                }

                p = p->next ;
        }

        if(flag == 0)
         return NULL ;
}



/*******************************************************************************************
**
**  FUNCTION NAME   : writing_buyer_info_to_file
**  DESCRIPTION     : In this function it writes the data of the buyer into a file
**  RETURN          :  No Return 
**  PARAMETERS      : No parameters
*******************************************************************************************/
void writing_buyer_info_to_file()
{
        char *str = "buyer_info.txt" ;

        FILE *fptr = NULL ;
        buyer_Details source ;

        fptr = fopen(str,"a");

        if(fptr == NULL)
        {
                printf("file opening is failed\n");
                return ;
        }
        else
        {
                printf("enter the name\n");
                getchar();
        //      fgets(source.name , 10 , stdin);
                scanf("%[^\n]",source.name);
                source.name[strlen(source.name)]= '\0';

                printf("enter the buyer-id\n");
                scanf("%d",&source.id);
        //      printf("source.id%d\n",source.id );
printf("enter the email-id\n");
                getchar();
                fgets(source.emailId , 20 , stdin);
                source.emailId[strlen(source.emailId)] = '\0';

                printf("enter the password\n");
                getchar();
                scanf("%s",source.password);
                printf("enter the phone number\n");
                scanf("%ld",&source.phoneNo);

                printf("enter the pan card number\n");
                getchar();
                fgets(source.panNo , 10 , stdin);
                source.panNo[strlen(source.panNo)-1] = '\0';

                fprintf(fptr,"%d,%s,%ld,%s,%s,%s\n",source.id,source.name,source.phoneNo,source.panNo,source.emailId,source.password);
        }

        fclose(fptr);
}



/*******************************************************************************************
**
**  FUNCTION NAME   : data_extraction_from_buyer_file
**  DESCRIPTION     : In this function it extracts the data of the buyer from  file
**  RETURN          :  Return DATA 
**  PARAMETERS      : char string for the buffer and Structure buyer_Details with variable DATA
*******************************************************************************************/
buyer_Details data_extraction_from_buyer_file(char *str ,buyer_Details DATA)
{

        //printf("str :%s\n",str);

        int index = 0;
        char *piece = NULL;
                piece = strtok(str,",");
                while(piece !=NULL)
                {
                        //printf("%s\n",piece);
                        if(index == 0)
                        {
                        //      printf("%s str\n",piece);

                                DATA.id = atoi(piece);
                        //      printf("%d int\n",DATA.id);
                                index =1;
}
                        else if(index == 1)
                        {
                        //      printf("%s str1\n",piece);
                                strcpy(DATA.name ,piece);
                        //      printf("%s str1\n",DATA.name);
                                DATA.name[strlen(DATA.name)] = '\0';
                        //       printf("%s str2\n",DATA.name);
                                index =2;
                        }
                        else if(index == 2)
                        {
                                piece[strlen(piece)]='\0';
                                DATA.phoneNo = atoi(piece);
                        //      printf("%ld phoneno\n",DATA.phoneNo);
                                index =3;
                        }
                        else if(index == 3)
                        {
                                strcpy(DATA.panNo ,piece);
                                DATA.name[strlen(DATA.panNo)-1] = '\0';
                                index = 4;
                        }
                        else if(index == 4)
                        {
                                strcpy(DATA.emailId ,piece);
                                DATA.name[strlen(DATA.emailId)] = '\0';
                                index = 5;
                        }
                        else if(index == 5)
                        {
                                strcpy(DATA.password ,piece);
                                DATA.password[strlen(DATA.password)-1] = '\0';

                        }
                        piece = strtok(NULL,",");
                }
return DATA;
}



/*******************************************************************************************
**
**  FUNCTION NAME   : create_list_buyer
**  DESCRIPTION     : In this function it creates a linked list to the buyer
**  RETURN          : Return source 
**  PARAMETERS      : Structure buyer_Details with variable source and DATA
*******************************************************************************************/
buyer_Details *create_list_buyer(buyer_Details *source , buyer_Details DATA)
{
        if(source == NULL)
        {
                source  = (buyer_Details *)malloc(sizeof(buyer_Details));
                source->id = DATA.id;
        //      printf("%s str6\n",DATA.name);
                strcpy(source->name ,DATA.name);
        //      printf("%s str3\n",source->name);
                source->phoneNo = DATA.phoneNo ;
                strcpy(source->panNo ,DATA.panNo);
                strcpy(source->emailId ,DATA.emailId);
                strcpy(source->password ,DATA.password );
                source->next = NULL;
        }
        else
        {
                buyer_Details *p = source ;
                buyer_Details *temp = (buyer_Details *) malloc(sizeof(buyer_Details));

                temp->id = DATA.id;
        //       printf("%s str5\n",DATA.name);
                strcpy(temp->name ,DATA.name);
        //      printf("%s str4\n",temp->name);
                temp->phoneNo = DATA.phoneNo ;
                strcpy(temp->panNo ,DATA.panNo);
                strcpy(temp->emailId ,DATA.emailId);
                strcpy(temp->password ,DATA.password );

                while(p->next != NULL)
                 {
                        p = p->next ;
                 }

                p->next = temp ;
                temp->next = NULL ;
        }

return source;
}



/*******************************************************************************************
**
**  FUNCTION NAME   : get_the_product_detail
**  DESCRIPTION     : In this function it display the data of the products to the buyer
**  RETURN          :  No Return 
**  PARAMETERS      : Structure product_details variable p and prod_id
*******************************************************************************************/
product_details *get_the_product_detail(product_details * p ,int prod_id)
{

                if(p==NULL)
                {
                        printf("product list is empty\n");
                        return NULL;
                }

                while(p!=NULL)
                {

                        //printf("p->product_id %d and prod_id %d \n",p->product_id ,prod_id );
                                if(p->product_id == prod_id)
                                {
                                        //printf("product id %d",p->product_id);
                                        return p;
                                }


                        p = p->next;
                }
                return NULL;
}




seller_Details *get_the_seller_details_for_product(product_details *p ,int product_id , seller_Details *q)
{

                int check_flag = 0;
                int seller_id ;

                printf("avilable sellers are shown below \n");
                while(p!=NULL)
                {
                        if(p->product_id == product_id)
                        {
                                check_flag = 1;
                                printf("seller-id%d and product cost %d\n",p->seller_id , p->product_price);
                        }

                        p = p->next;
                }

                if(check_flag == 1)
                {
                        printf("selecct the seller id \n");
                        scanf("%d",&seller_id);

                        while(q!=NULL)
                        {
                                if(q->id == seller_id)
                                {
                                        printf("you are selected %d and %s seller\n",q->id,q->name);

                                        return q;
                                }
                                q=q->next;
                        }
                }
}


        


