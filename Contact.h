#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

//#define MAX 1000

#define DEFAULT_CAPACITY 3//Ĭ������

#define MAX_NAME 20
#define MAX_SEX 6
#define MAX_TELE 12
#define MAX_ADDR 30

//���Ѹ�����Ϣ
typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;
//ͨѶ¼
typedef struct Contact
{
	struct PeoInfo* data;//ָ�򿪱ٵĿռ�
	int size;//��¼��ǰ���еĸ���
	int Capacity;//��¼��ǰ�������
}Contact;

enum Option//���ӿɶ���
{
	EXIT,//0
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

//��ʼ��ͨѶ¼
void InitContact(Contact* con);

//���Ӻ�����Ϣ
void AddContact(Contact* con);

//��ʾ������Ϣ
void ShowContact(const Contact* con);

//ɾ��������Ϣ
void DelContact(Contact* con);

//����ͨѶ¼
void Destory_Contact(Contact* con);

//���Һ�����Ϣ
void SearchContact(const Contact* con);

//�޸ĺ�����Ϣ
void ModifyContact(Contact* con);

//���������Ϣ
void SortContact(Contact* con);