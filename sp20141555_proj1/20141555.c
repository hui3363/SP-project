#include "20141555.h"

int main(){
	char c;char inp[80];char* command;int n=0;char nstr[80];
	unsigned char arr[MAX_ADD+1]={0};
	unsigned int start; unsigned int end;
	unsigned int tempend=0;int check=0; unsigned int editadd; unsigned int value_;
	int fstart;int fend;int fval;int re; Node* p;
	int rech;int i;int comindex;
	char line[100];unsigned int optmp; char opcode[100];int opindex;
	unsigned int tstart,tend; int while_out=0;
	int spcnt=0;

	//file scan
	FILE *fp=fopen("opcode.txt","r");

	//opcode table
	table=(optable*)malloc(sizeof(optable)*20);

	for(i=0;i<20;i++){
		table[i].head=NULL;
	}


	while(1){
		if(!fgets(line,100,fp)) break;
		sscanf(line,"%x %[^ \t]s",&optmp,opcode);
		spcnt+=1;
		opindex=opcodetable_func_make_hash(opcode);
		addopnode(opcode,optmp,opindex);
	}

	//shell
	while(1){
		start=0;end=0;
		spcnt=0;
		check=0;
		printf("sicsim> ");
		fflush(stdin);
		while(1){
			while_out=0;
			c=getchar();
			if(!isspace(c)){
			break;
			}
			if(c=='\n'){
				printf("명령어를 입력하세요.\n");
				while_out=1;
				break;
			}
		}
		if(while_out==1){
			continue;
		}
		inp[0]=c;
		fgets(inp+1,80,stdin);
		if(inp[strlen(inp)-1]=='\n'){
			inp[strlen(inp)-1]='\0';
		}
		strcpy(nstr,inp);
		for(i=0;i<strlen(inp);i++){
			if(!isspace(inp[i]))
				spcnt++;
		}
		if(spcnt==0||*inp=='\0'){
			printf("Error!\n");
			continue;

		}
		// tokenize input
		command=strtok(inp," \t");

		//help
		if(strcmp(command,"help")==0 ||strcmp(command,"h")==0){

			//help 만 입력한게 아니고 help 뒤에 다른 명령어가 있을 때 예외처리
			if((strcmp(nstr,"help")!=0&&strcmp(nstr,"h")!=0) && (strcmp(nstr,"help ")!=0&&strcmp(nstr,"help	")!=0&&strcmp(nstr,"h ")!=0&&strcmp(nstr,"h	")!=0)){
					command=strtok(NULL,"\0");
					spcnt=0;
					if(command!=NULL){
						for(i=0;i<strlen(command);i++){
							if(!isspace(command[i]))
								spcnt++;
						}
						if(spcnt!=0){
							printf("Error!\n");
							continue;
						}
					}
			}
			//올바른 help 명령어 이면 history()함수를 통해 linked list에 명령어 삽입
			n+=1;
			history(nstr,n);
			//명령어 출력
			printf("h[elp]\nd[ir]\nq[uit]\nhi[story]\ndu[mp] [start,end]\ne[dit] address, value\nf[ill] start, end, value\nreset\nopcode mnemonic\nopcode list\n");
		}

		//dir
		if(strcmp(command,"dir")==0 ||strcmp(command,"d")==0){
			//dir 뒤에 다른 명령어가 붙어있을 때 예외처리
			if((strcmp(nstr,"dir")!=0&&strcmp(nstr,"d")!=0) && (strcmp(nstr,"dir ")!=0&&strcmp(nstr,"dir	")!=0&&strcmp(nstr,"d ")!=0&&strcmp(nstr,"d	")!=0)){
				command=strtok(NULL,"\0");
				spcnt=0;
				if(command!=NULL){
					for(i=0;i<strlen(command);i++){
						if(!isspace(command[i]))
							spcnt++;
					}
					if(spcnt!=0){
						printf("Error!\n");
						continue;
					}
				}
			}

			//올바른 dir 입력이면 역시 history()를 호출하여 링크드 리스트에 삽입
			n+=1;
			history(nstr,n);
			//direc()을 호출하여 현재 폴더의 실행파일과 폴더들을 출력
			direc();
		}
		//quit
		else if(strcmp(command,"quit")==0 ||strcmp(command,"q")==0){

			//quit 뒤에 다른 명령어가 붙어 있으면 예외처리
			if((strcmp(nstr,"quit")!=0&&strcmp(nstr,"q")!=0) && (strcmp(nstr,"quit ")!=0&&strcmp(nstr,"quit\t")!=0&&strcmp(nstr,"q ")!=0&&strcmp(nstr,"q\t")!=0)){
				command=strtok(NULL,"\0");
				spcnt=0;
				if(command!=NULL){
					for(i=0;i<strlen(command);i++){
						if(!isspace(command[i]))
							spcnt++;
					}
					if(spcnt!=0){
						printf("Error!\n");
						continue;
					}
				}
			}

			//올바른 입력이면 역시 history()를 호출하여 링크드리스트에 삽입
			n+=1;
			history(nstr,n);
			//shell 프로그램 종료
			break;
		}

		//history
		else if(strcmp(command,"history")==0 ||strcmp(command,"hi")==0){
			//history 뒤에 다른 명령어가 붙어 있을때 예외처리
			if((strcmp(nstr,"history")!=0&&strcmp(nstr,"hi")!=0) && (strcmp(nstr,"history ")!=0&&strcmp(nstr,"history\t")!=0&&strcmp(nstr,"hi ")!=0&&strcmp(nstr,"hi\t")!=0)){
				command=strtok(NULL,"\0");
				spcnt=0;
				if(command!=NULL){
					for(i=0;i<strlen(command);i++){
						if(!isspace(command[i]))
							spcnt++;
					}
					if(spcnt!=0){
						printf("Error!\n");
						continue;
					}
				}
			}
			//올바른 입력이면 history()호출하여 링크드 리스트에 삽입
			n+=1;
			history(nstr,n);

			//링크드 리스트의 head부터 링크드 리스트의 끝까지 모두 출력
			p=head;
			while(p!=NULL){
				printf("%-6d%s\n",p->index,p->str);
				p=p->next;
			}
		}
		//dump
		else if(strcmp(command,"dump")==0 ||strcmp(command,"du")==0){


			//시작주소와 끝주소를 모두 입력하지 않으면 check=0
			if(command!=NULL){
				command=strtok(NULL,",");
				if(command!=NULL){//시작주소 있음

					if(strrchr(nstr,',')==NULL&&sscanf(command,"%x %x",&tstart,&tend)==2){
						// ','가 없는 경우 예외처리
						printf("Error!\n");
						continue;
					}

					//시작 주소만 주어졌을 때: check=1
					check+=1;
					sscanf(command,"%x",&start);
					command=strtok(NULL,"\n");
					if(command==NULL&&strrchr(nstr,',')!=NULL){
						printf("Error!\n");
						continue;
					}
					if(command!=NULL){
						//끝 주소도 주어졌을 때: check=2
						sscanf(command,"%x",&end);
						check+=1;
					}
				}
			}

			//dump()호출하여 해당 주소 메모리 출력하고 올바르지 않은 입력이라 종료될 경우에는 출력하지 않고 다시 shell 실행
			rech=dump(arr,start,end,&tempend,check);
			if(rech==-1){
				continue;
			}
			else if(rech==1){
				//dump가 올바르게 종료되면 history()호출해 링크드리스트에 삽입
				n+=1; history(nstr,n);
			}
			start=0;end=0;
		}
		//edit
		else if(strcmp(inp,"edit")==0 ||strcmp(inp,"e")==0){
			command=strtok(NULL,",");
			if(command==NULL){ //edit 뒤에 변경할 주소 입력하지 않으면 예외처리
				printf("Error!\n");
				continue;
			}
			sscanf(command,"%x",&editadd);
			command=strtok(NULL,"\n");
			if(command==NULL){ //edit 뒤에 변경할 값 입력하지 않으면 예외처리
				printf("Error!\n");
				continue;
			}
			sscanf(command,"%x",&value_);
			if(editadd<0 ||editadd>MAX_ADD){//입력한 메모리 주소가 초과할때 예외처리
				printf("Error! 주소초과\n");
				continue;
			}
			if(value_<0 || value_>MAX_VAL){ //입력한 변경 값이 초과할때 예외처리
				printf("Error! 값 초과\n");
				continue;
			}
			//올바른 입력인 경우 링크드 리스트에 삽입
			n+=1;
			history(nstr,n);
			//해당주소의 메모리값을 value로 변경
			arr[editadd]=value_;
		}
		//fill
		else if(strcmp(inp,"fill")==0||strcmp(inp,"f")==0){	
			//fill 뒤에 쉼표로 구분되어 시작 주소, 끝 주소, 메모리 값 이 입력받아지지 않는 경우 예외처리
			command=strtok(NULL,",");
			if(command!=NULL){
				sscanf(command,"%x",&fstart);
				command=strtok(NULL,",");
				if(command!=NULL){
					sscanf(command,"%x",&fend);
					command=strtok(NULL,"\n");
					if(command!=NULL){
						sscanf(command,"%x",&fval);
						//세 가지 모두 입력했지만 끝주소가 시작주소보다 작거나 주소가 범위를 초과하거나 값이 범위를 초과하는 경우 예외처리
						if(fstart>fend){
							printf("Error! 끝주소가 시작주소보다 작습니다.\n");
							continue;
						}
						if(fstart<0 || fstart> MAX_ADD ||fend<0 ||fend> MAX_ADD){
							printf("Error! 주소 초과\n");
							continue;
						}
						if(fval>MAX_VAL || fval<0){
							printf("Error! 값 초과\n");
							continue;
						}
						//fill을 호출하여 start부터 end 주소 까지 value 변경
						fill(arr,fstart,fend,fval);
						//history호출하여 링크드리스트에 삽입
						n+=1; history(nstr,n);
					}
					else{
						printf("Error\n");continue;
					}
				}
				else{
					printf("Error\n");continue;
				}
			}
			else{

				printf("Error\n");continue;
			}
		}

		//reset
		else if(strcmp(inp,"reset")==0){		
			//reset 뒤에 다른 명령어가 붙어 있을때 예외처리
			if((strcmp(nstr,"reset")!=0&&strcmp(nstr,"reset ")!=0) && strcmp(nstr,"reset\t")!=0){
				command=strtok(NULL,"\0");
				spcnt=0;
				if(command!=NULL){
					for(i=0;i<strlen(command);i++){
						if(!isspace(command[i]))
							spcnt++;
					}
					if(spcnt!=0){
						printf("Error!\n");
						continue;
					}
				}
			}
			//모든 메모리 값들을 0으로 초기화한다.
			n+=1;
			history(nstr,n);
			for(re=0;re<=MAX_ADD;re++){
				arr[re]=0;
			}
		}

		//opcode mnemonic
		else if(strcmp(inp,"opcode")==0){
			//opcodetable_func_make_hash을 호출하여 mnemonic의 해싱 결과를 찾고 findcode()호출하여  그값을 넘겨준다
			if(strcmp(nstr,"opcode")==0||strcmp(nstr,"opcode ")==0 || strcmp(nstr,"opcode\t")==0){
				printf("Error!\n");
				continue;
			}
			
			command=strtok(NULL,"\n");
			comindex=opcodetable_func_make_hash(command);
			findcode(comindex,command);
			//링크드리스트에 삽입
			n+=1;
			history(nstr,n);
		}

		//opcodelist
		else if(strcmp(inp,"opcodelist")==0){
			if((strcmp(nstr,"opcodelist")!=0&&strcmp(nstr,"opcodelist ")!=0) && strcmp(nstr,"opcodelist\t")!=0){		
				command=strtok(NULL,"\0");
				spcnt=0;
				if(command!=NULL){
					for(i=0;i<strlen(command);i++){
						if(!isspace(command[i]))
							spcnt++;
					}
					if(spcnt!=0){
						printf("Error!\n");
						continue;
					}
				}
			}
				//printtable()호출하여 opcode table 출력
			printtable();
			n+=1;
			history(nstr,n);
		}

	}
	//file 닫기
	fclose(fp);
	free(table);
	return 0;
}
void history(char* str,int n)
{
	// 기능: str과 n을 새로운 노드를 만들어서 linked list* head의 맨 뒤에 삽입
	Node* ptr;
	Node* newn;
	newn=(Node*)malloc(sizeof(Node));
	newn->index=n;
	strcpy(newn->str,str);
	newn->next=NULL;
	ptr=head;
	if(ptr==NULL)
		head=newn;
	else{
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next=newn;
	}


}
void direc()
{
	//기능: directory를 열어서 실행파일과 폴더들을 출력하고 directory 닫기
	DIR* dp =NULL;
	struct dirent* entry = NULL;
	struct stat buf;
	char temp[1000];
	int tmp=0;
	if((dp=opendir("/sogang/under/cse20141555/sp"))==NULL)
	{
		printf("/sogang/under/cse20141555/sp를 열 수 없습니다.\n");
	}
	while((entry=readdir(dp))!=NULL)
	{
		lstat(entry->d_name,&buf);
		strcpy(temp,entry->d_name);
		if(strcmp(temp,".")==0 ||strcmp(temp,"..")==0){//.과 ..은 예외처리
			continue;
		}
		if(S_ISDIR(buf.st_mode))//directory/ 출력
			printf("%20s/\t",entry->d_name);
		else if(S_IEXEC&buf.st_mode)//실행파일* 출력
			printf("%20s*\t",entry->d_name);
		tmp+=1;
		if(tmp%3==0)
			printf("\n");
	}
	printf("\n");

	closedir(dp);
}
int dump(unsigned char *arr,unsigned int start,unsigned int end,unsigned int* tempend,int check)
{
	//기능 : arr에서 주어지는 시작주소와 끝주소에 따라서 해당입력이 올바르지 않으면 에러처리하고 올바른 입력이면 메모리값들을 출력한다.
	int i;unsigned int tempcol;int k;int kf;int kr;int t;
	if(check==2 && start>end){//시작주소가 끝주소보다 크면 에러처리
		printf("Error!\n");
		return -1;
	}
	if(start<0 || start>MAX_ADD || end < 0 ||end>MAX_ADD)
	{
		//주소 값들이 초과할때 에러처리
		printf("Error! 주소 초과\n");
		return -1;
	}

	if(check==2){//시작주소 끝주소 주어짐
		tempcol=start-start%16;
	}
	else if(check==1){//시작 주소만 주어짐
		tempcol=start-start%16;
		if(start+159>MAX_ADD)
			end=MAX_ADD;
		else{
			end=start+159;
		}
	}
	else if(check==0){//아무것도 안주어짐
		if(*tempend==0){//마지막으로 dump로 출력한 마지막 메모리값 바로 다음부터 출력
			start=*tempend;
		}
		else
			start= *tempend+1;
		if(*tempend>=MAX_ADD){
			printf("끝까지 읽었습니다.\n");
			return -1;
		}
		tempcol=start-start%16;
		if(start+159<=MAX_ADD)// 시작 주소부터 160개
			end=start+159;
		else//160개가 FFFFF를 넘어가면 FFFFF까지
			end=MAX_ADD;
	}
	if(start%16!=0){//가장 왼쪽 칼럼: 메모리 주소
		printf("%05X ",tempcol);
	}
	for(i=tempcol;i<=end;i++){//시작 주소 전의 값들은 출력하지 않음
		if(i<start){
			printf("   ");
			continue;
		}
		if(i%16==0){// 가장 왼쪽 칼럼 출력
			printf("%05X ",i);
		}
		printf("%02X ",arr[i]);//메모리 값들 출력
		if(i%16==15 || i==end){
			if(i==end && i%16!=15){
				for(t=0;t<15-i%16;t++)
					printf("   ");
			}
			kf=i-i%16;
			kr=kf+15;
			printf(" ; ");
			for(k=kf;k<=kr;k++){
				if(k<start||k>end){
					printf(".");
				}
				else if(arr[k]>=' ' && arr[k]<='~')
					printf("%c",arr[k]);
				else{
					printf(".");
				}
			}
			printf("\n");
		}
	}
	*tempend=end;
	return 1;
}

void fill(unsigned char *arr, unsigned int start, unsigned int end,unsigned int val)
{
	//기능: arr에 start부터 end까지 val로 메모리 값을 변경
	int i;

	for(i=start;i<=end;i++){
		arr[i]=val;
	}
}
void addopnode(char*opcode,unsigned int optmp,int opindex)
{

	//opcode table에서 hashing 함수를 통해 발생한 opindex에 해당 opcode와 mnemonic을 새로운 노드로 만들어서 링크드리스트 마지막에 삽입
	opnode *ptr;
	opnode *newo;
	newo=(opnode*)malloc(sizeof(opnode));
	newo->next=NULL;
	newo->opcode=optmp;
	strcpy(newo->mnemonic,opcode);
	ptr=table[opindex].head;
	if(ptr==NULL){
		table[opindex].head=newo;
	}
	else{
		while(ptr->next!=NULL)
			ptr=ptr->next;
		ptr->next=newo;
	}
}
int opcodetable_func_make_hash(char *s)
{
	//hashing function
	int i,sum;
	int len=strlen(s);
	for(i=0,sum=0;i<len;i++){
		sum+=s[i];
	}
	return sum%20;

}
void printtable()
{
	//opcode table을 처음부터 끝까지 mnemonic과 opcode를 출력
	int i;
	opnode* ptr;
	for(i=0;i<20;i++){
		printf("%d : ",i);
		ptr=table[i].head;
		if(ptr==NULL)
			printf("\n");
		while(ptr!=NULL){
			printf("[%s,%X] ",ptr->mnemonic,ptr->opcode);
			if(ptr->next!=NULL){
				printf("-> ");
			}
			else{
				printf("\n");
			}
			ptr=ptr->next;
		}
	}
}
void findcode(int index, char* com)
{
	//기능: 해당 index번째의 opcode table의 링크드리스트에 com 명령어가 있는지 탐색하고 있으면 출력 없으면 에러처리
	opnode *ptr;
	ptr=table[index].head;
	while(ptr!=NULL)
	{
		if(strcmp(ptr->mnemonic,com)==0){
			printf("opcode is %X\n",ptr->opcode);
			break;
		}
		else{
			if(ptr->next==NULL){
				printf("no opcode\n");
			}
			ptr=ptr->next;
		}
	}
}
