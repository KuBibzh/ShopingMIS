#ifndef _MYSQLCON_H_
#define _MYSQLCON_H_
#include<mysql/mysql.h>
//连接数据库并初始化
void MysqlCon(MYSQL* mysql);
//关闭数据库
void MysqlClose(MYSQL* mysql);

void SetEncoding(MYSQL* mysql);



#endif
