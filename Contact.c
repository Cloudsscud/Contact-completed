#include "Contact.h"

void LoadContact(Contact* con);
//初始化通讯录
void InitContact(Contact* con)
{
	assert(con);
	//现在我们要求：该通讯录起始只有默认容量个好友位，当达到好友上限时增加两个好友位
	con->data = (PeoInfo*)malloc(DEFAULT_CAPACITY * sizeof(PeoInfo));//初始化（空白化）好友信息
	if (con->data == NULL)
	{
		return;
	}
	con->size = 0;//初始化已有好友数
	con->Capacity = DEFAULT_CAPACITY;//初始化默认容量

	//加载已保存的好友信息
	LoadContact(con);
}

//输出对应下标元素信息
void PrintInfo(const Contact* con, int cmp)
{
	printf("%-20s\t%-4d\t%-6s\t%-12s\t%-30s\n",
		con->data[cmp].name,
		con->data[cmp].age,
		con->data[cmp].sex,
		con->data[cmp].tele,
		con->data[cmp].addr);
}

//输出信息的菜单
static void PrintMenu()
{
	printf("%-20s\t%-4s\t%-6s\t%-12s\t%-30s\n", "名字", "年龄", "性别", "电话", "地址");
}

//在对应下标输入元素信息
void InputInfo(Contact* con, int cmp)
{
	printf("请输入名字:> ");
	scanf("%s", con->data[cmp].name);
	printf("请输入年龄:> ");
	scanf("%d", &(con->data[cmp].age));
	printf("请输入性别:> ");
	scanf("%s", con->data[cmp].sex);
	printf("请输入电话:> ");
	scanf("%s", con->data[cmp].tele);
	printf("请输入地址:> ");
	scanf("%s", con->data[cmp].addr);
}

//判断好友是否为空
int Whether(const Contact* con)
{
	if (con->size == 0)
	{
		printf("当前无好友，请先添加好友!\n");
		return 0;
	}
	return 1;
}

//检测是否满容		满容=>增加空间,否则不进行操作
void Check_Capacity(Contact* con)
{
	assert(con);
	if (con->size == con->Capacity)
	{
		//已满
		PeoInfo* ptr = (PeoInfo*)realloc(con->data, ((con->Capacity) + 2) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			printf("好友上限增加成功!\n");
			con->data = ptr;
			con->Capacity += 2;
		}
		else
		{
			printf("增加失败!\n");
			return;
		}
	}
}

//增加好友信息
void AddContact(Contact* con)
{
	//先检测一下是否满容		满容=>增加空间,否则不进行操作
	Check_Capacity(con);
	//增加数据
	InputInfo(con,con->size);
	con->size++;
	printf("添加成功!\n");
}

//通过名字找好友--找到就返回所在元素的下标，否则返回-1
static int FindByName(const Contact* con, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < con->size; i++)
	{
		if (strcmp(con->data[i].name, name) == 0)
			return i;//找到
	}
	return -1;//未找到
}

//显示好友信息
void ShowContact(const Contact* con)
{
	if (Whether(con))//判断是否有好友
	{
		int i = 0;
		PrintMenu();
		for (i = 0; i < con->size; i++)
		{
			PrintInfo(con, i);
		}
	}
}

//删除好友信息
void DelContact(Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("请输入您要删除的好友名字:>");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
			printf("未找到该好友\n");
		else if (ret == con->size)//删除最后一个好友
		{
			con->size--;
			printf("删除成功\n");
		}
		else
		{
			int j = 0;
			for (j = ret; j < con->size - 1; j++)
			{
				con->data[j] = con->data[j + 1];
			}
			con->size--;
			printf("删除成功\n");
		}
	}
}

//查找好友信息
void SearchContact(const Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("请输入要查找的好友名:> \n");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
		{
			printf("未找到该好友!\n");
		}
		else
		{
			printf("好友信息为:\n");
			PrintMenu();
			PrintInfo(con, ret);
		}
	}
}

//修改好友信息
void ModifyContact(Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("请输入要修改的好友名:> \n");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
		{
			printf("未找到该好友!\n");
		}
		else
		{
			InputInfo(con, ret);
			printf("修改成功!\n");
		}
	}
}

int Name_Sort(const void* data1,const void* data2)
{
	return strcmp(((PeoInfo*)data1)->name, ((PeoInfo*)data2)->name);
}
int Age_Sort(const void* data1,const void* data2)
{
	return ((PeoInfo*)data1)->age - ((PeoInfo*)data2)->age;
}
int Addr_Sort(const void* data1,const void* data2)
{
	return strcmp(((PeoInfo*)data1)->addr, ((PeoInfo*)data2)->addr);
}

//排序好友信息(按名字首字母排序，从小到大)
void SortContact(Contact* con)
{
	int input = 0;
	printf("*** 1、按名字增序  2、按年龄增序 ***\n");
	printf("*** 3、按地址增序  0、取消排序   ***\n");
	do
	{
		printf("请选择排序方式:>");
		scanf("%d", &input);
		switch (input)
		{
		case NAME_SORT:
			qsort(con->data,con->size,sizeof(PeoInfo), Name_Sort);
			printf("排序成功\n");
			break;
		case AGE_SORT:
			qsort(con->data, con->size, sizeof(PeoInfo), Age_Sort);
			printf("排序成功\n");
			break;
		case ADDR_SORT:
			qsort(con->data, con->size, sizeof(PeoInfo), Addr_Sort);
			printf("排序成功\n");
			break;
		case UNDO_SORT:
			printf("取消排序\n");
			break;
		default:
			printf("输入错误\n");
			break;
		}
	} while (input && (input > ADDR_SORT));
}

//销毁通讯录
void Destory_Contact(Contact* con)
{
	free(con->data);
	con->data = NULL;
}

//保存好友信息
void SaveContact(Contact* con)
{
	FILE* pfWrite = fopen("INFOMATION.txt", "wb");
	if (pfWrite == NULL)
	{
		printf("SaveContact:: %s\n", strerror(errno));
		return;
	}
	//存放信息到文件中
	int i = 0;
	for (i = 0; i < con->size; i++)
	{
		fwrite(&(con->data[i]), sizeof(PeoInfo), 1, pfWrite);
	}
	printf("保存成功\n");
	fclose(pfWrite);
	pfWrite = NULL;
}

//加载好友信息
void LoadContact(Contact* con)
{
	PeoInfo tmp = { 0 };
	FILE* pfRead = fopen("INFOMATION.txt", "rb");
	if (pfRead == NULL)
	{
		printf("LoadContact::%s\n", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(PeoInfo), 1, pfRead))
	{
		Check_Capacity(con);
		con->data[con->size] = tmp;
		con->size++;
	}
	fclose(pfRead);
	pfRead = NULL;
}