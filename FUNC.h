#ifndef _FUNC_H_
#define _FUNC_H_



//here in the .h file we're going to write the prototypes of our functions
//those are examples from a previous project i did
//obviously we're going to delete them 
void create_account(clients *ptr);
u16 check_password(u32 x);
void delay(int y);
void set_pasid(clients *ptr);
void transaction(clients *ptr,u64 targeted_id,u16 amount);







#endif