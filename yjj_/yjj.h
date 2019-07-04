#pragma once
#include <iostream>
using namespace std;
#define str_size 20
#ifndef YJJ_H
#define YJJ_H

typedef struct user_table/*用户模型链表*/
{
	char cName[str_size];/*用户名*/
	char secret[str_size];/*用户密码*/
	int group_num; /*所属用户组*/
	struct user_table *next;/*指向本结构体类型的指针类型*/
}user;

typedef struct object_model /*对象模型*/
{
	char oName[str_size]; /*对象名*/
	int permission; /*访问(r)、修改(w)、运行权限(x)*/
	struct object_model *next; 
}myobj;


/*
函数作用：添加用户
参数：姓名、用户组、密码
返回：1(成功),0（失败）
*/
int add_user(char* name, int group, char* secret);
/*
函数作用：初始化用户表
参数：无
返回：1（成功）
*/
int init();
/*
函数作用：添加对象或修改对象
参数：对象名、所属用户组名、权限(rwx)
返回：1(第一个对象成功)2(add成功)3(修改成功)
*/
int add_ob(char* name, int group, int permission);
/*
函数作用：用户读对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_read(char* user_name, char* ob_name);
/*
函数作用：用户写对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_write(char* user_name, char* ob_name);
/*
函数作用：用户运行对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_execute(char* user_name, char* ob_name);
/*
函数作用：显示用户表和组表（调试用）
参数：无
返回：无
*/
void show_fun(void);
/*
函数名：user_log
函数作用：用户登录
参数：用户名、密码
返回：1(成功) 0（用户不存在）2(密码错误)
*/
int user_log(char* user_name, char* secret);
#endif
