/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：userDAO.c
*   创 建 者：baozhenhua(鲍振华)
*   创建日期：2018年09月14日
*   描    述：用户表操作函数的实现
*
================================================================*/


#include<stdio.h>
#include<string.h>
#include"userDAO.h"
int UserLogin(MYSQL* mysql,User* user){
	char sql[1024];
	sprintf(sql,"select * from User where username='%s' and password=md5('%s')  ",user->user,user->passwd);

	if(mysql_query(mysql,sql)){
		fprintf(stderr,"Failed Login: Error: %s\n",mysql_error(mysql));
		exit(1);
	}
	else{
		MYSQL_RES* res=mysql_store_result(mysql);
		MYSQL_ROW row;

		if(row=mysql_fetch_row(res)){
			strcpy(user->power,row[3]);
			return 1;
		}
		else{
			return 0;
		}
	}

}

int UserRegister(MYSQL* mysql,User* user){
	char sql[1024];
	sprintf(sql,"insert into User(username,password) values('%s',md5('%s'))",user->user,user->passwd);
	if(mysql_query(mysql,sql)){
		fprintf(stderr, "Failed to insert to User: Error: %s\n",
				mysql_error(mysql));
		return 0;
	}
	return 1;
}

int UserDelete(MYSQL* mysql,const char* username){
	char sql[1024];
	sprintf(sql,"delete from User where username='%s' and power='normal'",username);
	if(mysql_query(mysql,sql)){
		return 0;

	}
	return 1;
}

int UserUpdataName(MYSQL* mysql,const char* old_username,const char* new_username){
	char sql[1024];
	sprintf(sql,"updata from User set username = '%s' where username = '%s' ",old_username,new_username);
	if(mysql_query(mysql,sql)){
		return 0;
	}
	return 1;

}
int UserUpdataPwd(MYSQL* mysql,const char* username,const char* passwd){
	char sql[1024];
	sprintf(sql,"updata from User set username = '%s' where username = '%s' ",passwd,username);
	if(mysql_query(mysql,sql)){
		return 0;
	}
	return 1;

}

User* UserSelect(MYSQL* mysql,const char* username){
	char sql[1024];
	sprintf(sql,"select * from User where username = '%s'",username);
	if(mysql_query(mysql,sql)){
		fprintf(stderr,"Failed to Select User: Error:%s\n",mysql_error(mysql));
		return NULL;
	}
	else{
		MYSQL_RES* res=mysql_store_result(mysql);
		MYSQL_ROW row=NULL;
		if(row==mysql_fetch_row(res)){
			User* user=(User*)malloc(sizeof(User));
			strcpy(user->user,row[1]);
			strcpy(user->passwd,row[2]);
			strcpy(user->power,row[3]);
			return user;
		}
		return NULL;
	}
}


