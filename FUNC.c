/*
here we're going to write the function definitions.
we have a couple of examples here from a previous project.  
we're going to delete them they're just here to clarify the purpose of the file. 
*/
#include <stdio.h>
#include  <time.h>
#include "FUNC.h"
#include <stdlib.h>




void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * 0.5;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
 

u16 check_password(u32 x){
	if(x == 1234){
		printf("ACCESS VALID!");
		printf(".");
		delay(1000000);
		printf(".");
		delay(1000000);
		printf(".");
		delay(1000000);
		return 1;
	}
	else if(x != 1234){
		return 0;
	}
}
void create_account(clients *ptr){
	printf("Enter the full name :");
	fflush(stdin);
	scanf("%[^\n]s" , &ptr->name);
	printf("Enter the adress :");
	fflush(stdin);
	scanf("%[^\n]s" , &ptr->adress);
	printf("Enter the age :");
	scanf("%hu" , &ptr->age);
	if(ptr->age < 21 ){
		printf("Enter the guardian national ID :");
		scanf("%ld" , &ptr->guard_id);
	}
	printf("Enter the balance :");
	scanf("%u" , &ptr->balance);
	
}
void set_pasid(clients *ptr){
	u16 x = (u16)(rand() % 99000) + 1000;
	ptr[0].password = x;
	u64 y = (u64)(rand() % 98999999999) + 1000000000;
	ptr[0].bank_id = y;
	printf("\nThe ID for this account is going to be : %hu  \nThe password : %hu \n ", y , x);
	
}

void transaction(clients *ptr,u64 targeted_id,u16 amount){
	printf("%lu\n" , ptr[0].bank_id );
	for(u16 i = 0 ; i < amount ; i++){
		if(ptr[i].bank_id == targeted_id){
			printf("yupppy");
		}
	}
}

 