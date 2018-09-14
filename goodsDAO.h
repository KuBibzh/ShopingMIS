/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：goodsDAO.h
*   创 建 者：baozhenhua(鲍振华)
*   创建日期：2018年09月14日
*   描    述：商品表的函数声明
*
================================================================*/


#ifndef _GOODSDAO_H_
#define _GOODSDAO_H_
    
#include<mysql/mysql.h>
typedef struct {
    int gno;
    char name[20];
    char type[10];
    float price;
    int count;
}goods;
    
    
//增加商品信息
int GoodsInsert(MYSQL* mysql,goods* g);
//查找全部商品信息
goods* GoodsSelectAll(MYSQL* mysql);
//根据名字查找商品信息
goods* GoodsSelectName(MYSQL* mysql,const char* goodsname);
//根据商品编号删除商品信息
int GoodsDelete(MYSQL* mysql,int gno);
//修改商品信息
int GoodsUpdate(MYSQL* mysql,int count,int gno);
    
    
    
#endif
