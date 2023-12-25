#ifndef _FUNC_H_
#define _FUNC_H_



//here in the .h file we're going to write the prototypes of our functions
//those are examples from a previous project i did
//obviously we're going to delete them 
int login(void);
int count_accounts();
accounts * load(int accnum);
int trans(accounts*accounts_infile,int n,int *sender,int *receiver);
int save(accounts *account_list,int n);





#endif
