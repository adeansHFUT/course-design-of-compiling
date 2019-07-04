// yjj.cpp : 定义静态库的函数。
//
#include "pch.h"
#include "framework.h"
#include "yjj.h"
#include <string.h>
#include <stdio.h>

user* user_head; /*用户表头*/
myobj* group_table[5] = { NULL,NULL,NULL,NULL,NULL }; /*用户组表（访问控制表）*/
/*
函数名：init
函数作用：初始化用户表
参数：无
返回：1（成功）
*/
int init() 
{
	//extern user* user_head;
	user_head = (user*)malloc(sizeof(user));
	char name[str_size] = "yjj";
	char secret[str_size] = "123";
	memcpy(user_head->cName, name, sizeof(char) * str_size);
	user_head->group_num = 0;
	memcpy(user_head->secret, secret, sizeof(char) * str_size);
	user_head->next = NULL;
	return 1;
}
/*
函数名：add_user
函数作用：添加用户
参数：姓名、用户组、密码
返回：1(成功),0（失败）
*/
int add_user(char *name, int group, char *secret)
{
	//extern user* user_head;
	user *t = user_head, *in;
	if (t == NULL)
		return 0;
	while (t->next != NULL) 
	{
		t = t->next;
	}
	in = (user*)malloc(sizeof(user));
	memcpy(in->cName, name, sizeof(char) * str_size);
	in->group_num = group;
	memcpy(in->secret, secret, sizeof(char) * str_size);
	in->next = NULL;
	t->next = in;
	return 1;

}
/*
函数名：add_ob
函数作用：添加对象或修改对象
参数：对象名、所属用户组名、权限(rwx)
返回：1(第一个对象成功)2(add成功)3(修改成功)
*/
int add_ob(char* name, int group, int permission)
{
	if (group_table[group] == NULL) // 该用户组的第一个对象
	{
		group_table[group] = (myobj*)malloc(sizeof(myobj));
		memcpy(group_table[group]->oName, name, sizeof(char) * str_size);
		group_table[group]->permission = permission;
		group_table[group]->next = NULL;
		return 1;
	}
	else
	{
		myobj* in = group_table[group];
		while (in != NULL && strcmp(in->oName, name)) // 是否该对象节点已经存在，存在则修改(strcmp函数相等则返回0)
			in = in->next;
		if(in != NULL ) // 对象已存在
		{
			memcpy(in->oName, name, sizeof(char) * str_size);
			in->permission = permission;
			return 3;
		}
		else // 对象要新建
		{
			in = group_table[group];
			while (in->next != NULL)    // 找到最后一个节点
				in = in->next;
			myobj* t = (myobj*)malloc(sizeof(myobj));
			memcpy(t->oName, name, sizeof(char) * str_size);
			t->permission = permission;
			t->next = NULL;
			in->next = t;
			return 2;
		}
		
	}
	
}
/*
函数名：show_fun
函数作用：显示用户表和组表（调试用）
参数：无
返回：无
*/
void show_fun(void)
{
	user* t = user_head;
	cout << "------------用户表------------" << endl;
	while (t != NULL)
	{
		cout << "用户名：" << t->cName << " 所在组：" << t->group_num << " 密码：" << t->secret << endl;
		t = t->next;
	}
	cout << "------------用户组表(访问控制表)------------" << endl;
	for (int i = 0; i < 5; i++)
	{
		if (group_table[i] != NULL)
		{
			myobj* j = group_table[i];
			cout << "组号："<<i;
			while (j != NULL)
			{
				cout << "---->对象名：" << j->oName << " 权限：" << j->permission;
				j = j->next;
			}
			cout << endl;
		}
	}
}
/*
函数名：user_log
函数作用：用户登录
参数：用户名、密码
返回：1(成功) 0（用户不存在）2(密码错误)
*/
int user_log(char* user_name, char* secret)
{
	user* p_user = user_head;
	while (p_user != NULL && strcmp(p_user->cName, user_name))
		p_user = p_user->next;
	if (p_user == NULL)
		return 0; // 用户不存在
	else
	{
		if (strcmp(p_user->secret, secret) == 0) // 密码符合
			return 1;
		else
			return 2; // 密码错误
	}
}
/*
函数名：user_read
函数作用：用户读对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_read(char* user_name, char* ob_name)
{
	user* p_user = user_head;
	while (p_user != NULL && strcmp(p_user->cName, user_name))
		p_user = p_user->next;
	if (p_user == NULL)
		return 0;  // 用户不存在
	else
	{
		myobj* t = group_table[p_user->group_num];
		while (t != NULL && strcmp(t->oName, ob_name))
			t = t->next;
		if (t == NULL)
			return 3;  //没有此对象
		else
		{
			if (t->permission & 0x04)
				return 1;   // 有读权限，第三位为1
			else
				return 2;   // 无读权限
		}
	}
}

/*
函数名：user_write
函数作用：用户写对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_write(char* user_name, char* ob_name)
{
	user* p_user = user_head;
	while (p_user != NULL && strcmp(p_user->cName, user_name))
		p_user = p_user->next;
	if (p_user == NULL)
		return 0;  // 用户不存在
	else
	{
		myobj* t = group_table[p_user->group_num];
		while (t != NULL && strcmp(t->oName, ob_name))
			t = t->next;
		if (t == NULL)
			return 3;  //没有此对象
		else
		{
			if (t->permission & 0x02)
				return 1;   // 有写权限，第二位为1
			else
				return 2;   // 无权限
		}
	}
}
/*
函数名：user_execute
函数作用：用户运行对象
参数：用户名、对象名
返回：1(成功) 0（用户不存在）2(无权限)3(对象不可见)
*/
int user_execute(char* user_name, char* ob_name)
{
	user* p_user = user_head;
	while (p_user != NULL && strcmp(p_user->cName, user_name))
		p_user = p_user->next;
	if (p_user == NULL)
		return 0;  // 用户不存在
	else
	{
		myobj* t = group_table[p_user->group_num];
		while (t != NULL && strcmp(t->oName, ob_name))
			t = t->next;
		if (t == NULL)
			return 3;  //没有此对象
		else
		{
			if (t->permission & 0x01)
				return 1;   // 有运行权限，第一位为1
			else
				return 2;   // 无权限
		}
	}
}
