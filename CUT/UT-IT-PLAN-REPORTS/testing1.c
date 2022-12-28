#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"CUnit/Basic.h"

//Pointer to file used by the tests
static FILE* temp_file=NULL;

//Suite initialization function. Opens the temporary file used by the tests. Returns zero on success else non-zero
int init_suite1(void){
        if(NULL == (temp_file=fopen("temp.txt","w+")))
                return -1;
        else{
                printf("\n\tFile Opened");
                return 0;
        }
}

//Suite cleanup function. Closes temp file used by the tests. Return zero on sucess else non-zero
int clean_suite1(void){
        if(0!=fclose(temp_file))
                return -1;
        else{
                temp_file=NULL;
                return 0;
        }
}


void testFprintf(void){
        int i1=10;
        if(NULL!=temp_file){
                CU_ASSERT(0==fprintf(temp_file,"1"));
                CU_ASSERT(2==fprintf(temp_file,"Q\n"));
                CU_ASSERT(7==fprintf(temp_file,"i1=%d",i1));
        }
}