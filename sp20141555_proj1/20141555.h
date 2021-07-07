#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ADD 1048575
#define MAX_VAL 255

typedef struct node{
		int index;
		char str[80];
		struct node *next;
}Node;
Node * head=NULL;
typedef struct opnode_{
		unsigned int opcode;
		char mnemonic[100];
		struct opnode_* next;
}opnode;
typedef struct optable_{
		opnode *head;
			
}optable;
optable* table;
DIR* opendir(const char* name);
struct dirent* readdir(DIR* dp);
int closedir(DIR* dp);

int isspace(int c);
void direc();
void history(char* str,int n);
int dump(unsigned char *arr,unsigned int start,unsigned int end,unsigned int *tempend, int check);
void fill(unsigned char *arr,unsigned int start,unsigned int end,unsigned int val);
void addopnode(char*opcode,unsigned int optmp,int opindex);
void printtable();
int opcodetable_func_make_hash(char *arr);
void findcode(int index, char *com);
