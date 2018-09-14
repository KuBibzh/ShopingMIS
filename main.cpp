#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<regex>
#include<iostream>
#include<mysql/mysql.h>
#include"mysqlCon.h"
#include"sqlHandle.h"
void UserLogin();
int UIDisplay();
void UserRegister();
void UserDel();
void UIGoods();
void UICost();
void GoodsInsert();
void GoodsUpdate();
void GoodsDelete();
void GoodsSelect();
MYSQL mysql;
User user;
int main(){
	while(1){
		UserLogin();
		if(!UIDisplay()){
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
		if(!std::regex_match(user.user,std::regex("^.{4,12}$"))){
			printf("用户名格式不正确，请重新输入\n");
			continue;
		}
		printf("请输入你的密码：");
		scanf("%s",user.passwd);
		if(!std::regex_match(user.passwd,std::regex("^.{5,10}$"))){
              printf("密码格式不正确，请重新输入\n");
              continue;
        }

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
int UIDisplay(){
	while(1){
		int n;
		if(strcmp(user.power,"admin")==0){
			printf("/***********商店管理系统*****************/\n");
			printf("1.进入商品表界面          2.进入销售表界面\n");
			printf("3.添加新的普通用户        4.删除普通用户\n");
			printf("		5.退出程序\n\n\n");
			printf("请输入想要的功能序号：");
			scanf("%d",&n);
			while(getchar()!='\n');
			switch(n){
				case 1:
					UIGoods();
					break;
				case 2:
					//TODO 销售表UI函数
					break;
				case 3:
					UserRegister();
					break;
				case 4:
					UserDel();
					break;
				case 5:
					return 0;
				default:
					printf("一个错误的输入\n");
					break;
			}
		}
		else{
			printf("/***********商店管理系统*****************/\n");
			printf("1.进入商品表界面                2.退出程序\n\n\n");
			printf("请输入想要的功能序号：");
			scanf("%d",&n);
			while(getchar()!='\n');
			switch(n){
				case 1:
					UIGoods();
					break;
				case 2:
					return 0;
				default:
					printf("一个错误的输入\n");
					break;
			}
		}		
	}
}
void UserRegister(){
	system("clear");
	User newUser;
	printf("欢迎来到注册界面\n\n");
	printf("请输入新用户的账号名：");
	scanf("%s",newUser.user);
	getchar();
	if(!std::regex_match(newUser.user,std::regex("^.{4,12}$"))){
              printf("用户名格式不正确，请重新注册\n");
              sleep(3);
			  return;
    }
	printf("请输入新用户的密码:");
	scanf("%s",newUser.passwd);
	if(!std::regex_match(newUser.passwd,std::regex("^.{6,10}$"))){
              printf("密码格式不正确，请重新输入\n");
              sleep(3);
			  return;
    }
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	if(Register(&mysql,&newUser)){
		printf("注册失败，用户名重复\n");
		return;
	}
	printf("注册成功\n");
	MysqlClose(&mysql);
	sleep(3);
}
void UserDel(){
	system("clear");
	printf("删除用户功能界面\n\n");
	char username[20];
	printf("请输入用户名进行删除：");
	scanf("%s",username);
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	if(!UserDelete(&mysql,username)){
		printf("删除失败，不存在此用户\n");
		sleep(3);
		return;
	}
	MysqlClose(&mysql);
	printf("删除用户成功\n");
	sleep(3);
}
void UIGoods(){
	int c;
	while(1){
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
