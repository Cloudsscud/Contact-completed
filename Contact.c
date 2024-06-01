#include "Contact.h"

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

//���������Ϣ(����������ĸ���򣬴�С����)
void SortContact(Contact* con)
{
	PeoInfo cmp;
	int i = 0;
	int j = 0;
	for (i = 0; i < con->size; i++)
	{
		for (j = 0; j < con->size-1-i; j++)
		{
			if (strcmp(con->data[j].name, con->data[j + 1].name) > 0)
			{
				cmp = con->data[j];
				con->data[j] = con->data[j+1];
				con->data[j+1] = cmp;
			}
		}
	}
	printf("�Ѱ����ִ�С��������ɹ�!\n");
}

//����ͨѶ¼
void Destory_Contact(Contact* con)
{
	free(con->data);
	con->data = NULL;
}