#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<mysql/mysql.h>
#include<iostream>
#include<regex>
#include"mysqlCon.h"
#include"userDAO.h"
#include"goodsDAO.h"
void main_UserLogin();
int UIDisplay();
void main_UserRegister();
void main_UserDelete();
void UIGoods();
void UICost();
void main_GoodsInsert();
void main_GoodsUpdate();
void main_GoodsDelete();
void main_GoodsSelectAll();
MYSQL mysql;
User user;
int main(){
	while(1){
		main_UserLogin();
		if(!UIDisplay()){
			break;
		}
	}
	return 0;
}
void main_UserLogin(){
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
		if(UserLogin(&mysql,&user)){
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
		system("clear");
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
					main_UserRegister();
					break;
				case 4:
					main_UserDelete();
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
void main_UserRegister(){
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
	if(UserRegister(&mysql,&newUser)){
		printf("注册失败，用户名重复\n");
		return;
	}
	printf("注册成功\n");
	MysqlClose(&mysql);
	sleep(3);
}
void main_UserDelete(){
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
				main_GoodsInsert();
				break;
			case 2:
				main_GoodsDelete();
				break;
			case 3:
				main_GoodsUpdate();
				break;
			case 4:
				main_GoodsSelectAll();
				break;
			case 5:
				return;
			default:
				printf("错误输入\n");
				break;
		}
	}
}
void main_GoodsInsert(){
	goods g;
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
	if(GoodsInsert(&mysql,&g)){
		printf("物品添加成功!\n");
	}
	else
		printf("商品编号重复!\n");
	MysqlClose(&mysql);
	sleep(3);
}
void main_GoodsUpdate(){
	int count,gno;
	printf("欢迎来到修改商品信息界面：\n");
	printf("输入需要修改的水果编号\n");
	scanf("%d",&count);
	while(getchar()!='\n');
	printf("修改后的水果数量\n");
	scanf("%d",&count);
	while(getchar()!='\n');
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	if(GoodsUpdate(&mysql,count,gno))
		printf("更新商品信息成功!\n");
	else
		printf("没有此商品!\n");
	MysqlClose(&mysql);
	sleep(3);
}
void main_GoodsDelete(){
	int gno;
	printf("请输入要删除信息的水果编号\n");
	scanf("%d",&gno);
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	if(GoodsDelete(&mysql,gno)){
		printf("商品删除成功\n");
	}
	else
		printf("没有此编号的商品\n");
	MysqlClose(&mysql);
	sleep(3);
}
void main_GoodsSelectAll(){
	int i=0;
	MysqlCon(&mysql);
	SetEncoding(&mysql);
	goods* good_Infos;
	good_Infos=GoodsSelectAll(&mysql);
	MysqlClose(&mysql);
	if(good_Infos==NULL){
		printf("没有商品信息！\n");
		return;
	}	
	for(i=0;i<good_Infos[i].gno!=0;i++){
		printf("所有商品信息：\n");
		printf("第%d种商品：\n",i);
		printf("商品ID:%d\n",good_Infos[i].gno);		
		printf("商品名字:%s\n",good_Infos[i].name);
		printf("商品类别:%s\n",good_Infos[i].type);
		printf("商品价格:%f\n",good_Infos[i].price);
		printf("商品数量:%d\n",good_Infos[i].count);
	}
	//TODO 可以添加键盘点击时间进行结束查看信息
	sleep(5);
}
