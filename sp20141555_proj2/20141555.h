#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ADD 1048575
#define MAX_VAL 255
int base;
typedef struct node{
		int index;
		char str[80];
		struct node *next;
}Node;
Node * head=NULL;
typedef struct opnode_{
		unsigned int opcode;
		char mnemonic[100];
		int len;
		struct opnode_* next;
}opnode;
typedef struct optable_{
		opnode *head;
			
}optable;
optable* table;
typedef struct symtab_{
	char symbol[100];
	int add;
	struct symtab_ *next;
}symtab;
symtab* symt;

DIR* opendir(const char* name);
struct dirent* readdir(DIR* dp);
int closedir(DIR* dp);
char* itoa(int val,char* buf,int radix);
int isspace(int c);

void direc();
void history(char* str,int n);
int dump(unsigned char *arr,unsigned int start,unsigned int end,unsigned int *tempend, int check);
void fill(unsigned char *arr,unsigned int start,unsigned int end,unsigned int val);
void addopnode(char*opcode,unsigned int optmp,int opindex,int len);
void printtable();
int opcodetable_func_make_hash(char *arr);
void findcode(int index, char *com);
void typefile(char finame[80]);
void fun_assemble(char *command);
int searchop(char* command);
int lenfind(char *opcode);
int searchsymtab(char *command);
void insertsymtab(char *sym, int add);
int searchsym(char *sym);
int searchconstant(char *str);
char* transstring(char* str);
int searchregister(char *arr);
int nextaddfind(char* opcode,char* operand);
int opcodefind(char*opcode);
int searchhexa(char* arr);
