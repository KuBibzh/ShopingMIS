/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：goodsDAO.c
*   创 建 者：baozhenhua(鲍振华)
*   创建日期：2018年09月14日
*   描    述：商品表函数实现
*
================================================================*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"goodsDAO.h"

//增加商品信息
int GoodsInsert(MYSQL* mysql,goods* g){
	char sql[1024];
	sprintf(sql,"insert into goods_Info values(%d,'%s','%s',%f,%d)",g->gno,g->name,g->type,g->price,g->count);
	if(mysql_query(mysql,sql)){
		fprintf(stderr, "Failed to insert to batabase: Error: %s\n",
				mysql_error(mysql));
		return 0;
	}
	return 1;
}
//查找全部商品信息
goods* GoodsSelectAll(MYSQL* mysql){
	char sql[1024];
	sprintf(sql,"select * from goods_Info");
	goods* good_Infos=NULL;
	if(mysql_query(mysql,sql)){
		fprintf(stderr, "Failed to Select batabase: Error: %s\n",
				mysql_error(mysql));
		return NULL;
	}
	else{
		MYSQL_RES* res=mysql_store_result(mysql);
		MYSQL_ROW row;
		int rows=mysql_num_rows(res);
		int i=0;
		if(rows==0){
			return NULL;
		}
		else{
			good_Infos=(goods*)malloc(sizeof(goods)*rows);
		}
		for(i=0;i<rows;i++){
			row=mysql_fetch_row(res);
			good_Infos[i].gno=atoi(row[0]);
			good_Infos[i].price=atof(row[3]);
			good_Infos[i].count=atoi(row[4]);
			strcpy(good_Infos[i].name,row[1]);
			strcpy(good_Infos[i].type,row[2]);

		}

		mysql_free_result(res);

	}
	return good_Infos;
}
//根据名字查找商品信息
goods* GoodsSelectName(MYSQL* mysql,const char* goodsname){
	return NULL;
}
//根据商品编号删除商品信息
int GoodsDelete(MYSQL* mysql,int gno){
	char sql[1024];
	sprintf(sql,"delete from goods_Info where gno=%d",gno);
	if(mysql_query(mysql,sql)){
		return 0;

	}
	return 1;
}
//修改商品信息
int GoodsUpdate(MYSQL* mysql,int count,int gno){
	char sql[1024];
	sprintf(sql,"update goods_Info set count=%d where gno=%d",count,gno);
	if(mysql_query(mysql,sql)){
		fprintf(stderr,"Failed to Update database:Error:%s\n",mysql_error(mysql));
		return 0;

	}
	return 1;
}
