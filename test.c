#include "Contact.h"

void menu()
{
	printf("****************************\n");
	printf("***1��Add       2��del   ***\n");
	printf("***3��search    4��modify***\n");
	printf("***5��show      6��sort  ***\n");
	printf("***7��save      0��exit  ***\n");
	printf("****************************\n");
}
int main()
{
	int input = 0;
	//����ͨѶ¼		
	Contact con;
	//��ʼ��ͨѶ¼,����ȡ������Ϣ
	InitContact(&con);

	do
	{
		menu();
		printf("��ѡ��:> ");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			//���Ӻ�����Ϣ
			AddContact(&con);
			break;
		case DEL:
			//ɾ��
			DelContact(&con);
			break;
		case SEARCH:
			//����
			SearchContact(&con);
			break;
		case MODIFY:
			//�޸�
			ModifyContact(&con);
			break;
		case SHOW:
			//��ʾ
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			//���ٸ�ͨѶ¼
			Destory_Contact(&con);
			printf("�����˳�\n");
			break;
		case SAVE:
			SaveContact(&con);
			break;
		default:
			printf("�������˴�����Ϣ\n");
			break;
		}
	} while (input);
	return 0;
}