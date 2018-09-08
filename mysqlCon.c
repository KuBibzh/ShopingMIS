#include<stdio.h>
#include"mysqlCon.h"
void MysqlCon(MYSQL* mysql){
	mysql_init(mysql);
	if(!mysql_real_connect(mysql,"localhost","hehe","789789","shoping",0,NULL,0)){
		fprintf(stderr, "Failed to connect to database: Error: %s\n",
				mysql_error(mysql));
		return;
	}
	printf("连接数据库成功\n");
}
void MysqlClose(MYSQL* mysql){
	mysql_close(mysql);
}
