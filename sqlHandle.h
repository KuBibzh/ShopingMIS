#ifndef _SHOPINGMIS_H_
#define _SHOPINGMIS_H_
#include<mysql/mysql.h>
typedef struct {
	int gno;
	char name[20];
	char type[10];
	float price;
	int count;
}goods;
typedef struct{
	char user[20];
	char passwd[20];
	char power[10];
}User;
//设置数据库编码
void SetEncoding(MYSQL* mysql);
//用户注册
int Register(MYSQL* mysql,User* user);
//用户登录
int Login(MYSQL* mysql,User* user);
//增加商品信息
void Insert(MYSQL* mysql,goods* g);
//查找商品信息
void Select(MYSQL* mysql);
//删除商品信息
void Delete(MYSQL* mysql,int gno);
//修改商品信息
void Update(MYSQL* mysql,int count,int gno);


#endif  
