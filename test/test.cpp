// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//对象名、用户名、密码都是char[str_size]
#include "..\yjj_\yjj.h"
#include <iostream>
using namespace std;

void adduser_interface(); // 管理员添加用户界面
void addob_interface();  // 管理员添加对象界面
void userread_interface(char* username); // 用户读对象界面
void userwrite_interface(char* username); // 用户写对象界面
void userexecute_interface(char* username); // 用户执行对象界面
void userlog_interface(void);  // 用户登录界面
void user_select(char* username); // 用户选择界面


int main()
{
	init();
	int select;

	while (1)
	{
		cout << "请选择操作（1添加用户 2添加或修改对象 3用户登录 6退出 7显示表）：";
		cin >> select;
		switch (select)
		{
		case 1: adduser_interface(); break;
		case 2: addob_interface(); break;
		case 3: userlog_interface(); break;
		case 6: return 0;
		case 7: show_fun(); break;
		default: cout << "未定义" << endl;
			    return 0;
		}

	}
	char a[str_size];
	cin >> a;
	char* b = a;
	cout << b;
	return 0;
}


/*******************添加用户界面函数*****************/
void adduser_interface()
{
	char username[str_size] = "0";
	int group = 0;
	char se[str_size] = "0";
	cout << "开始添加用户......" << endl;
	cout << "username:";
	cin >> username;
	cout << "group:";
	cin >> group;
	cout << "secret:";
	cin >> se;
	if(add_user(username, group, se))
		cout << "用户组: " << group << "下用户: " << username << "添加成功!" << endl;
	else
		cout << "用户组: " << group << "下用户: " << username << "添加失败!" << endl;
	
}
/*******************添加对象界面函数*****************/
void addob_interface()
{
	char obname[str_size] = "0";
	int group = 0;
	int permission = 0;
	cout << "开始添加对象......" << endl;
	cout << "obname: ";
	cin >> obname;
	cout << "group: ";
	cin >> group;
	cout << "permission(0x00000rwx): ";
	cin >> permission;
	switch (add_ob(obname, group, permission))
	{
	case 1: cout << "用户组: "<<group<<"新建第一个对象: "<< obname <<"成功!" << endl; break;
	case 2: cout << "用户组: " << group << "新对象: " << obname << "添加成功!" << endl; break;
	case 3: cout << "用户组: "<<group<<"下对象: "<<obname<<"权限修改成功!" << endl; break;
	default: cout << "未知错误！" << endl;
	}
}
/*******************用户读界面函数*****************/
void userread_interface(char* username)
{
	//char username[str_size] = "0";
	char obname[str_size] = "0";
	cout << "开始读对象......" << endl;
	//cout << "username:";
	//cin >> username;
	cout << "obname: ";
	cin >> obname;
	switch (user_read(username, obname))
	{
		case 0: cout << "用户不存在！" <<endl; break;
		case 1: cout << "读成功！" << endl; break;
		case 2: cout << "无权限！" << endl; break;
		case 3: cout << "对象不可见！" << endl; break;
		default: cout << "未知错误！"<<endl;
	}
	
}
/*******************用户写界面函数*****************/
void userwrite_interface(char* username)
{
	char obname[str_size] = "0";
	cout << "开始写对象......" << endl;
	//cout << "username:";
	//cin >> username;
	cout << "obname: ";
	cin >> obname;
	switch (user_write(username, obname))
	{
	case 0: cout << "用户不存在！" << endl; break;
	case 1: cout << "写成功！" << endl; break;
	case 2: cout << "无权限！" << endl; break;
	case 3: cout << "对象不可见！" << endl; break;
	default: cout << "未知错误！" << endl;
	}
}
/*******************用户运行界面函数*****************/
void userexecute_interface(char* username)
{
	char obname[str_size] = "0";
	cout << "开始运行对象......" << endl;
	//cout << "username:";
	//cin >> username;
	cout << "obname: ";
	cin >> obname;
	switch (user_write(username, obname))
	{
	case 0: cout << "用户不存在！" << endl; break;
	case 1: cout << "运行成功！" << endl; break;
	case 2: cout << "无权限！" << endl; break;
	case 3: cout << "对象不可见！" << endl; break;
	default: cout << "未知错误！" << endl;
	}
}
/*******************用户登录界面函数*****************/
void userlog_interface(void)
{
	char username[str_size] = "0";
	char secret[str_size] = "0";
	cout << "开始用户登录......" << endl;
	cout << "username: ";
	cin >> username;
	cout << "secret: ";
	cin >> secret;
	switch (user_log(username, secret))
	{
	case 1: cout << "用户: "<<username<<"登录成功!" << endl; 
			user_select(username);  // 传入用户名
			break;
	case 0: cout << "用户不存在！" << endl; break;
	case 2: cout << "密码错误！" << endl; break;
	default: cout << "未知错误！" << endl;
	}
}
/*******************用户选择界面函数*****************/
void user_select(char* username)
{
	int select2;
	while (true)
	{
		cout << "请选择操作（1读对象 2写对象 3运行对象 6用户注销）：";
		cin >> select2;
		switch (select2)
		{
		case 1: userread_interface(username); break;
		case 2: userwrite_interface(username); break;
		case 3: userexecute_interface(username); break;
		case 6: return;
		default: cout << "未知错误！" << endl;
			     return;
		}
	}
	
}



