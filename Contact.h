#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

//#define MAX 1000

#define DEFAULT_CAPACITY 3//默认容量

#define MAX_NAME 20
#define MAX_SEX 6
#define MAX_TELE 12
#define MAX_ADDR 30

//好友个人信息
typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;
//通讯录
typedef struct Contact
{
	struct PeoInfo* data;//指向开辟的空间
	int size;//记录当前已有的个数
	int Capacity;//记录当前最大容量
}Contact;

enum Option//增加可读性
{
	EXIT,//0
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

//初始化通讯录
void InitContact(Contact* con);

//增加好友信息
void AddContact(Contact* con);

//显示好友信息
void ShowContact(const Contact* con);

//删除好友信息
void DelContact(Contact* con);

//销毁通讯录
void Destory_Contact(Contact* con);

//查找好友信息
void SearchContact(const Contact* con);

//修改好友信息
void ModifyContact(Contact* con);

//排序好友信息
void SortContact(Contact* con);