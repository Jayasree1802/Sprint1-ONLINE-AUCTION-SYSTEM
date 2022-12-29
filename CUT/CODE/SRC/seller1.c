#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"header.h"

void display(seller_Details *seller_root)
{
        int ch ;
        printf("1) For Available Seller's\n");
//      printf("2) FOr Blocked seller's\n");
        scanf("%d",&ch);
        if(ch == 1)
        {
                while(seller_root !=NULL)
                {
                        if(seller_root->status != 1)
                        printf("%s,%d,%ld,%s,%s,%s\n",seller_root->name,seller_root->id ,seller_root->phoneNo ,seller_root->emailId ,seller_root->panNo,seller_root->password);


                        seller_root = seller_root->next;
                }
        }
        else if(ch == 2)
        {
                while(seller_root!=NULL)
                {
                        if(seller_root->status == 1)
                        printf("%s,%d,%ld,%s,%s,%s\n",seller_root->name,seller_root->id ,seller_root->phoneNo ,seller_root->emailId ,seller_root->panNo,seller_root->password);


                        //printf("seller-id::%d\n",seller_root->status);

                        seller_root = seller_root->next;
                }
        }
}

seller_Details * login(seller_Details *seller_root )
{
        char seller_name[20] , seller_pswd[20] ;
        printf("enter the name: \n");
        while(getchar()!='\n');
         fgets(seller_name,20,stdin);
          seller_name[strlen(seller_name)-1]='\0';

         printf("enter the password: \n");
         strcpy(seller_pswd,getpass("enter password: "));

         if((seller_root = login_seller(seller_root ,seller_name,seller_pswd ))
         {
                printf("%s is loged in succsfully\n",seller_name);
                return seller_root;
                //check_the_buyer_request(seller_id);
        }
        else
        {
                printf("%s seller is not found\n",seller_name);
                return NULL;
        }
}
void save_product_info_file(product_details *product_root)
{
        product_details *p = product_root  ;

        FILE *fptr = NULL;
        char *str = "product_info.txt";
        fptr = fopen(str,"w");

        if(fptr == NULL)
        {
                printf("%s is opened to fail\n",str);
                return ;
        }

        while(p!=NULL)
        {
                fprintf(fptr,"%d,%d,%s,%s,%d,%d-%d-%d\n",p->seller_id,p->product_id,p->product_name,p->product_details ,p->product_price,p->end_date[0],p->end_date[1],p->end_date[2]);
                p = p->next;
        }

        fclose(fptr);
}

product_details *get_prodouct_seller_id(product_details *p , int seller_id)
{

                if(p==NULL)
                {
                        printf("product list is empty\n");
                        return NULL;
                }

                char ch ;

                while(p!=NULL)
                {
                        printf("seller id is %d constant %d \n",p->seller_id , seller_id);
                        if(p->seller_id == seller_id)
                        {
                                //printf("seller id is %d\n",p->seller_id);
//printf("address %p\n",p);
                                return p;
                        }

                        p = p->next;
                        getchar();
                }

                return NULL;
}


seller_Details *seller(seller_Details *seller_root, product_details *product_root)
{
        system("clear");

        int ch  , seller_exit_flag = 0 , exit_flag = 0 , p_id = 0 , exit_flag_1 = 0;

        seller_Details *seller_id = NULL;

        char int_reading[20];
        design() ;
        printf("WELCOME TO SELLER\n");
        design() ;
        seller_root = file_to_list(seller_root);
        if(seller_root != NULL)
        {
                product_root = product_registration(product_root) ;
                seller_root->link = product_root;

        }

        while(1)
        {

                design() ;
                printf("1) New Registration \n");
                printf("2) For Login\n");
                printf("3) Display\n");
                printf("4) exit\n");
                design() ;
                //scanf("%d",&ch);
                ch = int_ans_choice(1,4);
                switch(ch)
                {
                        case REGISTRATION:
                                new_registration_to_file();
                                seller_root=NULL;
                                seller_root = file_to_list(seller_root);
                                break;
                        case LOGIN:
                                seller_id = login(seller_root) ;
                                if(seller_id !=NULL)
                                {
                                        while(1)
                                        {
                                                printf("1) Product Registration\n");
                                                printf("2) Delete Prdouct\n");
                                                printf("3  modify product details\n");
                                                printf("4) Display\n");
                                                printf("5  Biding History \n");
                                                printf("6) exit\n")
                                                ch = int_ans_choice(1,6);
                                                switch(ch)
                                                {
                                                        case PRODUCT_REGISTRATION:
                                                                adding_the_product_into_file(seller_id->id);
                                                                product_root = NULL;
                                                                product_root = product_registration(product_root) ;
                                                                seller_root->link = product_root;
                                                                break;
                                                        case DELETE_PRODUCTS:
                                                                printf("enter the product id\n");
                                                                p_id = int_id_validation();
                                                                product_root = delete_product(product_root ,p_id );
                                                                save_product_info_file(product_root);
                                                                seller_id->link = product_root ;
                                                                break;
                                                        case MODIFY_PRODUCTS:
                                                                printf("enter the product id\n");
                                                                p_id = int_id_validation();
                                                                product_root = modify_product_details(product_root ,p_id,seller_id);
                                                                save_product_info_file(product_root);
                                                                seller_id->link = get_prodouct_seller_id(product_root , seller_id->id);
                                                                break;
                                                        case DISPLAY_PRODUCTS: display_product(product_root);
                                                                break ;
                                                        case BIDDING_HISTORY:
                                                                history_display();
                                                        break;
                                                        case 6:
                                                                exit_flag_1 = 1;
                                                                break;

                                                }

                                                if(exit_flag_1 == 1)
                                                        break;
                                        }
                                }
                                break;
                        case DISPLAY SELLER_DETAILS:
                                display(seller_root);
                                break;
                        case 4:
                                exit_flag = 1;
                                break;
                }
        if(exit_flag == 1)
                break;
}
return seller_root;
}


seller_Details *create_lisr_of_seller(seller_Details *source_1 , seller_Details DATA)
{

        static seller_Details *source;
        source = source_1 ;
        if(source == NULL)
        {
                source = (seller_Details *) calloc(1,sizeof(seller_Details));

                   strcpy(source->name , DATA.name);
                   source->id = DATA.id;
                   source->phoneNo = DATA.phoneNo;
                   strcpy(source->emailId , DATA.emailId);
                   strcpy(source->panNo , DATA.panNo);
                   strcpy(source->password , DATA.password);
                source->next = NULL;
        }
        else
        {
                seller_Details *p = source ;
                seller_Details *temp = (seller_Details *) calloc(1,sizeof(seller_Details));

                   strcpy(temp->name , DATA.name);
                   temp->id = DATA.id;
                   temp->phoneNo = DATA.phoneNo;
                   strcpy(temp->emailId , DATA.emailId);
                   strcpy(temp->panNo , DATA.panNo);
                   strcpy(temp->password , DATA.password);

                while(p->next != NULL)
                 {
                        p = p->next ;

                 }

                p->next = temp ;
                temp->next = NULL ;

        }

        return source ;
}


seller_Details *login_seller(seller_Details *seller_root,char *user_name , char *pswd)
{
        seller_Details *p = seller_root ;
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


void check_the_buyer_request(seller_Details *seller)
{

        FILE *fptr = NULL;
        char *seller_file = "selling_info.txt";

        printf("checking\n");
        if(seller==NULL)
        {
                printf("list is empty\n");
                return ;
        }

        seller_Details *p = seller ;

        for(int i = 0 ; i< p->count ; i++)
        {
                printf("product id :%d product name %s asking price %d and buyer id %d\n",p->product_id , p->product_name , p->buyer_request_amount[i],p->buyer_id_request[i]);
        }
        printf("entert buyer id you want to sell \n");
        scanf("%d",&p->buyer_id_sell);
        p->product_status = 2;
        printf("%s is sold to buyer - id %d\n",p->name ,p->buyer_id_sell );

        fptr = fopen(seller_file,"a");
        if(fptr ==NULL)
        {
                printf("file open is failed\n");
                return ;
        }
        else
        {
                for(int i = 0 ; i< p->count ; i++)
                {
                        if(p->buyer_id_sell == p->buyer_id_request[i])
                        {
                                fprintf(fptr,"%d,%s,%d,%s,%d\n",p->product_id  ,p->product_name,p->buyer_id_request[i],p->buyer_name ,p->buyer_request_amount[i]);
                        }

                }
        }

        fclose(fptr);

}
int new_registration_to_file()
{
        seller_Details seller_data ;

        FILE *fptr = NULL;
        char *seller_file = "seller_info.txt";
        fptr =fopen(seller_file ,"a");
        if(fptr == NULL)
        {
                printf("%s file is not found\n",seller_file);

        }
        else
        {


                printf("enter the name\n");
                while(1)
                {
                        getchar();
                        fgets(seller_data.name , 30 , stdin);
                        seller_data.name[strlen(seller_data.name)-1] = '\0';

                        if(alpha_validator(seller_data.name))
                                break;
                        else
                                printf("Username,must contain characters only\n");
                }

                printf("name::%s\n",seller_data.name);

                printf("enter the seller-id\n");
                //getchar();
                //scanf("%d",&seller_data.id);
                seller_data.id = int_id_validation(seller_data.id);

                printf("enter the email-id\n");
                while(1)
                {
                        getchar();
                        fgets(seller_data.emailId , 50 , stdin);
                        seller_data.emailId[strlen(seller_data.emailId)-1] = '\0';
                       if(Emai_validation(seller_data.emailId))
                             break;
                       else
                           printf("Please Enter Correct Email-id\n");
                }

//              printf("enter the password\n");
                while(1)
                {
                //      scanf("%s",seller_data.password);
                        strcpy(seller_data.password,getpass("enter password: "));
                        seller_data.password[strlen(seller_data.password)-1] = '\0';
                        if(password_validation(seller_data.password))
                                break;
                        else
                                printf("enter correct password\n");
                }
             //   printf("password is %s\n",seller_data.password);

                printf("enter the phone number\n");
                scanf("%ld",&seller_data.phoneNo);

                printf("enter the pan card number\n");
                while(1)
                {
                        getchar();
                        fgets(seller_data.panNo , 10 , stdin);
                        seller_data.panNo[strlen(seller_data.panNo)-1] = '\0';

                        if(validate_Pan(seller_data.panNo))
                                break;
                        else
                            printf("Ente correct Pan NUmber\n");
                }
                fprintf(fptr,"%s,%d,%ld,%s,%s,%s\n",seller_data.name,seller_data.id ,seller_data.phoneNo ,seller_data.emailId ,seller_data.panNo,seller_data.password);
        }

        fclose(fptr);

}

seller_Details *file_to_list(seller_Details *seller_root_1)
{

        seller_Details q_data ;

        char *seller_file = "seller_info.txt";
        FILE *fptr ;
        char buffer[BUFFER_SIZE];
        seller_Details *seller_root = NULL;

        fptr =fopen(seller_file ,"r");
        if(fptr == NULL)
        {
                printf("%s file is not found\n",seller_file);

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
                                        q_data = seller_extraction_from_file(buffer , q_data);
                                        seller_root = create_lisr_of_seller(seller_root ,q_data );

                                        //printf("return add %p\n",seller_root);

                        }
                }
}

        fclose(fptr);

        return seller_root;
}

seller_Details seller_extraction_from_file(char *str , seller_Details q_data)
{
        //printf("str recv: %s\n",str);

        char *piece = NULL;

        int index = 0;
                piece = strtok(str,",");
                while(piece !=NULL)
                {

                        if(index == 0)
                        {
                           strcpy(q_data.name , piece);
                           index =1;
                        }
                        else if(index == 1)
                        {
                                q_data.id = atoi(piece);
                                index =2;
                        }
                        else if(index ==2)
                        {
                                q_data.phoneNo = atoi(piece);
                                index = 3;
                        }
                        else if(index == 3)
                        {
                           strcpy(q_data.emailId , piece);
                           index =4;
                        }
                        else if(index == 4)
                        {
                          strcpy(q_data.panNo , piece);
                           index =5;
                        }
                        else if(index == 5)
                        {
                           strcpy(q_data.password , piece);
                           q_data.password[strlen(q_data.password)-1] = '\0';
                           index =6;
                        }

                        piece = strtok(NULL,",");
                }

                return q_data ;
}

product_details *product_registration(product_details *root)
{

        char *str  = "product_info.txt";
        char buffer[BUFFER_SIZE];
        FILE *fptr = NULL;
        product_details p_data ;
        int seller_num =0 ;
        fptr = fopen(str,"r");
        if(fptr == NULL)
        {
                printf("%s file is not found please check\n",str);
                return NULL;
        }
        else
        {
              //  printf("file open is scuccess\n");
                  while(!feof(fptr))
                {

                        if(!(fgets(buffer,BUFFER_SIZE,fptr)))

{
                                //printf("file is empty\n");
                                break ;
                        }
                        else
                        {

                                        p_data = data_extraction_from_buffer(buffer ,p_data ,&seller_num);

                                        p_data.seller_id =  seller_num ;
                                        //printf("point :sller-id %d prod: %d\n",p_data.seller_id ,p_data.product_id );
                                        //getchar();
                                        root = create_list_for_product(root , p_data);

                        }
                }
        }
return root;
}

product_details data_extraction_from_buffer(char *str, product_details DATA , int *seller_id)
{
        int index = 0 , i =0 , j =0 ,l = 0, date_index = 0 , num = 0 ;

        char *piece = NULL;
        char *piece_date = NULL;
        char temp[10] ;

                piece = strtok(str,",");
                while(piece !=NULL)
                {
                        //printf("piece :%s\n",piece);
                        if(index == 0)
                        {
                                //printf("piece :%s\n",piece);
                                DATA.seller_id = atoi(piece);
                                //printf("data extraction :sller-id %d\n",DATA.seller_id);
                                *seller_id = DATA.seller_id ;
                                index = 1;
                        }
                        else if(index == 1)
                        {
                                DATA.product_id = atoi(piece);
                                index = 2;
                        }
                        else if(index == 2)
                        {
                                strcpy(DATA.product_name , piece);
                                index =3;
                        }
                        else if(index == 3)
                        {
                                strcpy(DATA.product_details , piece);
                                index = 4;
                        }
                        else if(index == 4)
                        {
                                DATA.product_price = atoi(piece);
                                index = 5;
                        }
                        else if(index == 5)
                        {
                                //printf("str :%s\n",piece);


                                piece_date = strtok(piece,"-");
                                while(piece_date !=NULL)
                                {
                                        DATA.end_date[date_index++] = atoi(piece_date);
                                        piece_date = strtok(NULL,"-");
                                }

                                DATA.end_date[date_index++] = atoi(temp);

                                //printf("date :%d-%d-%d \n",DATA.end_date[0] ,DATA.end_date[1] , DATA.end_date[2] );
                                //getchar();
                        }
                        piece = strtok(NULL,",");
                }

        return DATA;
}


product_details *create_list_for_product(product_details *source , product_details p_data)
{


        if(source == NULL)
        {
                source = (product_details *) malloc(sizeof(product_details));

                  source->seller_id = p_data.seller_id ;
                 // printf("sller-id %d\n",source->seller_id);
                  source->product_id = p_data.product_id ;
                  strcpy(source->product_name,p_data.product_name);
                  strcpy(source->product_details , p_data.product_details);
                  source->product_price = p_data.product_price;
                  for(int i = 0 ; i <3 ; i++)
                  {
                        //printf("data date :%d\n",p_data.end_date[i]);
                         source->end_date[i] = p_data.end_date[i] ;
                        //printf("source date :%d\n",source->end_date[i]);

                   }
                source->next = NULL;

        }
        else
        {
                product_details *p = source ;
                product_details *temp = (product_details *) malloc(sizeof(seller_Details));
                  temp->seller_id = p_data.seller_id ;
                  temp->product_id = p_data.product_id ;
                  strcpy(temp->product_name,p_data.product_name);
                  strcpy(temp->product_details , p_data.product_details);
                  temp->product_price = p_data.product_price ;
                  for(int i = 0 ; i <3 ; i++)
                       temp->end_date[i] = p_data.end_date[i] ;

               while(p->next != NULL)
                 {
                        p = p->next ;

                 }

                p->next = temp ;
                temp->next = NULL ;

        }

        //printf("source is return %p\n",root);
        return source;

}


int *lookup(product_details *source, int prod_id , int *index )
{


         int count = 1 , check_flag = 0;

         if(source ==  NULL)
         {
                printf("list is empty\n") ;
                return NULL ;
          }

        product_details *p = source ;

        int i = 0 , j =0;

        while(p!=NULL)
        {
                if(p->product_id  == prod_id)
                {
                        printf("Name: %s, Details %s,Price %d ,End-Date %d-%d-%d \n",p->product_name , p->product_details,p->product_price,p->end_date[0],p->end_date[1],p->end_date[2]);
                        check_flag = 1;
                        break;
                }
                else
                {
                        count++ ;

                }
                p = p->next ;
        }

        if(check_flag == 1)
        {
                *index = count ;
        }
        else
                *index = -1;

        return index ;
}

int* len_of_list(product_details  *source ,int *index)
{
        int count =0 ;

        if(source ==  NULL)
        {
                printf("list is empty\n") ;
                return NULL ;
        }


        product_details   *p = source ;

        while(p!=NULL)
        {
                count ++;
                p = p->next ;
        }

        *index = count ;
        return index ;
}


product_details *delete_product(product_details *source ,int p_id)
{

        int position = 0   , len = 0 , link =1;
        char ch ;

        //printf("source addres:%p\n",source);
        if(source ==  NULL)
        {
                printf("list is empty\n") ;
                return NULL ;
         }

        product_details *p = source ;
        product_details *temp = source  ;
        position = *lookup(p,p_id,&position) ;
        len = *len_of_list(p,&len);
        printf("please enter y to delete \n");
        scanf(" %c",&ch);

        if((ch == 'y' || ch == 'Y')&&position >0)
        {
                if(position == 1)
                {
                        source = temp->next ;
                        temp->next = NULL ;
                }
                else if(position < len)
                {

                        while(link < position-1)
    {
                                temp = temp->next;
                                link++ ;

                        }

                        product_details* del = temp->next;
                        del->next = del->next ;
                        temp->next = del->next ;

                }
                else if(position == len)
                {
                        link = 1 ;


                        while(link < position-1)
                        {
                                temp = temp->next;
                                link++;
                        }

                        temp->next = NULL;


                }
        }
        else
        printf("product -id is  not deleted\n");

return source;

}

product_details * modify_product_details(product_details *p_root ,int id , seller_Details *selle_id)
{

                product_details *p = p_root ;
                if(p==NULL)
                {
-               printf("product list is empty\n");
                        return NULL;
                }
                //product_details *p = p_root ;

                char ch ;

                while(p!=NULL)
                {
                        if(p->product_id == id)
                        {
                                printf("Name: %s, Details %s,Price %d ,End-Date %d-%d-%d \n",p->product_name , p->product_details,p->product_price,p->end_date[0],p->end_date[1],p->end_date[2]);

                                printf("enter y to update\n");

                                scanf(" %c",&ch);

                                if(ch == 'y' || ch == 'Y')
                                {
                                        printf("enter the Product name \n");
                                        getchar();
                                        fgets(p->product_name , 30 , stdin);
                                        p->product_name[strlen(p->product_name)-1] = '\0';

                                        printf("enter the detials \n");
                                        getchar();
                                        fgets(p->product_details , 30 , stdin);
                                        p->product_details[strlen(p->product_details)-1] = '\0';


                                        printf("enter the price\n");
                                        scanf("%d",&p->product_price);

                                        printf("enter the END Date in format of DD-MM-YYYY\n");
                                        scanf("%d-%d-%d",&p->end_date[0],&p->end_date[1],&p->end_date[2]);
                                        p->seller_id =selle_id->id ;

                                        printf("Product Data Update successfully\n");
                                    }
                        }

                        p = p->next;
                }

        return p_root;
}


void display_product(product_details *product_root)
{
        product_details *p = product_root ;
        int ch ;

        while(p!=NULL)
        {
                printf("Id: %d,Name: %s, Details %s,Price %d ,End-Date %d-%d-%d \n",p->product_id,p->product_name , p->product_details,p->product_price,p->end_date[0],p->end_date[1],p->end_date[2]);

                p=p->next;
        }
}

void adding_the_product_into_file(int selle_id)
{
        FILE *fptr = NULL;
        char *str = "product_info.txt";
        product_details p_root ;
        fptr = fopen(str,"a");

        if(fptr == NULL)
        {
                printf("%s is not found please check\n",str);
                return ;
        }
        else
        {
                printf("enter the Product name \n");
                while(1)
{
                        fgets(p_root.product_name , 30 , stdin);
                        p_root.product_name[strlen(p_root.product_name)-1] = '\0';
                        if(alpha_validator(p_root.product_name))
                           break ;
                        else
                        printf("user name should be in characters\n");
                }
                printf("enter the detials \n");
                scanf("%[^\n]",p_root.product_details);
                p_root.product_details[strlen(p_root.product_details)] = '\0';


                printf("enter the product id\n");
                scanf("%d",&p_root.product_id);
                //p_root.product_id = int_ans_choice();

                printf("enter the price\n");
                scanf("%d",&p_root.product_price);

                printf("enter the END Date in format of DD-MM-YY\n");
                scanf("%d-%d-%d",&p_root.end_date[0],&p_root.end_date[1],&p_root.end_date[2]);

                fprintf(fptr,"%d,%d,%s,%s,%d,%d-%d-%d\n",selle_id,p_root.product_id,p_root.product_name,p_root.product_details,p_root.product_price,p_root.end_date[0],p_root.end_date[1],p_root.end_date[2]);
        }

        fclose(fptr);
}








