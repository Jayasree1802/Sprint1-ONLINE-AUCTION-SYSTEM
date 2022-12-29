//definition file for validation
//header files

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

//Macros 
#define MAX 10
#define MIN 5

/*******************************************************************************************
**  FUNCTION NAME   : intiger_validation
**  DESCRIPTION     : It is the function for validating the string or username
**  PARAMETERS      : character string is the parameter
**  RETURN          : No Return 
*******************************************************************************************/

int intiger_validation(char *str)
{
	long int num ;
	int len =0 , count = 0;
	num = atoi(str);
	len = strlen(str);
	if(num <= 0)
	{
		return 0;
	}
	else
	{	
		do {
			num /= 10;
			++count;
			
		  }while(num != 0); 
		  if(len == count)
		  	return 1;
		  else 
		  	return 0;	
        }
}


/*******************************************************************************************
**  FUNCTION NAME   : alpha_validator
**  DESCRIPTION     : It is the function for validating the alphabets
**  PARAMETERS      : parameter of character type of string
**  RETURN          :  No Return 
*******************************************************************************************/

int alpha_validator(char *s)
{

        //validation for alphabets
        for(char *p=s;*p!='\0';p++)
        {
                if((!isalpha(*p)) && (*p!=' '))
                        return 0;
        }
        //validation for length
        if(strlen(s)>15 || strlen(s) < 3)
        {
                printf("Enter name within the length of 5 to 15\n");
                return 0;
        }
        return 1;
}

/*******************************************************************************************
**  FUNCTION NAME   : phone_validation
**  DESCRIPTION     : It is the function to validate the phone_number of buyer and seller
**  PARAMETERS      : parameter of character pointer
**  RETURN          :  No Return 
*******************************************************************************************/

int phone_validation(char *str)
{
	long int num ;
	int len =0 , count = 0;
	len = strlen(str);
	if(num <= 0 || len < 10 || len > 10)
	{
		return 0;
	}
	else
	{
		num = atoi(str);	
		do {
		
			num /= 10;
			++count;
			
		  }while(num != 0);
		  
		  if(len == count)
		  	return 1;
		  else 
		  	return 0;	
        }	
}


/*******************************************************************************************
**  FUNCTION NAME   : password_validation
**  DESCRIPTION     : It is the function to validate the password
**  PARAMETERS      : character string is parameter
**  RETURN          :  No Return 
*******************************************************************************************/

int password_validation(char *str)
{
	char *ptr = str ;
	
	int c_count = 0 , s_count = 0 , i_count = 0;
	
	while(*ptr !='\0')
	{
		if(*ptr >= 'A' && *ptr <= 'Z')	
		{
			c_count = 1;	
			//printf("Capital\n");
		}
		else if(*ptr >= 'a' && *ptr <= 'z')
		{
			s_count = 1;
			//printf("small\n");
		}
		else if(*ptr >= 48 && *ptr <= 58 )
		{
			i_count = 1;
			//printf("num\n");
		}
		else 
		{
		
		}
		
		ptr++;
	}
	
	if(c_count &&s_count &&i_count )
	return 1;
	else 
	return 0;
}

int int_ans_choice(int n , int m)
{
	int ch;
	char temp[10];
	
		while(1)
		{
			scanf("%s",temp);
			if(intiger_validation(temp))
			{
				ch = atoi(temp);
				if(ch >= n && ch <= m)
				{
					ch = atoi(temp);
					break;
				}
				else 
					printf("enter number with range of %d to %d \n",n,m);
				
			}
			else
			{
				printf(" int enter valid input\n");
				return -1;
			}
		}
	return ch;
}
int int_id_validation()
{
	char int_reading[10];
	
	while(1)
	{
		scanf("%s",int_reading);
		int_reading[strlen(int_reading)] = '\0';
		
		if(intiger_validation(int_reading))
		{
			return atoi(int_reading);
			break;
		}	
		else
		printf("Product-Id is in intiger farmat only\n");		
	}
}

/*******************************************************************************************
**  FUNCTION NAME   : Emai_validation
**  DESCRIPTION     : It is the function validate the email for buyer and seller
**  PARAMETERS      : passing parameter as char type of string
**  RETURN          :  No Return 
*******************************************************************************************/

int Emai_validation(char *str)
{
	char *ptr = str ;
	
	int c_count = 0 , s_count = 0 , i_count = 0 ,e_count =0 ; 
	
	while(*ptr !='\0')
	{
		if(*ptr >= 'A' && *ptr <= 'Z')	
		{
			c_count = 1;	
			//printf("Capital\n");
		}
		else if(*ptr >= 'a' && *ptr <= 'z')
		{
			s_count = 1;
			//printf("small\n");
		}
		else if(*ptr >= 48 && *ptr <= 58 )
		{
			
			//printf("num\n");
		}
		else if(*ptr == '@')
		{
			e_count = 1;
		}
		else if(*ptr == '.')
		{
			i_count = 1;
		}
		
		
		ptr++;
	}
	
	if(e_count == 1 && i_count == 1 )
	return 1;
	else 
	return 0;	
}
/*******************************************************************************************
**  FUNCTION NAME   : validate_pan
**  DESCRIPTION     : It is the function validate the pan for buyer and seller
**  PARAMETERS      : character of pan no
**  RETURN          :  No Return 
*******************************************************************************************/

int validate_Pan(char *Pan_No)
{

       int i = 0 , c_flag = 0 , n_flag = 0 , s_flag =0 ;

	//printf("pan number len %d\n",strlen(Pan_No));
        
		while(Pan_No[i]!='\0')
		{
			if( (Pan_No[i] >='A'&& Pan_No[i] <= 'Z') )
			{

			       c_flag = 1;
			}

			if(  (Pan_No[i]>48 && Pan_No[i]<57) )
			{

				n_flag = 1;
			}
		       if( (Pan_No[i] >='A' && Pan_No[i] <='Z' ) )
			{

			       s_flag = 1 ;
			}
			i++;
               }
       

        //printf("\nvalid Pan No");

	if(c_flag == 1 && n_flag == 1 && s_flag == 1)
        return 1;
        else
        return 0;

}
