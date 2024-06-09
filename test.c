#include "Contact.h"

void menu()
{
	printf("****************************\n");
	printf("***1、Add       2、del   ***\n");
	printf("***3、search    4、modify***\n");
	printf("***5、show      6、sort  ***\n");
	printf("***7、save      0、exit  ***\n");
	printf("****************************\n");
}
int main()
{
	int input = 0;
	//生成通讯录		
	Contact con;
	//初始化通讯录,并读取好友信息
	InitContact(&con);

	do
	{
		menu();
		printf("请选择:> ");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			//增加好友信息
			AddContact(&con);
			break;
		case DEL:
			//删除
			DelContact(&con);
			break;
		case SEARCH:
			//查找
			SearchContact(&con);
			break;
		case MODIFY:
			//修改
			ModifyContact(&con);
			break;
		case SHOW:
			//显示
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con);
			break;
		case EXIT:
			//销毁该通讯录
			Destory_Contact(&con);
			printf("您已退出\n");
			break;
		case SAVE:
			SaveContact(&con);
			break;
		default:
			printf("您输入了错误信息\n");
			break;
		}
	} while (input);
	return 0;
}