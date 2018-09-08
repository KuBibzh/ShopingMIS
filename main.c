#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<mysql/mysql.h>
#include"mysqlCon.h"
#include"sqlHandle.h"
void UserLogin();
void UIDisplay();
void UIGoods();
void UICost();
void GoodsInsert();
void GoodsUpdate();
void GoodsDelete();
void GoodsSelect();
MYSQL mysql;
User user;
int main(){
	int n;
	while(1){
		UserLogin();
		UIDisplay();
		printf("请输入你想要选择的编号\n");
		scanf("%d",&n);
		if(n==1){
			UIGoods();
		}
		else if(n==2){

		}
		else{
			printf("错误输出\n");
			break;
		}
	}
	return 0;
}
void UserLogin(){
	while(1){
		printf("请输入你的用户名：");
		scanf("%s",user.user);
		getchar();
		printf("请输入你的密码：");
		scanf("%s",user.passwd);
		MysqlCon(&mysql);
		SetEncoding(&mysql);
		if(Login(&mysql,&user)){
			printf("登录成功\n");
			printf("用户权限%s\n\n\n\n",user.power);
			break;
		}
		printf("用户名密码错误，请重新输入！\n");

		MysqlClose(&mysql);
	}
}
void UIDisplay(){
	if(strcmp(user.power,"admin")==0){
		printf("/***********商店管理系统*****************/\n");
		printf("1.进入商品表界面          2.进入销售表界面\n");
		printf("3.添加新的普通用户        4.删除普通用户\n");
		printf("				5.退出程序\n");
	}
	else{
		printf("/***********商店管理系统*****************/\n");
		printf("1.进入商品表界面                2.退出程序\n");
	}
}
void UIGoods(){
	int c;
	while(1){
		sleep(2);
		system("clear");
		printf("/***********商品表管理*******************/\n");
		printf("1.增加商品信息              2.删除商品信息\n");
		printf("3.修改商品信息              4.查找商品信息\n");
		printf("             5.返回主界面\n");
		printf("请输入选择的功能编号：\n");
		scanf("%d",&c);
		switch(c){
			case 1:
				GoodsInsert();
				break;
			case 2:
				GoodsDelete();
				break;
			case 3:
				GoodsUpdate();
				break;
			case 4:
				GoodsSelect();
				break;
			case 5:
				return;
			default:
				printf("错误输入\n");
				break;
		}
	}
}
void GoodsInsert(){
	goods g;
	//printf("请输入商品编号，名字，类别，价钱，数量\n");
	//scanf("%d %s %s %d %d",&g.gno,g.name,g.type,&g.price,&g.count);
	printf("商品编号：");
	scanf("%d",&g.gno);
	printf("商品名字：");
	scanf("%s",g.name);
	getchar();
	printf("商品类别：");
	scanf("%s",g.type);
	getchar();
	printf("商品价钱：");
	scanf("%f",&g.price);
	printf("商品所剩数量：");
	scanf("%d",&g.count);
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	Insert(&mysql,&g);
	MysqlClose(&mysql);
}
void GoodsUpdate(){
	int count,gno;
	printf("请输入要水果的数量和对应的编号\n");
	scanf("%d %d",&count,&gno);
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	Update(&mysql,count,gno);
	MysqlClose(&mysql);
}
void GoodsDelete(){
	int gno;
	printf("请输入要删除信息的水果编号\n");
	scanf("%d",&gno);
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	Delete(&mysql,gno);
	MysqlClose(&mysql);
}
void GoodsSelect(){
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	Select(&mysql);
	MysqlClose(&mysql);
}
