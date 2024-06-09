#include "Contact.h"

void LoadContact(Contact* con);
//��ʼ��ͨѶ¼
void InitContact(Contact* con)
{
	assert(con);
	//��������Ҫ�󣺸�ͨѶ¼��ʼֻ��Ĭ������������λ�����ﵽ��������ʱ������������λ
	con->data = (PeoInfo*)malloc(DEFAULT_CAPACITY * sizeof(PeoInfo));//��ʼ�����հ׻���������Ϣ
	if (con->data == NULL)
	{
		return;
	}
	con->size = 0;//��ʼ�����к�����
	con->Capacity = DEFAULT_CAPACITY;//��ʼ��Ĭ������

	//�����ѱ���ĺ�����Ϣ
	LoadContact(con);
}

//�����Ӧ�±�Ԫ����Ϣ
void PrintInfo(const Contact* con, int cmp)
{
	printf("%-20s\t%-4d\t%-6s\t%-12s\t%-30s\n",
		con->data[cmp].name,
		con->data[cmp].age,
		con->data[cmp].sex,
		con->data[cmp].tele,
		con->data[cmp].addr);
}

//�����Ϣ�Ĳ˵�
static void PrintMenu()
{
	printf("%-20s\t%-4s\t%-6s\t%-12s\t%-30s\n", "����", "����", "�Ա�", "�绰", "��ַ");
}

//�ڶ�Ӧ�±�����Ԫ����Ϣ
void InputInfo(Contact* con, int cmp)
{
	printf("����������:> ");
	scanf("%s", con->data[cmp].name);
	printf("����������:> ");
	scanf("%d", &(con->data[cmp].age));
	printf("�������Ա�:> ");
	scanf("%s", con->data[cmp].sex);
	printf("������绰:> ");
	scanf("%s", con->data[cmp].tele);
	printf("�������ַ:> ");
	scanf("%s", con->data[cmp].addr);
}

//�жϺ����Ƿ�Ϊ��
int Whether(const Contact* con)
{
	if (con->size == 0)
	{
		printf("��ǰ�޺��ѣ�������Ӻ���!\n");
		return 0;
	}
	return 1;
}

//����Ƿ�����		����=>���ӿռ�,���򲻽��в���
void Check_Capacity(Contact* con)
{
	assert(con);
	if (con->size == con->Capacity)
	{
		//����
		PeoInfo* ptr = (PeoInfo*)realloc(con->data, ((con->Capacity) + 2) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			printf("�����������ӳɹ�!\n");
			con->data = ptr;
			con->Capacity += 2;
		}
		else
		{
			printf("����ʧ��!\n");
			return;
		}
	}
}

//���Ӻ�����Ϣ
void AddContact(Contact* con)
{
	//�ȼ��һ���Ƿ�����		����=>���ӿռ�,���򲻽��в���
	Check_Capacity(con);
	//��������
	InputInfo(con,con->size);
	con->size++;
	printf("��ӳɹ�!\n");
}

//ͨ�������Һ���--�ҵ��ͷ�������Ԫ�ص��±꣬���򷵻�-1
static int FindByName(const Contact* con, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < con->size; i++)
	{
		if (strcmp(con->data[i].name, name) == 0)
			return i;//�ҵ�
	}
	return -1;//δ�ҵ�
}

//��ʾ������Ϣ
void ShowContact(const Contact* con)
{
	if (Whether(con))//�ж��Ƿ��к���
	{
		int i = 0;
		PrintMenu();
		for (i = 0; i < con->size; i++)
		{
			PrintInfo(con, i);
		}
	}
}

//ɾ��������Ϣ
void DelContact(Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("��������Ҫɾ���ĺ�������:>");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
			printf("δ�ҵ��ú���\n");
		else if (ret == con->size)//ɾ�����һ������
		{
			con->size--;
			printf("ɾ���ɹ�\n");
		}
		else
		{
			int j = 0;
			for (j = ret; j < con->size - 1; j++)
			{
				con->data[j] = con->data[j + 1];
			}
			con->size--;
			printf("ɾ���ɹ�\n");
		}
	}
}

//���Һ�����Ϣ
void SearchContact(const Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("������Ҫ���ҵĺ�����:> \n");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
		{
			printf("δ�ҵ��ú���!\n");
		}
		else
		{
			printf("������ϢΪ:\n");
			PrintMenu();
			PrintInfo(con, ret);
		}
	}
}

//�޸ĺ�����Ϣ
void ModifyContact(Contact* con)
{
	if (Whether(con))
	{
		char name[MAX_NAME];
		printf("������Ҫ�޸ĵĺ�����:> \n");
		scanf("%s", name);
		int ret = FindByName(con, name);
		if (ret == -1)
		{
			printf("δ�ҵ��ú���!\n");
		}
		else
		{
			InputInfo(con, ret);
			printf("�޸ĳɹ�!\n");
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

//���������Ϣ(����������ĸ���򣬴�С����)
void SortContact(Contact* con)
{
	int input = 0;
	printf("*** 1������������  2������������ ***\n");
	printf("*** 3������ַ����  0��ȡ������   ***\n");
	do
	{
		printf("��ѡ������ʽ:>");
		scanf("%d", &input);
		switch (input)
		{
		case NAME_SORT:
			qsort(con->data,con->size,sizeof(PeoInfo), Name_Sort);
			printf("����ɹ�\n");
			break;
		case AGE_SORT:
			qsort(con->data, con->size, sizeof(PeoInfo), Age_Sort);
			printf("����ɹ�\n");
			break;
		case ADDR_SORT:
			qsort(con->data, con->size, sizeof(PeoInfo), Addr_Sort);
			printf("����ɹ�\n");
			break;
		case UNDO_SORT:
			printf("ȡ������\n");
			break;
		default:
			printf("�������\n");
			break;
		}
	} while (input && (input > ADDR_SORT));
}

//����ͨѶ¼
void Destory_Contact(Contact* con)
{
	free(con->data);
	con->data = NULL;
}

//���������Ϣ
void SaveContact(Contact* con)
{
	FILE* pfWrite = fopen("INFOMATION.txt", "wb");
	if (pfWrite == NULL)
	{
		printf("SaveContact:: %s\n", strerror(errno));
		return;
	}
	//�����Ϣ���ļ���
	int i = 0;
	for (i = 0; i < con->size; i++)
	{
		fwrite(&(con->data[i]), sizeof(PeoInfo), 1, pfWrite);
	}
	printf("����ɹ�\n");
	fclose(pfWrite);
	pfWrite = NULL;
}

//���غ�����Ϣ
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