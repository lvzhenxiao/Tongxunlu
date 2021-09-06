#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//创建两个结构体
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
//方法声明
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
		printf("\n\n\t\t\t&&&&欢迎进入通讯录管理系统&&&&\n\n");
		printf("\t\t\t系统加载中，请稍候!!!!");
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
        printf("[A]注册\n[B]登录\n[C]关闭系统\n");
        printf("@@@@@@@@@@@@\n");
        fflush(stdin);
        scanf("%c",&input);
        if(input=='A'||input=='a'){
            int rs=rgist();
            if(rs){
                printf("\n用户注册成功，用户名：%s、电话：%s,用户编号：%d",yonghu[count-1].name,yonghu[count-1].mobile,yonghu[count-1].num);
            }else{
                printf("\n用户注册失败！！\n");
            }
        }else if(input=='B'||input=='b'){
            int ret=login();
            system("cls");
            if(ret){
                while(1){
                    printf("&&&&&&&&&&&&&&\n");
                    printf("[A]添加电话\n[B]查看电话\n[C]删除电话\n");
                    printf("[D]退出登录\n[E]关闭系统\n[F]拉黑电话\n");
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
                        printf("\n输入有误！！");
                    }
                    printf("\n请输入任意键进入个人中心！！");
                    getch();
                    system("cls");
                }
            }
        }else if(input=='C'||input=='c'){
            exitSystem();
        }else{
            printf("\n输入有误！！");
        }
        printf("\n请输入任意键退出！！");
        getch();
        system("cls");
    }
}
//初始化数据
void initSystem(){
    //读取全局变量
    FILE *file_t;
    char txt[1024];
    file_t=fopen("data.txt","r");
    fgets(txt,1024,file_t);
    sscanf(txt,"count=%d,mcount=%d",&count,&mcount);
    fclose(file_t);

    //读取结构体数据
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


//保存数据退出系统
void exitSystem(){
    //保存结构体数据
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
    //保存全局变量
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
    printf("\n请输入姓名：");
    fflush(stdin);
    scanf("%s",yonghu[count].name);
    while(1){
        printf("\n请输入密码：");
        fflush(stdin);
        //scanf("%s",yonghu[count].pwd);
        inputPwdChange(yonghu[count].pwd);
        printf("%s",yonghu[count].pwd);
        printf("\n请输入确认密码：");
        fflush(stdin);
        //scanf("%s",&confirm_pwd);
        inputPwdChange(&confirm_pwd);
        if(strcmp(yonghu[count].pwd,confirm_pwd)==0){
            break;
        }else{
            printf("\n确认密码与密码不相同！！！");
        }
    }

    while(1){
        printf("\n请输入电话：");
        fflush(stdin);
        scanf("%s",yonghu[count].mobile);
        int rs=checkYongHuMobile(yonghu[count].mobile);
        if(rs==0){
            break;
        }else{
            printf("\n该手机号已存在，请重新输入：");
        }
    }
    yonghu[count].num=count;
    count++;
    return 1;
}
//密码处理
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
                printf("\n密码长度不能小于六位！！！");
            }else{
                break;
            }
        }
    }
    printf("\n");
    pwd[i]='\0';
}

//验证用户电话号码唯一性
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
        printf("\n请输入电话:");
        fflush(stdin);
        scanf("%s",&mobile);
        printf("\n请输入密码：");
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
            printf("\n用户名或密码错误！！！");
        }else{
             break;
        }
        if(i==2){
            printf("\n您输入的次数超出上限，请明天再来！！！");
        }
    }

    return flag;
}

void mobileAdd(){
    printf("\n请输入姓名：");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].name);
    printf("\n请输入电话：");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].mobile);
    printf("\n请输入用户邮箱：");
    fflush(stdin);
    scanf("%s",noteInfo[mcount].email);
    noteInfo[mcount].num=yonghu[lg].num;
    mcount++;
}
/**
*删除电话信息
*/
void mobileDelete(){
    char mobile[100];
    printf("\n请输入要删除的手机号:");
    fflush(stdin);
    scanf("%s",&mobile);
    //查找要删除的手机号
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
        printf("\n该手机号删除成功！手机号：%s ",mobile);
    }else{
        printf("\n删除的手机号不存在!!!");
    }
}
void mobileUpdate();
void mobileQuery(){
    for(int i=0;i<mcount;i++){
        if(noteInfo[i].num==yonghu[lg].num){
            printf("\n用户信息，用户名：%s、电话：%s,邮箱：%s",noteInfo[i].name,noteInfo[i].mobile,noteInfo[i].email);
        }
    }
}
void mobileStar();
void mobileShouCang();
/**
*拉黑电话
*/
void mobileBlack(){
 char mobile[100];
    printf("\n请输入您要拉黑的手机号:");
    fflush(stdin);
    scanf("%s",&mobile);
    //查找要拉黑的手机号
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
        printf("\n该手机号拉黑成功！手机号：%s ",mobile);
    }else{
        printf("\n拉黑的手机号不存在！！！");
    }
}
