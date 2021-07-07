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
    int len;
    symtab *psym;
    int progaddr;char objbuf[10][20];//object파일 로드시 파일 이름 길이 20이하 최대 10개의 obj파일 로드 가능
    int objlen;
    int bptmp;
    bp* ptr;


    //file scan
    FILE *fp=fopen("opcode.txt","r");

    //opcode table
    table=(optable*)malloc(sizeof(optable)*20);

    for(i=0;i<20;i++){
        table[i].head=NULL;
    }


    while(1){
        if(!fgets(line,100,fp)) break;
        sscanf(line,"%x %100[^ \t] %d%*c",&optmp,opcode,&len);
        spcnt+=1;
        opindex=opcodetable_func_make_hash(opcode);
        addopnode(opcode,optmp,opindex,len);
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
            printf("h[elp]\nd[ir]\nq[uit]\nhi[story]\ndu[mp] [start,end]\ne[dit] address, value\nf[ill] start, end, value\nreset\nopcode mnemonic\nopcode list\nassemble filename\ntype filename\nsymbol\n");
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
        else if(strcmp(inp,"assemble")==0){
            if(strcmp(nstr,"assemble")==0||strcmp(nstr,"assemble ")==0 || strcmp(nstr,"assemble\t")==0){
                printf("Error!\n"); continue;
            }
            command=strtok(NULL,"\n");
            fun_assemble(command);
            n+=1; history(nstr,n);
        }

        else if(strcmp(inp,"type")==0){
            if(strcmp(nstr,"type")==0||strcmp(nstr,"type ")==0 || strcmp(nstr,"type\t")==0){
                printf("Error!\n");
                continue;
            }

            command=strtok(NULL,"\n");
            typefile(command);
            n+=1; history(nstr,n);

        }
        else if(strcmp(inp,"symbol")==0){
            //symtab 
            psym=symt;
            while(psym!=NULL){
                printf("\t%s\t%04X\n",psym->symbol,psym->add);
                psym=psym->next;
            }
            n+=1; history(nstr,n);
        }
        else if(strcmp(command,"progaddr")==0){
            command=strtok(NULL," \t\n");
            if(command!=NULL){
                sscanf(command,"%x",&progaddr);
                printf("PROGADDR is set by %6x\n",progaddr);
            }
            else{
                progaddr=0;
                printf("Default progaddr: 0x00.\n");
            }
        }
        else if(strcmp(command,"loader")==0){

            i=0;
            command=strtok(NULL," \t\n");
            while(command!=NULL){
                strcpy(objbuf[i],command);
                i+=1;
                command=strtok(NULL," \t\n");
            }
            objlen=i;
            loader_fun(objbuf,objlen,progaddr,arr);

        }
        else if(strcmp(command,"run")==0){
            //입력에 오류 확인
            if((strcmp(nstr,"run")!=0&&strcmp(nstr,"run ")!=0) && strcmp(nstr,"run\t")!=0){		
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
            //run 실행

        }
        //break point 관련명령어
        else if(strcmp(command,"bp")==0){
            command=strtok(NULL," \t\n");
            //print breakpoints
            if(command==NULL){
                printf("    breakpoint\n");
                printf("    -----------\n");
                ptr=bplist;
                while(ptr!=NULL){
                    printf("    %-10x\n",ptr->item);
                    ptr=ptr->next;
                }
            }
            else{
                //breakpoints clear
                if(strcmp(command,"clear")==0){
                    bpclear();
                }
                else{
                     //new break point
                    sscanf(command,"%x",&bptmp);
                    insertbplist(bptmp);
                    printf("    [ok] create breakpoint %6x\n",bptmp);
                }
            }
        }
        else{
            printf("Wrong instruction.\n");
        }
    }
    //file 닫기
    fclose(fp);
    free(table);
    return 0;
}
void insertbplist(int bptmp)
{
    bp* newb;
    bp* ptr;
    newb=(bp*)malloc(sizeof(bp));
    newb->item=bptmp;
    newb->next=NULL;
    ptr=bplist;
    if(ptr==NULL){
        bplist=newb;
    }
    else{
        while(ptr->next!=NULL)
            ptr=ptr->next;
        ptr->next=newb;
        bplen+=1;
    }
}
void bpclear(){
    bp* ptr;
    while(bplist!=NULL){
        ptr=bplist;
        bplist=bplist->next;
        free(ptr);
        bplen-=1;
    }
    printf("    [ok] clear all breakpoints\n");
    bplen=1;
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
    if((dp=opendir("."))==NULL)
    {
        printf("/sogang/under/cse20141555/sp20141555_proj1를 열 수 없습니다.\n");
    }
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name,&buf);
        strcpy(temp,entry->d_name);
        if(strcmp(temp,".")==0 ||strcmp(temp,"..")==0){//.과 ..은 예외처리
            continue;
        }
        if(S_ISDIR(buf.st_mode)){//directory/ 출력
            printf("%20s/\t",entry->d_name);
            tmp+=1;
            if(tmp%3==0)
                printf("\n");

        }
        else if(S_IEXEC&buf.st_mode){//실행파일* 출력
            printf("%20s*\t",entry->d_name);
            tmp+=1;
            if(tmp%3==0)
                printf("\n");
        }
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
        /*  if(arr[i]/16>=8){
            printf("%02X ",arr[i]&&0x0000ff);//메모리 값들 출력
            }
            else{*/
        printf("%02X ",arr[i]);//메모리 값들 출력
        //   }
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
void addopnode(char*opcode,unsigned int optmp,int opindex,int len)
{

    //opcode table에서 hashing 함수를 통해 발생한 opindex에 해당 opcode와 mnemonic을 새로운 노드로 만들어서 링크드리스트 마지막에 삽입
    opnode *ptr;
    opnode *newo;
    newo=(opnode*)malloc(sizeof(opnode));
    newo->next=NULL;
    newo->opcode=optmp;
    newo->len=len;
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
void typefile(char* finame){
    DIR* dp=NULL;
    struct dirent* entry=NULL;
    struct stat buf;
    char temp[80]; int ch=0;char line[1000];
    FILE *fp2;
    if((dp=opendir("."))==NULL){
        printf("디렉토리를 열 수 없습니다.\n");
    }
    while((entry=readdir(dp))!=NULL)
    {
        lstat(entry->d_name,&buf);
        strcpy(temp,entry->d_name);
        if(strcmp(temp,finame)==0){
            ch=1;
            fp2=fopen(temp,"r");
            break;
        }
    }
    if(ch==0){
        printf("파일이 없습니다.\n");
        return;
    }


    while(1){
        if(!fgets(line,100,fp2)) break;
        printf("%s",line);
    }
    printf("\n");
    fclose(fp2);

}
void fun_assemble(char*command){
    DIR *dp=NULL;
    struct dirent*entry=NULL;
    struct stat buf;
    char temp[80];int i;
    FILE *fp3;FILE *fp4;
    int ch=0;char fircommand[100];char firsymbol[100];
    unsigned int firadd;
    unsigned int locctr;
    char line[1000];char temp3[100]; char copyline[1000];char* temp1;char temp2[100];char opersym[100];char opcodetmp[100];
    int tch=0;int opch;
    char symbol[100]; char opcode[100];char operand[100];char operand2[100];
    int opernum;
    int symch=0;
    int ERROR_FLAG=0;
    char opcodetemp[100];
    char* bytearr;
    FILE *fp5;//intermediate 파일
    FILE *fp6;//listing 파일
    FILE *fp7;//obj 파
    char tmp[80];
    int operandadd;int originadd;int mynextadd;
    int inttmp;int chch=0;
    int diff;
    char file1[100];char file2[100];char operandtmp[100];
    int linenum=5;
    int ni,x,b,p,e;
    int addlen;int bytecnt;
    int modaddtmp[100000];int ecnt=0;char objectcode[1000];int prevlen;

    //command file 열기 
    ERROR_FLAG=0;
    if((dp=opendir("."))==NULL)
    {
        printf("디렉토리를 열수 없습니다.\n");
    }
    while((entry=readdir(dp))!=NULL){
        lstat(entry->d_name,&buf);
        strcpy(temp,entry->d_name);
        if(strcmp(temp,command)==0){
            ch=1;
            fp3=fopen(temp,"r");
            break;
        }
    }
    if(ch==0){
        printf("파일이 없습니다.\n");
        return;
    }


    //    strcpy(file1,command);
    //    strcpy(file2,command);
    fgets(line,1000,fp3);
    //한줄씩 읽음 첫번째줄 따로 변수에 저장 
    sscanf(line,"%s %s %x",firsymbol,fircommand,&firadd);

    insertsymtab(firsymbol,firadd);

    fp4=fopen("inter.txt","w");
    if(strcmp(fircommand,"START")==0){
        locctr=firadd;
        fprintf(fp4,"      %04x%10s%10s%10x\n",locctr,firsymbol,fircommand,firadd);
    }
    else{
        printf("Error! START 명령어에는 label이 필요합니다.\n");
        return;
    }

    //pass 1
    while(1){
        if(ERROR_FLAG==1){
            //printf("line %5d Error\n",linenum);
        }
        linenum+=5;
        ERROR_FLAG=0;
        strcpy(operand2,"\0");
        chch=0;
        if(strcmp(opcode,"END")==0)
            break;
        // END까지 계속읽음 
        tch=0;
        fgets(line,1000,fp3);	
        if(line[0]=='.'){
            fprintf(fp4,"%s",line);
            continue;
        }
        strcpy(copyline,line);
        temp1=strtok(line," \t\n");
        while(temp1!=NULL){	//케이스 나누기 ; OPCH=0이면 SYMBOL 존재 OPCH=1 SYMBOL없음 OPCH=2이면 RSUB OPCH=3이면 END나 BASE 
            tch+=1;
            if(tch==1){
                opch=searchop(temp1);
                if(strcmp(temp1,"RSUB")==0){
                    strcpy(opcode,temp1);
                    opch=2;
                    strcpy(symbol,"\0");strcpy(operand,"\0");
                    break;
                }
                if(strcmp(temp1,"BASE")==0||strcmp(temp1,"END")==0){
                    strcpy(opcode,temp1);
                    strcpy(symbol,"\0");
                    opch=3;
                }
                if(opch==0){
                    if(strrchr(copyline,',')!=NULL)
                        chch=1;
                    strcpy(symbol,temp1);
                }
                else if(opch==1){
                    if(strrchr(copyline,',')!=NULL) 
                        chch=1;
                    strcpy(opcode,temp1);
                    strcpy(symbol,"\0");
                }

            }
            else{
                if(opch==0&&tch==2){
                    if(temp1[0]=='+'){
                        strcpy(temp3,transstring(temp1));
                    }
                    else strcpy(temp3,temp1);
                    if(searchop(temp3)==0&&strcmp(temp3,"BYTE")!=0&&strcmp(temp3,"WORD")!=0&&strcmp(temp3,"RESW")!=0&&strcmp(temp3,"RESB")!=0){
                        ERROR_FLAG=1;
                    }
                    strcpy(opcode,temp1);
                }
                if(opch==0&&tch==3){
                    strcpy(operand,temp1);
                }
                if(opch==1&&tch==2){
                    strcpy(operand,temp1);
                }
                if(opch==3&&tch==2){//END BASE
                    strcpy(operand,temp1);
                }
                if(chch==1&&opch==0&&tch==4){//operand 2개
                    strcpy(operand2,temp1);
                }
                if(chch==1&&opch==1&&tch==3){//operand 2개
                    strcpy(operand2,temp1);
                }
            }
            temp1=strtok(NULL," \t\n,");
        }

        if(opch==0){
            symch=searchsymtab(symbol);
            if(symch==0){
                insertsymtab(symbol,locctr);
            }
            else{
                ERROR_FLAG=1;
            }
        }

        if(strcmp(opcode,"END")==0||strcmp(opcode,"BASE")==0){//END, BASE
            fprintf(fp4,"%3d               %35s%10s\n",opch,opcode,operand);

        }
        else if(opch==0){//3가지 정보
            if(chch==1){
                fprintf(fp4,"%3d %04x%10s%10s%10s,%10s\n",opch,locctr,symbol,opcode,operand,operand2);
            }

            else{
                fprintf(fp4,"%3d %04x%10s%10s%10s\n",opch,locctr,symbol,opcode,operand);
            }
        }
        else if(opch==1){//2가지 정보
            if(chch==0){
                fprintf(fp4,"%3d %04x          %10s%10s\n",opch,locctr,opcode,operand);

            }
            else if(chch==1){
                fprintf(fp4,"%3d %04x          %10s%10s,%10s\n",opch,locctr,opcode,operand,operand2);
            }
        }
        else if(opch==2){//RSUB
            fprintf(fp4,"%3d %04x%35s\n",opch,locctr,opcode);
        }		
        if(opch==2){//RSUB
            locctr+=3;
        }
        else if(opch==3)//END BASE
        {
            locctr=locctr;//변화없음
        }
        else if(opch==1||opch==0){

            if(strcmp(opcode,"BYTE")==0){
                //find length
                bytearr=strtok(operand,"'");
                bytearr=strtok(NULL,"'");

                if(operand[0]=='X'){      
                    if(searchhexa(bytearr)==-1)
                        ERROR_FLAG=1;
                    locctr+=strlen(bytearr)/2;
                }
                else if(operand[0]=='C'){
                    locctr+=strlen(bytearr);
                }
            }
            else if(strcmp(opcode,"WORD")==0){
                locctr+=3;
            }

            else if(strcmp(opcode,"RESW")==0){
                opernum=atoi(operand);
                //opernum=strtol(operand,NULL,16);
                locctr+=3*opernum;
            }

            else if(strcmp(opcode,"RESB")==0){
                opernum=atoi(operand);
                //opernum=strtol(operand,NULL,16);
                locctr+=opernum;
            }
            else{
                if(opcode[0]=='+'){
                    for(i=0;i<strlen(opcode)-1;i++){
                        opcodetemp[i]=opcode[i+1];
                    }
                    opcodetemp[strlen(opcode)-1]='\0';
                    locctr+=(lenfind(opcodetemp)+1);
                }
                else{
                    locctr+=lenfind(opcode);

                }
            }
        }
        else{
            ERROR_FLAG=1;
        }
    }

    fclose(fp3);
    fclose(fp4);
    //pass 2
    fp5=fopen("inter.txt","r");
    strcpy(tmp,".lst");
    command[strlen(command)-4]='\0';
    strcat(command,tmp);
    fp6=fopen(command,"w");

    command[strlen(command)-4]='\0';
    strcat(command,".obj");
    fp7=fopen(command,"w");

    command[strlen(command)-4]='\0';
    //FP6는 LISTING FP7는 OBJ 

    fscanf(fp5,"%d",&inttmp);
    if(inttmp==0)
        fscanf(fp5,"%d %x %s %s %x",&inttmp,&firadd,firsymbol,fircommand,&firadd);
    else{
        fscanf(fp5,"%d %x %s %x",&inttmp,&firadd,fircommand,&firadd);
    }

    linenum=5;
    //printf("%s",line);
    if(strcmp(fircommand,"START")==0){
        if(inttmp==0)
            fprintf(fp6,"%10d    %04X%10s%10s%20x\n",linenum,firadd,firsymbol,fircommand,firadd);
        else
            fprintf(fp6,"%10d    %04X%10s%20x\n",linenum,firadd,fircommand,firadd);

    }
    addlen=locctr-firadd;
    fprintf(fp7,"H%-6s%06X%06X\n",firsymbol,firadd,addlen);
    linenum=0;
    //write obj
    strcpy(opcodetmp,"\0");
    bytecnt=0;
    //INTTMP에 OPCH저장되있음 
    while(1){
        ni=0;x=0;b=0;p=0;e=0;
        linenum+=5;
        if(strcmp(opcodetmp,"END")==0)
            break;
        fgets(line,1000,fp5);
        if(line[0]=='.'){
            //linenum+=5;
            fprintf(fp6,"%10d    %s",linenum,line);
            continue;
        }

        sscanf(line,"%d",&inttmp);
        if(inttmp==2){//RSUB
            sscanf(line,"%d %x %s",&inttmp,&originadd,opcodetmp);
            ni=3;
            fprintf(fp6,"%10d    %04X          %10s                        %02X0000\n",linenum,originadd,opcodetmp,opcodefind(opcodetmp)+ni);   
            if(bytecnt==0){
                fprintf(fp7,"T%06X",originadd);
            }
            if(bytecnt+6>60){
                // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                objectcode[bytecnt]='\0';
                prevlen=strlen(objectcode);
                fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                //fprintf(fp7,"T%06X",originadd);
                //배열 초기화한다
                //현재 opcode를 삽입
                memset(objectcode,'\0',1000);
                bytecnt=0;
                sprintf(objectcode,"T%06X",originadd);
            }
            sprintf(objectcode+bytecnt,"%02X0000",opcodefind(opcodetmp)+ni);
            bytecnt+=6;           

        }
        else if(inttmp==0||inttmp==1)//[symbol] opcode operand
        {
            if(strrchr(line,',')==NULL){//OPERAND가 1개 
                if(inttmp==0)
                {
                    sscanf(line,"%d %x %s %s %s",&inttmp,&originadd,temp2,opcodetmp,opersym);
                    strcpy(operand2,"\0");
                }
                else{
                    sscanf(line,"%d %x %s %s",&inttmp,&originadd,opcodetmp,opersym);
                    strcpy(operand2,"\0");
                }
            }
            else{
                if(inttmp==0){
                    sscanf(line,"%d %x %s %s %100[^,]%*c %s",&inttmp,&originadd,temp2,opcodetmp,opersym,operand2);
                }
                else{
                    sscanf(line,"%d %x %s %100[^,]%*c %s",&inttmp,&originadd,opcodetmp,opersym,operand2);
                }
            }
            /*  if(nonvisit==0){
                fprintf(fp7,"T%06X",originadd);
                nonvisit=1;
                }*/
            //opcode에 +문자 있는 경우 제외
            if(opcodetmp[0]=='+')
            {
                strcpy(opcode,transstring(opcodetmp));
            }
            else
                strcpy(opcode,opcodetmp);
            //operand1에 문자가 써있으면 제외
            if(opersym[0]=='#'||opersym[0]=='@')
            {
                strcpy(operand,transstring(opersym));
            }
            else
                strcpy(operand,opersym);

            //opcode exists in opcodetable
            if(searchop(opcode)!=0)
            {
                if(opcodetmp[0]=='+'){
                    e=1;
                }
                else{
                    e=0;
                }
                //len_opcode=lenfind(opcode);//opcode의 크기조사
                //operand is symbol
                if(searchsymtab(operand)!=0)
                {
                    operandadd=searchsym(operand);
                    mynextadd=originadd+nextaddfind(opcodetmp,opersym);
                    diff=operandadd-mynextadd;
                    if(operand2!=NULL){
                        if(strcmp(operand2,"X")==0){
                            x=1;
                        }
                        else x=0;
                    }
                    else   
                        x=0;
                    if(opersym[0]=='@')
                        ni=2;
                    else if(opersym[0]=='#')
                        ni=1;
                    else
                        ni=3;

                    if(e==1)//FORMAT 4 
                    {
                        b=0;p=0;
                        modaddtmp[ecnt]=originadd+1;
                        ecnt++;

                        if(strcmp(operand2,"\0")==0){
                            if(inttmp==0){
                                fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%05X\n",linenum,originadd,temp2,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,searchsym(operand));
                            }
                            else{
                                fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%05X\n",linenum,originadd,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,searchsym(operand));
                            }
                        }
                        //X REGISTER EXIST 
                        else if(strcmp(operand2,"X")==0){
                            strcpy(operandtmp,opersym);
                            strcat(operandtmp,",");
                            strcat(operandtmp,"X");
                            if(inttmp==0){
                                printf("%04X%10s%10s%10s    %02X%X%05X\n",originadd,temp2,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,searchsym(operand));

                            }
                            else 
                                printf("%04X%10s%10s    %02X%X%05X\n",originadd,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,searchsym(operand));


                        }
                        if(bytecnt==0){
                            fprintf(fp7,"T%06X",originadd);
                        }
                        if(bytecnt+8>60){
                            // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                            objectcode[bytecnt]='\0';
                            prevlen=strlen(objectcode);
                            fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                            //fprintf(fp7,"T%06X",originadd);
                            //배열 초기화한다
                            //현재 opcode를 삽입
                            memset(objectcode,'\0',1000);
                            bytecnt=0;
                            fprintf(fp7,"T%06X",originadd);
                        }
                        sprintf(objectcode+bytecnt,"%02X%X%05X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,searchsym(operand));
                        bytecnt+=8;           

                        //linenum+=5;
                        continue;
                    }

                    //범위 안이면 PC 아니면 B 레지스터 사용 

                    if(diff>=-2048&&diff<=2047){
                        b=0;p=1;
                        if(diff<0){
                            diff=diff&0x000fff;
                        }
                    }
                    else{
                        b=1;p=0;
                        diff=operandadd-base;
                    }
                    if(opersym[0]!='@'&&opersym[0]!='#')
                    {
                        //n=1,i=1
                        ni=3;
                        if(inttmp==0)//symbol opcode operand
                        {
                            if(strcmp(operand2,"\0")==0){
                                fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%03X\n",linenum,originadd,temp2,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                            }
                            else if(strcmp(operand2,"X")==0){
                                if(b==1&&p==0){
                                    diff=searchsym(operand)-base;
                                }   
                                strcpy(operandtmp,opersym);
                                strcat(operandtmp,",");
                                strcat(operandtmp,operand2);

                                fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%03X\n",linenum,originadd,temp2,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                            }
                        }
                        else if(inttmp==1){//opcode operand
                            if(strcmp(operand2,"\0")==0){
                                fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%03X\n",linenum,originadd,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                            }
                            else if(strcmp(operand2,"X")==0){
                                if(b==1&&p==0)
                                    diff=searchsym(operand)-base;
                                strcpy(operandtmp,opersym);
                                strcat(operandtmp,",");
                                strcat(operandtmp,operand2);
                                fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%03X\n",linenum,originadd,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                            }
                        }
                        if(bytecnt==0){
                            fprintf(fp7,"T%06X",originadd);
                        }
                        if(bytecnt+6>60){
                            // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                            objectcode[bytecnt]='\0';
                            prevlen=strlen(objectcode);
                            fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                            //fprintf(fp7,"T%06X",originadd);
                            //배열 초기화한다
                            //현재 opcode를 삽입
                            memset(objectcode,'\0',1000);
                            bytecnt=0;
                            fprintf(fp7,"T%06X",originadd);
                        }
                        sprintf(objectcode+bytecnt,"%02X%X%03X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        bytecnt+=6;           


                    }
                    else if(opersym[0]=='@'){//POINTER INDERECT ADD
                        ni=2;
                        if(inttmp==0){
                            fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%03X\n",linenum,originadd,temp2,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        }
                        else if(inttmp==1){
                            fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%03X\n",linenum,originadd,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        }
                        if(bytecnt==0){
                            fprintf(fp7,"T%06X",originadd);
                        }
                        else if(bytecnt+6>60){
                            // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                            objectcode[bytecnt]='\0';
                            prevlen=strlen(objectcode);
                            fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                            //fprintf(fp7,"T%06X",originadd);
                            //배열 초기화한다
                            //현재 opcode를 삽입
                            memset(objectcode,'\0',1000);
                            bytecnt=0;
                            fprintf(fp7,"T%06X",originadd);
                        }
                        sprintf(objectcode+bytecnt,"%02X%X%03X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        bytecnt+=6;

                    }
                    else if(opersym[0]=='#'){//operand is not a constant
                        ni=1;
                        if(inttmp==0){
                            fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%03X\n",linenum,originadd,temp2,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        }
                        else{
                            fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%03X\n",linenum,originadd,opcodetmp,opersym,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,diff);
                        }
                        if(bytecnt==0){
                            fprintf(fp7,"T%06X",originadd);
                        }
                        else if(bytecnt+6>60){
                            // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                            objectcode[bytecnt]='\0';
                            prevlen=strlen(objectcode);
                            fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                            //fprintf(fp7,"T%06X",originadd);
                            //배열 초기화한다
                            //현재 opcode를 삽입
                            memset(objectcode,'\0',1000);
                            bytecnt=0;
                            fprintf(fp7,"T%06X",originadd);

                        }
                        sprintf(objectcode+bytecnt,"%02X%X%03X",opcodefind(opcodetmp)+ni,x*8+b*4+p*2+e*1,diff);
                        bytecnt+=6;   


                    }
                }
                else{
                    //operand is constant or register
                    if(searchregister(operand)!=-1){
                        //operand is a memory
                        ni=0;

                        if(strcmp(operand2,"X")==0)
                            x=1;
                        x=0;
                        if(inttmp==0){
                            fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%X\n",linenum,originadd,temp2,opcodetmp,opersym,opcodefind(opcode)+ni,searchregister(operand),searchregister(operand2));
                        }
                        else{
                            fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%X\n",linenum,originadd,opcodetmp,opersym,opcodefind(opcode)+ni,searchregister(operand),searchregister(operand2));

                        }
                        if(bytecnt==0){
                            fprintf(fp7,"T%06X",originadd);
                        }
                        else if(bytecnt+4>60){
                            // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                            objectcode[bytecnt]='\0';
                            prevlen=strlen(objectcode);
                            fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                            //fprintf(fp7,"T%06X",originadd);
                            //배열 초기화한다
                            //현재 opcode를 삽입
                            memset(objectcode,'\0',1000);
                            bytecnt=0;
                            fprintf(fp7,"T%06X",originadd);

                        }
                        sprintf(objectcode+bytecnt,"%02X%X%X",opcodefind(opcodetmp)+ni,searchregister(operand),searchregister(operand2));
                        bytecnt+=4;   

                    }
                    else{//operand is a constant
                        ni=1;
                        b=0;p=0;
                        e=0;
                        if(strcmp(operand2,"X")==0)
                            x=1;
                        else
                            x=0;
                        if(x==1){
                            strcpy(operandtmp,opersym);
                            strcat(operandtmp,",");
                            strcat(operandtmp,"X");
                        }
                        else
                            strcpy(operandtmp,opersym);
                        if(opcodetmp[0]=='+')
                            e=1;
                        if(inttmp==0){
                            if(e==1){
                                fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%05X\n",linenum,originadd,temp2,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                if(bytecnt==0){
                                    fprintf(fp7,"T%06X",originadd);
                                }
                                else if(bytecnt+8>60){
                                    // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                                    objectcode[bytecnt]='\0';
                                    prevlen=strlen(objectcode);
                                    fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                                    //fprintf(fp7,"T%06X",originadd);
                                    //배열 초기화한다
                                    //현재 opcode를 삽입
                                    memset(objectcode,'\0',1000);
                                    bytecnt=0;
                                    fprintf(fp7,"T%02X",originadd);
                                }
                                sprintf(objectcode+bytecnt,"%02X%X%05X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                bytecnt+=8;    

                            }
                            else{
                                fprintf(fp6,"%10d    %04X%10s%10s%20s    %02X%X%03X\n",linenum,originadd,temp2,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                if(bytecnt==0){
                                    fprintf(fp7,"T%06X",originadd);
                                }
                                else if(bytecnt+6>60){
                                    // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                                    objectcode[bytecnt]='\0';
                                    prevlen=strlen(objectcode);
                                    fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                                    //fprintf(fp7,"T%06X",originadd);
                                    //배열 초기화한다
                                    //현재 opcode를 삽입
                                    memset(objectcode,'\0',1000);
                                    bytecnt=0;
                                    fprintf(fp7,"T%02X",originadd);

                                }
                                sprintf(objectcode+bytecnt,"%02X%X%03X",opcodefind(opcodetmp)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                bytecnt+=6;   

                            }
                        }
                        else{
                            if(e==1){//FORMAT 4
                                fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%05X\n",linenum,originadd,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                if(bytecnt==0){
                                    fprintf(fp7,"T%06X",originadd);
                                }
                                else if(bytecnt+8>60){
                                    // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                                    objectcode[bytecnt]='\0';
                                    prevlen=strlen(objectcode);
                                    fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);

                                    //fprintf(fp7,"T%06X",originadd);
                                    //배열 초기화한다
                                    //현재 opcode를 삽입
                                    memset(objectcode,'\0',1000);
                                    bytecnt=0;
                                    fprintf(fp7,"T%02X",originadd);
                                }
                                sprintf(objectcode+bytecnt,"%02X%X%05X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                bytecnt+=8;   


                            }
                            else{//FORMAT 4가 아님 
                                fprintf(fp6,"%10d    %04X          %10s%20s    %02X%X%03X\n",linenum,originadd,opcodetmp,operandtmp,opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                if(bytecnt==0){
                                    fprintf(fp7,"T%06X",originadd);
                                }
                                else if(bytecnt+6>60){
                                    // 그 전 줄의 byte수 계산해서 fp7에 T처음주소바이트수 쓰기
                                    objectcode[bytecnt]='\0';
                                    prevlen=strlen(objectcode);
                                    fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);
                                    //fprintf(fp7,"T%06X",originadd);
                                    //배열 초기화한다
                                    //현재 opcode를 삽입
                                    memset(objectcode,'\0',1000);
                                    bytecnt=0;
                                    fprintf(fp7,"T%02X",originadd);
                                }
                                sprintf(objectcode+bytecnt,"%02X%X%03X",opcodefind(opcode)+ni,x*8+b*4+p*2+e*1,atoi(operand));
                                bytecnt+=6;   
                            }
                        }
                    }
                }
            }
            else if(strcmp(opcode,"BYTE")==0||strcmp(opcode,"WORD")==0)
            {
                if(strcmp(opcode,"WORD")==0){
                    fprintf(fp6,"%10d    %04X%10s%10s%20s    %06X\n",linenum,originadd,temp2,opcodetmp,opersym,atoi(operand));
                    bytecnt+=6;
                }
                else{
                    strcpy(temp3,opersym);
                    bytearr=strtok(temp3,"'");
                    bytearr=strtok(NULL,"'");
                    fprintf(fp6,"%10d    %04X%10s%10s%20s    ",linenum,originadd,temp2,opcodetmp,opersym);

                    /* if(opersym[0]=='C'){
                       fprintf(fp6,"%X",atoi(bytearr));
                       printf("%X",atoi(bytearr));
                       }
                       if(opersym[0]=='X'){*/
                    for(i=0;i<strlen(bytearr);i++){
                        if(opersym[0]=='X'){
                            sprintf(objectcode+bytecnt,"%c",bytearr[i]);
                            bytecnt+=1;
                        }
                        if(opersym[0]=='C'){
                            sprintf(objectcode+bytecnt,"%02X",bytearr[i]);
                            bytecnt+=2;
                        }
                    }
                    fprintf(fp6,"\n");
                    // }
                }

            }
            else if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0)
            {
                //objectcode 다음 칸으로
                if(inttmp==0){
                    fprintf(fp6,"%10d    %04X%10s%10s%20s\n",linenum,originadd,temp2,opcodetmp,opersym);

                }
                else{
                    fprintf(fp6,"%10d    %04X%10s%20s\n",linenum,originadd,opcodetmp,opersym);
                }
                objectcode[bytecnt]='\0';
                if(bytecnt!=0){
                    prevlen=strlen(objectcode);
                    fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);
                    memset(objectcode,'\0',1000);
                    bytecnt=0;
                }
            }

        }		
        else if(inttmp==3){	//END OR BASE
            sscanf(line,"%d %s %s",&inttmp,opcodetmp,opersym);
            if(strcmp(opcodetmp,"BASE")==0){
                base=searchsym(opersym);
            }
            fprintf(fp6,"%10d                  %10s%20s\n",linenum,opcodetmp,opersym);
            if(strcmp(opcodetmp,"END")==0){
                objectcode[bytecnt]='\0';
                prevlen=strlen(objectcode);
                fprintf(fp7,"%02X%s\n",prevlen/2,objectcode);
                memset(objectcode,'\0',1000);
                bytecnt=0;
            }
        }
    }

    for(i=0;i<ecnt;i++)
        fprintf(fp7,"M%06X05\n",modaddtmp[i]);
    fprintf(fp7,"E000000\n");

    fclose(fp5);fclose(fp6);
    fclose(fp7);
    strcpy(file1,command);
    strcpy(file2,command);
    file1[strlen(command)-4]='\0';
    file2[strlen(command)-4]='\0';
    strcat(file1,".lst");
    strcat(file2,".obj");
    printf("\toutput file : [%s],[%s]\n",file1,file2);
}
int searchconstant(char *str)
{
    //STR이 CONSTANT로만 이루어져있는지 확인 
    int i;
    for(i=0;i<strlen(str);i++)
    {
        if(str[i]<'0'&&str[i]>'9')
            return -1;
    }
    return 1;
}
char* transstring(char* str)
{
    //앞의 한글자 제외 
    int i;
    char* result;
    result=(char*)malloc(sizeof(char)*100);
    for(i=0;i<strlen(str)-1;i++)
        result[i]=str[i+1];
    result[strlen(str)-1]='\0';
    return result;
}
int searchregister(char *arr)
{
    //레지스터값 조사 
    if(strcmp(arr,"A")==0)
        return 0;
    if(strcmp(arr,"X")==0)
        return 1;
    if(strcmp(arr,"L")==0)
        return 2;
    if(strcmp(arr,"B")==0)
        return 3;
    if(strcmp(arr,"S")==0)
        return 4;
    if(strcmp(arr,"T")==0)
        return 5;
    if(strcmp(arr,"F")==0)
        return 6;
    if(strcmp(arr,"PC")==0)
        return 8;
    if(strcmp(arr,"SW")==0)
        return 9;
    if(strcmp(arr,"\0")==0)
        return 0;
    return -1;
}
int searchop(char* command)
{
    //OPCODE에 속하는지 조사 
    opnode *ptr;
    int index;char temp[100];int i=0;
    if(strcmp(command,"END")==0||strcmp(command,"BASE")==0)
        return 1;
    if(command[0]=='+'){
        for(i=0;i<strlen(command)-1;i++){
            temp[i]=command[i+1];
        }
        index=opcodetable_func_make_hash(temp);
        ptr=table[index].head;
    }
    else{
        index=opcodetable_func_make_hash(command);
        ptr=table[index].head;
    }
    while(ptr!=NULL){
        if(strcmp(ptr->mnemonic,command)==0){
            return 1;
        }
        if(command[0]=='+'&&strcmp(ptr->mnemonic,temp)==0)
            return 1;
        ptr=ptr->next;
    }
    return 0;
}
int opcodefind(char* opcode)
{
    //OPCODE 찾아주기 
    opnode *ptr;
    int index=opcodetable_func_make_hash(opcode);
    ptr=table[index].head;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->mnemonic,opcode)==0)
            return ptr->opcode;
        ptr=ptr->next;
    }
    return -1;
}
int lenfind(char* opcode)//opcode의 크기를 찾아줌
{
    opnode *ptr;
    int index=opcodetable_func_make_hash(opcode);
    ptr=table[index].head;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->mnemonic,opcode)==0){
            return ptr->len;
        }
        ptr=ptr->next;
    }

    return 0;
}
int searchsymtab(char *command)
{
    //SYMTAB에 있는지 조사 

    symtab *ptr;
    ptr=symt;
    if(symt==NULL)
        return 0;
    else{

        while(ptr!=NULL){
            if(strcmp(ptr->symbol,command)==0)
                return 1;
            ptr=ptr->next;
        }
    }

    return 0;

}
void insertsymtab(char *sym,int add)
{
    //SYMTAB에 새로운 SYMBOL 넣기 
    symtab *news;
    symtab *ptr;
    news=(symtab*)malloc(sizeof(symtab));
    news->next=NULL;
    strcpy(news->symbol,sym);
    news->add=add;

    if(symt==NULL){
        symt=news;
    }
    else if(strcmp(symt->symbol,news->symbol)<0){

        news->next=symt;
        symt=news;
    }

    else{
        ptr=symt;
        while(ptr->next!=NULL){
            if(strcmp(ptr->next->symbol,news->symbol)<0)
            {
                news->next=ptr->next;
                ptr->next=news;
                return;
            }
            ptr=ptr->next;
        }
        ptr->next=news;
    }

}
int searchsym(char *sym)
{
    //SYMBOL의 주소 반환 
    symtab *ptr;
    ptr=symt;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->symbol,sym)==0){
            return ptr->add;
        }
        ptr=ptr->next;
    }
    return -1;
}
int nextaddfind(char* opcode,char*operand)
{
    //바로 다음줄의 주소 찾기 
    char *temp;int templen=0;char opcodetemp[100];
    strcpy(opcodetemp,"\0");
    if(opcode[0]=='+')
    {
        strcpy(opcodetemp,transstring(opcode));
        templen=1;
    }
    else
        strcpy(opcodetemp,opcode);
    if(searchop(opcodetemp)!=0)
    {
        templen+=lenfind(opcodetemp);
    }
    else{
        if(strcmp(opcodetemp,"BYTE")==0){
            temp=strtok(operand,"'");
            temp=strtok(NULL,"'");
            templen=strlen(temp);
        }
        if(strcmp(opcodetemp,"WORD")==0){
            templen=3;
        }
    }
    return templen;
}
int searchhexa(char *arr)
{
    //ARR가 HEXADECIMAL NUM 인지 조사 
    int i;
    for(i=0;i<strlen(arr);i++){
        if(!((arr[i]>='0'&&arr[i]<='9')||(arr[i]>='A'&&arr[i]<='Z'))){
            return -1;
        }
    }
    return 1;
}
void loader_fun(char objbuf[10][20],int objlen,int progaddr,unsigned char*arr)
{
    DIR *dp=NULL;
    struct dirent *entry=NULL;
    struct stat buf;
    char temp[80];
    int ch=0;int error=1;
    FILE *fp;
    int i;
    char line[100];char tarr[100];
    int ERROR_FLAG=0;
    int totlen=0;
    int csaddr;int execaddr;
    int tlen;int tmp;int tmp2;
    int linecnt=0;char listnametmp[20]; int listaddtmp;
    list* ptr;
    int mlen,mnum,modadd;char mname[20];
    char rtab[10][100][20];int indextmp;char operator;

    estab=(cs*)malloc(sizeof(cs)*objlen);

    if((dp=opendir("."))==NULL)
    {
        printf("디렉토리를 열 수 없습니다.\n");
    }

    //pass1
    csaddr=progaddr;
    while(1){
        error=1;
        if(ch==objlen)
            break;
        dp=opendir(".");
        while((entry=readdir(dp))!=NULL){
            lstat(entry->d_name,&buf);
            strcpy(temp,entry->d_name);
            if(strcmp(temp,objbuf[ch])==0){
                fp=fopen(temp,"r");
                error=0;
                while(1)
                {
                    fgets(line,100,fp);
                    if(line[0]=='H'){
                        //control section name, starting address, control section length
                        sscanf(line,"%*c%6[^\n]%6x%6x",estab[ch].name,&estab[ch].add,&estab[ch].len);
                        estab[ch].add+=csaddr;
                    }
                    else if(line[0]=='D'){
                        //외부에서 쓰일 수 있는 현재 control section의 symbol
                        linecnt=1;
                        while(1){
                            sscanf(line+linecnt,"%6s",listnametmp);
                            linecnt+=5;
                            sscanf(line+linecnt,"%6x",&listaddtmp);
                            listaddtmp+=csaddr;
                            //searchestab : ESTAB에 이미 symbol name이 존재하면 에러처리하기
                            if(searchestab(listnametmp,objlen)!=-1){
                                printf("%s is already in ESTAB.\n",listnametmp);
                                return;
                            }

                            insertestab(ch,listnametmp,listaddtmp);
                            linecnt+=7;
                            if(line[linecnt]=='\n'||line[linecnt]=='\0'){
                                break;
                            }
                        }
                    }
                    else if(line[0]=='R')
                    {
                        //현재 control section에서 외부로부터 가져오는 symbol
                        linecnt=1;
                        while(1)
                        {
                            sscanf(line+linecnt,"%2d%6[^ \n]",&indextmp,mname);
                            strcpy(rtab[ch][indextmp],mname);
                            linecnt+=8;
                            if(line[linecnt]=='\n'||line[linecnt]=='\0'||line[linecnt-1]=='\n'||line[linecnt-2]=='\n'||line[linecnt-3]=='\n'||line[linecnt-4]=='\n')
                                break;
                        }
                    }
                    else if(line[0]=='E'){
                        csaddr+=estab[ch].len;
                        break;
                    }
                    else
                        continue;
                }
                ch+=1;

            }
        }
        if(error==1){//디렉토리에  .obj파일에 일치하는 이름의 파일이 없음
            printf("%s 파일이 없습니다.\n",objbuf[ch]);
            error=1;
            return;
        }
    }
    if(error==1){
        //return ;
    }
    if(ERROR_FLAG==1){
        //   return;
    }

    //pass2
    ch=0;
    csaddr=progaddr;
    execaddr=progaddr;
    while(1){
        if(ch==objlen)
            break;
        dp=opendir(".");
        while((entry=readdir(dp))!=NULL){
            lstat(entry->d_name,&buf);
            strcpy(temp,entry->d_name);
            if(strcmp(temp,objbuf[ch])==0){
                fp=fopen(temp,"r");
                //파일 읽기 prog.obj 한개씩 
                while(1)
                {
                    fgets(line,100,fp);
                    if(line[0]=='T'){
                        //before modification 
                        sscanf(line,"%*c%6x%2x",&execaddr,&tlen);
                        execaddr+=estab[ch].add;

                        //두 숫자 씩 읽어서 하나로 합친다.
                        for(i=0;i<tlen*2;i++){
                            if(i%2==0||i==0){
                                sscanf(line+9+i,"%1x",&tmp);
                            }
                            else {
                                sscanf(line+9+i,"%1x",&tmp2);
                                tmp=tmp*16+tmp2;
                                tarr[(i-1)/2]=tmp;
                            }
                        }
                        //memory에 modification되기 전의 code를 load
                        for(i=0;i<tlen;i++){
                            arr[i+execaddr]=tarr[i];
                        }
                    }
                    else if(line[0]=='M'){
                        //memory에 load된 내용 modification
                        sscanf(line,"%*c%6x%2x%c%2x",&execaddr,&mlen,&operator,&mnum);
                        execaddr+=estab[ch].add;
                        modadd=0;

                        //+03, -02 등 외부 참조가 estab에서 발견되지 않으면 error 처리
                        if(find_estab_index(objlen,rtab[ch][mnum])==-1 && mnum!=1){
                            printf("Wrong external reference. %s[%c%d] is not in ESTAB.\n",rtab[ch][mnum],operator,mnum);
                            return;
                        }
                        if(mlen==5){
                            //format 4(extended addressing) 8글자 000XXXXX에서 XXXXX가 고쳐져야할 주소이다
                            execaddr-=1;
                            modadd+=(arr[execaddr+1]%16)*65536;
                            modadd+=arr[execaddr+2]*256;
                            modadd+=arr[execaddr+3];
                            //ESTAB에서 mnum에 해당하는 외부기호의 시작주로를 탐색해서 add or sub
                            if(operator=='+'){
                                modadd+=find_estab_index(objlen,rtab[ch][mnum]);
                            }
                            else if(operator=='-'){
                                modadd-=find_estab_index(objlen,rtab[ch][mnum]);
                            }
                            //memory space load
                            arr[execaddr+1]=(arr[execaddr+1]/16)*16+modadd/65536;
                            arr[execaddr+2]=(modadd%65536)/256;
                            arr[execaddr+3]=(modadd%65536)%256;

                        }
                        else if(mlen==6){ 
                            //6글자에 직접 시작주소를 더하거나 빼야함 
                            modadd+=arr[execaddr]*65536;
                            modadd+=arr[execaddr+1]*256;
                            modadd+=arr[execaddr+2];   
                            if(arr[execaddr]<=0){
                                if(arr[execaddr+1]<0){
                                    modadd-=256;
                                }
                            }
                            //mnum이 1인 것은 그 control section의 시작 address add or sub
                            if(mnum==1){
                                if(operator=='+')
                                    modadd+=estab[ch].add;
                                else if(operator=='-')
                                    modadd-=estab[ch].add;
                            }
                            else{
                                //mnum이 1이 아닌 경우로 estab 탐색하여 해당 외부기호의 시작주소를 add or sub
                                if(operator=='+'){
                                    modadd+=find_estab_index(objlen,rtab[ch][mnum]);
                                }
                                else if(operator=='-'){
                                    modadd-=find_estab_index(objlen,rtab[ch][mnum]);
                                } 
                            }
                            //memory에 load
                            if(((modadd%65536)/256)<0){
                                arr[execaddr]=modadd/65536-1;           
                            }
                            else{
                                arr[execaddr]=modadd/65536;
                            }
                            if((modadd%65536)%256<0){
                                arr[execaddr+1]=(modadd%65536)/256 -1;
                                if((modadd%65536)/256==0){
                                    arr[execaddr]-=1;
                                }
                            }
                            else
                                arr[execaddr+1]=(modadd%65536)/256;
                            arr[execaddr+2]=(modadd%65536)%256;
                        }

                    }
                    else if(line[0]=='E'){//exit
                        break;
                    }
                    else if(line[0]=='.')//comment
                        continue;
                }
                ch+=1;
                break;
            }
        }
    }

    //ESTAB print
    printf("control   symbol    address         length\n");
    printf("section   name\n");
    printf("----------------------------------------------\n");
    for(i=0;i<objlen;i++){
        printf("%-10s          %-10X      %04X\n",estab[i].name,estab[i].add,estab[i].len);
        ptr=estab[i].dlist;
        while(ptr!=NULL){
            printf("          %-10s%-10X\n",ptr->name,ptr->listadd);
            ptr=ptr->next;
        }
        totlen+=estab[i].len;
    }
    printf("----------------------------------------------\n");
    printf("                    total length   %04X\n",totlen);

}
int find_estab_index(int objnum,char mname[20])
{
    //estab에서 mname에 해당하는 이름을 가진 control section이나 외부 기호의  address return
    list* ptr;
    int i=0;
    for(i=0;i<objnum;i++)
    {
        ptr=estab[i].dlist;
        while(ptr!=NULL){
            if(strcmp(ptr->name,mname)==0){
                return ptr->listadd;
            }
            ptr=ptr->next;
        }
    }
    return -1;
}   
void insertestab(int ch,char *name,int add)
{
    //ESTAB에 name과 주소를 가지는 외부 기호를 insert
    list*ptr;
    list*newe;
    newe=(list*)malloc(sizeof(list));
    strcpy(newe->name,name);
    newe->listadd=add;
    newe->next=NULL;

    ptr=estab[ch].dlist;
    if(ptr==NULL){
        estab[ch].dlist=newe;
    }
    else{
        while(ptr->next!=NULL)
            ptr=ptr->next;
        ptr->next=newe;
    }
}
int searchestab(char *name,int len)
{
    //ESTAB에 name이 존재하는지 조사. 존재하면 해당 address, 존재하지 않으면 -1 return
    int i;
    list *ptr;

    for(i=0;i<len;i++){
        if(strcmp(estab[i].name,name)==0){
            return estab[i].add;
        }
        else{
            ptr=estab[i].dlist;
            while(ptr!=NULL){
                if(strcmp(ptr->name,name)==0){
                    return ptr->listadd;
                }
                ptr=ptr->next;
            }
        }
    }
    return -1;
}

