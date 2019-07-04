#pragma once
#include <iostream>
using namespace std;
#define str_size 20
#ifndef YJJ_H
#define YJJ_H

typedef struct user_table/*�û�ģ������*/
{
	char cName[str_size];/*�û���*/
	char secret[str_size];/*�û�����*/
	int group_num; /*�����û���*/
	struct user_table *next;/*ָ�򱾽ṹ�����͵�ָ������*/
}user;

typedef struct object_model /*����ģ��*/
{
	char oName[str_size]; /*������*/
	int permission; /*����(r)���޸�(w)������Ȩ��(x)*/
	struct object_model *next; 
}myobj;


/*
�������ã�����û�
�������������û��顢����
���أ�1(�ɹ�),0��ʧ�ܣ�
*/
int add_user(char* name, int group, char* secret);
/*
�������ã���ʼ���û���
��������
���أ�1���ɹ���
*/
int init();
/*
�������ã���Ӷ�����޸Ķ���
�������������������û�������Ȩ��(rwx)
���أ�1(��һ������ɹ�)2(add�ɹ�)3(�޸ĳɹ�)
*/
int add_ob(char* name, int group, int permission);
/*
�������ã��û�������
�������û�����������
���أ�1(�ɹ�) 0���û������ڣ�2(��Ȩ��)3(���󲻿ɼ�)
*/
int user_read(char* user_name, char* ob_name);
/*
�������ã��û�д����
�������û�����������
���أ�1(�ɹ�) 0���û������ڣ�2(��Ȩ��)3(���󲻿ɼ�)
*/
int user_write(char* user_name, char* ob_name);
/*
�������ã��û����ж���
�������û�����������
���أ�1(�ɹ�) 0���û������ڣ�2(��Ȩ��)3(���󲻿ɼ�)
*/
int user_execute(char* user_name, char* ob_name);
/*
�������ã���ʾ�û������������ã�
��������
���أ���
*/
void show_fun(void);
/*
��������user_log
�������ã��û���¼
�������û���������
���أ�1(�ɹ�) 0���û������ڣ�2(�������)
*/
int user_log(char* user_name, char* secret);
#endif
