/*================================================================
*   
*   文件名称：userDAO.h
*   创 建 者：baozhenhua(鲍振华)
*   创建日期：2018年09月14日
*   描    述：对用户表的sql语句操作
*
================================================================*/


#ifndef _USERDAO_H_
#define _USERDAO_H_

#include<mysql/mysql.h>


typedef struct{
    char user[20];
    char passwd[20];
    char power[10];
}User;    

//用户登录
int UserLogin(MYSQL* mysql,User* user);
//用户注册
int UserRegister(MYSQL* mysql,User* user);
//删除普通用户
int UserDelete(MYSQL* mysql,const char* username);
//更新用户信息
int UserUpdataName(MYSQL* mysql,const char* old_username,const char* new_username);
int UserUpdataPwd(MYSQL* mysql,const char* username,const char* password);
//查找用户信息
User* UserSelect(MYSQL* mysql,const char* username);
    
    
    
#endif
