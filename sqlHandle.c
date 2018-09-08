#include<stdio.h>
#include"sqlHandle.h"

void SetEncoding(MYSQL* mysql){
	mysql_query(mysql,"set names utf8");
}
void Insert(MYSQL* mysql,goods* g){
	char sql[1024];
	sprintf(sql,"insert into goods_Info values(%d,'%s','%s',%f,%d)",g->gno,g->name,g->type,g->price,g->count);
	if(mysql_query(mysql,sql)){
		fprintf(stderr, "Failed to insert to batabase: Error: %s\n",
				mysql_error(mysql));
		return;
	}
	printf("添加成功\n");
}
void Select(MYSQL* mysql){
	char sql[1024];
	sprintf(sql,"select * from goods_Info");
	if(mysql_query(mysql,sql)){
		fprintf(stderr, "Failed to Select batabase: Error: %s\n",
				mysql_error(mysql));
		return;
	}
	else{
		MYSQL_RES* res=mysql_store_result(mysql);
		MYSQL_ROW row;
		while(row=mysql_fetch_row(res)){
			printf("%s %s %s %s %s\n",row[0],row[1],row[2],row[3],row[4]);
		}
		mysql_free_result(res);
	}
}
void Delete(MYSQL* mysql,int gno){
	char sql[1024];
	sprintf(sql,"delete from goods_Info where gno=%d",gno);
	if(mysql_query(mysql,sql)){
		return;

	}
	printf("删除操作成功\n");
}
void Update(MYSQL* mysql,int count,int gno){

	char sql[1024];
	sprintf(sql,"update goods_Info set count=%d where gno=%d",count,gno);
	if(mysql_query(mysql,sql)){
		fprintf(stderr,"Failed to Update database:Error:%s\n",mysql_error(mysql));
		return;

	}
	printf("更新操作成功\n");
}
