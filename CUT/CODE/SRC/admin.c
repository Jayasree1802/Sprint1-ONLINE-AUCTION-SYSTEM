//header files
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"header.h"
#include<stdlib.h>



/*********************************************************************************
 * FUNCTION_NAME        :      admin
 * DESCRIPTION          :      This function is used to print the main menu and to choose the menu from the entered choice .
 * Parameters           :      seller_details structure seller_rote and structure buyer_details buyer_root
 * return type          :      void return type
 *******************************************************************************/
void admin(seller_Details *seller_root , buyer_Details *buyer_root)
{
        int ch , exit_flag = 0 , p_id = 0 , seller_id = 0 , exit_flag_1 = 0;
        design();
        if(admin_login())
        {
                system("clear");
                printf("WelCome To Admin menu\n");
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
                                 case MANAGE_SELLER:
                                        if(seller_root == NULL)
                                        {
                                                printf("seller is not listed\n");

                                        }
                                        else
                                        {
                                                printf("1) Block seller\n");
                                                printf("2) List seller\n");
                                                scanf("%d",&ch);
                                                switch(ch)
                                                {
                                                        case BLOCK_SELLER:
                                                                block_sller(seller_root);
                                                                break;
                                                        case LIST_SELLER:
                                                                if(seller_root!=NULL)
                                                                        display(seller_root);
                                                                else
                                                                        printf(" seller list is empty\n");
                                                                break;
                                                }//end_switch
                                        }//end_else

                                        break;

                                 case MANAGE_BUYER:

                                        if(buyer_root == NULL)
                                        {
                                                printf("Byer is not listed\n");
                                        }
                                        else
                                        {
                                                printf("1) Block buyer\n");
                                                printf("2) List buyer\n");
                                                scanf("%d",&ch);
                                                switch(ch)
                                                {
                                                        case BLOCK_BUYER:
                                                                block_buyer(buyer_root);
                                                                break;
                                                        case LIST_BUYER:
                                                                if(buyer_root!=NULL)
                                                                        display_buyer(buyer_root);
                                                                else
                                                                        printf("List is empty\n");

                                                                break;
                                                }
                                        }

                                        break ;

                                case MANAGE_PRODUCTS:
                                        
                                        if(seller_root->link == NULL)
                                        {
                                                printf("Products are not listed\n");
                                        }
                                        
                                        else
                                        {
                                                printf("1) Add product \n");
                                                printf("2) Remove products\n");
                                                printf("3) modify product\n");
                                                scanf("%d",&ch);
                                                switch(ch)
                                                {
                                                        case ADD_PRODUCT:
                                                                printf("seller_root->link %p\n",seller_root->link );
                                                                seller_root->link = NULL;
                                                                seller_root->link  = add_product_to_list(seller_root->link );
                                                                break ;
                                                        case REMOVE_PRODUCT:
                                                                if(seller_root->link != NULL)
                                                                {
                                                                        printf("enter the product id\n");
                                                                        scanf("%d",&p_id);
                                                                        seller_root->link = delete_product(seller_root->link ,p_id );
                                                                        save_product_info_file(seller_root->link);
                                                                }
                                                                else
                                                                        printf("product list is empty\n");
                                                                break;
                                                                
                                                        case MODIFY_PRODUCT:
                                                                
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
                                                }//end_switch
                                        }//end_else

                                      case EXIT:
                                      exit_flag = 1;
                        }//end_switch
                        
                    if(exit_flag == 1)
                        break;
                        
                }//end_while

        }//end_if
}



/*******************************************************************************************
**
**  FUNCTION NAME   : admin_login
**  DESCRIPTION     : It is the function for admin login into the application
**  PARAMETERS      : No parameters
**  RETURN          : No Return 
*******************************************************************************************/
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
                        strcpy(password,getpass("enter password: "));
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



/*******************************************************************************************
**  FUNCTION NAME   : read_admin_file
**  DESCRIPTION     : In this function it  reads the admin data to a file 
**  PARAMETERS      : Structure admin_data with variable source
**  RETURN          :  No Return 
*******************************************************************************************/
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



/*******************************************************************************************
**  FUNCTION NAME   : add_product_to_list
**  DESCRIPTION     : In this function admin adds the products to the linkedl list
**  PARAMETERS      : Structure product_Details with variable source
**  RETURN          :  Return source
*******************************************************************************************/
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



/*******************************************************************************************
**  FUNCTION NAME   : block_seller
**  DESCRIPTION     : It is the function admin has authority to block the seller
**  PARAMETERS      : structure seller_Details with variable source
**  RETURN          :  No Return 
*******************************************************************************************/
void block_sller(seller_Details *source)
{
        seller_Details  *p = source ;
        char ch ;
        int id , check_flag = 0;
        printf("enter the sller id\n");
        scanf("%d",&id);

        while(p!= NULL)
        {
                if(p->id == id)
                {
                        printf("seller-d %d and %s is listed\n",p->id,p->name);

                        printf("enter y to block the seller \n");
                        scanf(" %c",&ch);
                        if(ch == 'y' || ch == 'Y')
                        {
                                printf("seller-d %d is blocked successfully\n",p->id);
                                p->status = 1;
                        }
                        else
                         printf("seller-d %d is not blocked\n",p->id);

                        check_flag = 1;

                 }

                p = p->next ;
        }

        if(check_flag == 0)
                printf("seller-d %d is not listed\n",id);
}



/*******************************************************************************************
**  FUNCTION NAME   : block_buyer
**  DESCRIPTION     : It is the function admin has authority to block the buyer
**  PARAMETERS      : structure buyer_Details with variable source
**  RETURN          :  No Return 
*******************************************************************************************/
void block_buyer(buyer_Details *source)
{
        buyer_Details   *p = source ;
        char ch ;
        int id  , check_flag =0  ;
        printf("enter the buyer id\n");
        scanf("%d",&id);

        while(p!= NULL)
        {
                if(p->id == id)
                {
                        check_flag = 1;

                        printf("Buer-id %d and buyer name : %s is listed\n",p->id,p->name);
                        printf("enter y to block \n");
                        scanf(" %c",&ch);
                        if(ch== 'y' || ch == 'Y')
                        {
                                p->status = 1;
                                printf("Buyer name %s,Buyer Id %d is blocked successfully\n",p->name,p->id );
                        }
                        else
                           printf("Buyer name %s,Buyer Id %d is not blocked\n",p->name,p->id );

                 }

                p = p->next ;
         }

         if(check_flag == 0)
              printf("Buer-id %d is not listed\n",id);

}

