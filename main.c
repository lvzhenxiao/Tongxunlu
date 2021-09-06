#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//���������ṹ��
struct user{
    char name[100];
    char mobile[15];
    char pwd[30];
    int num;
}yonghu[100];

struct note{
    char name[100];
    char mobile[15];
    char email[100];
    int num;
    int is_delete;
}noteInfo[100];

int count=0;
int mcount=0;
int lg=-1;
//��������
int rgist();
int login();

void mobileAdd();
void mobileDelete();
void mobileUpdate();
void mobileQuery();
void mobileStar();
void mobileShouCang();
void mobileBlack();
int checkYongHuMobile();
void inputPwdChange();
void exitSystem();
void initSystem();
int main(){
    int num;
	int p_count=0;
	char input;
	for(num=0;num<=100;num++)
	{
		printf("\n\n\t\t\t&&&&��ӭ����ͨѶ¼����ϵͳ&&&&\n\n");
		printf("\t\t\tϵͳ�����У����Ժ�!!!!");
		for(int j=0;j<p_count;j++)
		{
			printf(".");
		}
		p_count++;
		if(p_count==6)
		{
			p_count=0;
		}
		for(int i=0;i<8000000;i++){};
		printf("\t\t\t%d%%",num);
		system("cls");
	}
	initSystem();
    while(1){

        printf("@@@@@@@@@@@@\n");
        printf("[A]ע��\n[B]��¼\n[C]�ر�ϵͳ\n");
        printf("@@@@@@@@@@@@\n");
        fflush(stdin);
        scanf("%c",&input);
        if(input=='A'||input=='a'){
            int rs=rgist();
            if(rs){
                printf("\n�û�ע��ɹ����û�����%s���绰��%s,�û���ţ�%d",yonghu[count-1].name,yonghu[count-1].mobile,yonghu[count-1].num);
            }else{
                printf("\n�û�ע��ʧ�ܣ���\n");
            }
        }else if(input=='B'||input=='b'){
            int ret=login();
            system("cls");
            if(ret){
                while(1){
                    printf("&&&&&&&&&&&&&&\n");
                    printf("[A]��ӵ绰\n[B]�鿴�绰\n[C]ɾ���绰\n");
                    printf("[D]�˳���¼\n[E]�ر�ϵͳ\n[F]���ڵ绰\n");
                    printf("&&&&&&&&&&&&&&\n");
                    fflush(stdin);
                    scanf("%c",&input);
                    if(input=='A'||input=='a'){
                        mobileAdd();
                    }else if(input=='B'||input=='b'){
                        mobileQuery();
                    }else if(input=='C'||input=='c'){
                        mobileDelete();
                    }else if(input=='D'||input=='d'){
                        lg=-1;
                        break;
                    }else if(input=='E'||input=='e'){
                        exitSystem();
                    }else if(input=='F'||input=='f'){
                        mobileBlack();
                    }else{
                        printf("\n�������󣡣�");
                    }
                    printf("\n���������������������ģ���");
                    getch();
                    system("cls");
                }
            }
        }else if(input=='C'||input=='c'){
            exitSystem();
        }else{
            printf("\n�������󣡣�");
        }
        printf("\n������������˳�����");
        getch();
        system("cls");
    }
}
//��ʼ������
void initSystem(){
    //��ȡȫ�ֱ���
    FILE *file_t;
    char txt[1024];
    file_t=fopen("data.txt","r");
    fgets(txt,1024,file_t);
    sscanf(txt,"count=%d,mcount=%d",&count,&mcount);
    fclose(file_t);

    //��ȡ�ṹ������
    FILE *file;
    FILE *file_n;
    file=fopen("data_y.dat","rb");
    for(int i=0;i<count;i++){
        fread(&yonghu[i],sizeof(yonghu),1,file);
    }
    fclose(file);
    file_n=fopen("data_n.dat","rb");
    for(int i=0;i<mcount;i++){
        fread(&noteInfo[i],sizeof(noteInfo),1,file_n);
    }
    fclose(file_n);
}


//���������˳�ϵͳ
void exitSystem(){
    //����ṹ������
    FILE *file;
    FILE *file_n;
    file=fopen("data_y.dat","wb");
    for(int i=0;i<count;i++){
        fwrite(&yonghu[i],sizeof(yonghu),1,file);
    }
    fclose(file);
    file_n=fopen("data_n.dat","wb");
    for(int i=0;i<mcount;i++){
        fwrite(&noteInfo[i],sizeof(noteInfo),1,file_n);
    }
    fclose(file_n);
    //����ȫ�ֱ���
    FILE *file_t;
    char txt[1024];
    sprintf(txt,"count=%d,mcount=%d",count,mcount);
    file_t=fopen("data.txt","w");
    fputs(txt,file_t);
    fclose(file_t);
    exit(0);
}

int rgist(){
    char confirm_pwd[30];
    printf("\n������������");
    fflush(stdin);
    scanf("%s",yonghu[count].name);
    while(1){
        printf("\n���������룺");
        fflush(stdin);
        //scanf("%s",yonghu[count].pwd);
        inputPwdChange(yonghu[count].pwd);
        printf("%s",yonghu[count].pwd);
        printf("\n������ȷ�����룺");
        fflush(stdin);
        //scanf("%s",&confirm_pwd);
        inputPwdChange(&confirm_pwd);
        if(strcmp(yonghu[count].pwd,confirm_pwd)==0){
            break;
        }else{
            printf("\nȷ�����������벻��ͬ������");
        }
    }

    while(1){
        printf("\n������绰��");
        fflush(stdin);
        scanf("%s",yonghu[count].mobile);
        int rs=checkYongHuMobile(yonghu[count].mobile);
        if(rs==0){
            break;
        }else{
            printf("\n���ֻ����Ѵ��ڣ����������룺");
        }
    }
    yonghu[count].num=count;
    count++;
    return 1;
}
//���봦��
void inputPwdChange(char pwd[30]){
    int i=0;
    while(1){
        char word=getch();
        if(word!='\r'){
            if(word!='\b'){
                pwd[i]=word;
                printf("*");
                i++;
            }else{
                if(strlen(pwd)>0){
                    printf("\b \b");
                    i--;
                }
            }
        }else{
            if(strlen(pwd)<6){
                i=0;
                printf("\n���볤�Ȳ���С����λ������");
            }else{
                break;
            }
        }
    }
    printf("\n");
    pwd[i]='\0';
}

//��֤�û��绰����Ψһ��
int checkYongHuMobile(char mobile[15]){
    int flag=0;
    for(int i=0;i<count;i++){
        if(strcmp(yonghu[i].mobile,mobile)==0){
            flag=1;
        }
    }
    return flag;
}

int login(){
    char mobile[100];
    char pwd[15];
    int flag=0;
    for(int i=0;i<3;i++){\
        printf("\n������绰:");
        fflush(stdin);
        scanf("%s",&mobile);
        printf("\n���������룺");
        fflush(stdin);
        //scanf("%s",&pwd);
        inputPwdChange(&pwd);
        for(int i=0;i<count;i++){
            //printf("%s-%s,%s-%s",yonghu[i].mobile,mobile,yonghu[i].pwd,pwd);
            if(strcmp(yonghu[i].mobile,mobile)==0 && strcmp(yonghu[i].pwd,pwd)==0){
                flag=1;
                lg=i;
                break;
            }
        }
        if(flag==0){
            printf("\n�û�����������󣡣���");
        }else{
             break;
        }
        if(i==2){
            printf("\n������Ĵ����������ޣ�����������������");
        }
    }

    return flag;
}

void mobileAdd(){
    printf("\n������������");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].name);
    printf("\n������绰��");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].mobile);
    printf("\n�������û����䣺");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].email);
    noteInfo[mcount].num=yonghu[lg].num;
    mcount++;
}
/**
*ɾ���绰��Ϣ
*/
void mobileDelete(){
    char mobile[100];
    printf("\n������Ҫɾ�����ֻ���:");
    fflush(stdin);
    scanf("%s",&mobile);
    //����Ҫɾ�����ֻ���
    int find=0;
    for(int i=0;i<mcount;i++){
        if(noteInfo[i].num==yonghu[lg].num &&strcmp(mobile,noteInfo[i].mobile)==0){
            find=1;
        }
        if(find==1){
            noteInfo[i]=noteInfo[i+1];
        }
    }
    if(find==1){
        mcount--;
        find=0;
        printf("\n���ֻ���ɾ���ɹ����ֻ��ţ�%s ",mobile);
    }else{
        printf("\nɾ�����ֻ��Ų�����!!!");
    }
}
void mobileUpdate();
void mobileQuery(){
    for(int i=0;i<mcount;i++){
        if(noteInfo[i].num==yonghu[lg].num){
            printf("\n�û���Ϣ���û�����%s���绰��%s,���䣺%s",noteInfo[i].name,noteInfo[i].mobile,noteInfo[i].email);
        }
    }
}
void mobileStar();
void mobileShouCang();
/**
*���ڵ绰
*/
void mobileBlack(){
 char mobile[100];
    printf("\n��������Ҫ���ڵ��ֻ���:");
    fflush(stdin);
    scanf("%s",&mobile);
    //����Ҫ���ڵ��ֻ���
    int find=0;
    for(int i=0;i<mcount;i++){
        if(noteInfo[i].num==yonghu[lg].num &&strcmp(mobile,noteInfo[i].mobile)==0){
            find=1;
        }
        if(find==1){
            noteInfo[i]=noteInfo[i+1];
        }
    }
    if(find==1){
        mcount--;
        find=0;
        printf("\n���ֻ������ڳɹ����ֻ��ţ�%s ",mobile);
    }else{
        printf("\n���ڵ��ֻ��Ų����ڣ�����");
    }
}
