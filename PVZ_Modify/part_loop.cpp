#include"public.h"
#include"op.h"
#include"modify.h"

extern DWORD Num_You_Want = 0;		//存储修改值		
extern HANDLE hProcess = 0;		//进程运行后的句柄

static byte Choose;							//控制项

void ModifyFunctions() {
	//输入功能需求
	printf("请选择要进行的操作：");
	scanf_s("%c", &Choose);

	switch (Choose)
	{
		//输入0，重新打开游戏
	case '0':
		OpenTheGame();
		break;

		//输入1，功能为修改阳光数
	case '1':
		printf("请输入修改的阳光数：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 9990);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifySunshine);
		break;

		//输入2，功能为修改金币数值
	case '2':
		printf("请输入修改的金币数：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 99990);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyCoin);
		break;

		//输入3，功能为修改植物栏数量
	case '3':
		printf("请输入修改的植物栏数量：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 10);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyBlank);
		break;

		//输入4，功能为植物无冷却
	case '4':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyNoCD);
		break;

		//输入5，功能为开启/关闭后台运行
	case '5':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyBackRun);
		break;

		//输入6，功能为开启/关闭自动收集
	case '6':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyAutoCollect);
		break;

		//输入7，功能为开启/关闭植物重叠放置
	case '7':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyOverlapping);
		break;

		//输入8，功能为修改智慧树高度
	case '8':
		printf("请输入修改的智慧树高度：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 2147483647);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyTree);
		break;

		//输入9，功能为修改巧克力数
	case '9':
		printf("请输入修改的巧克力数：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 10);
		Num_You_Want += 1000;	//游戏内的奇怪存储机制，我也不知道为什么XD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyChocolate);
		break;

		//输入a，功能为修改花肥数
	case 'a':
		printf("请输入修改的花肥数：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 999);
		Num_You_Want += 1000;	//游戏内的奇怪存储机制，我也不知道为什么XD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyFertilizer);
		break;

		//输入b，功能为修改杀虫剂数
	case 'b':
		printf("请输入修改的杀虫剂数：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 999);
		Num_You_Want += 1000;	//游戏内的奇怪存储机制，我也不知道为什么XD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyPesticides);
		break;

		//输入c，功能为冒险模式跳关
	case 'c':
		printf("请输入你想去的关卡(1-50，假如想去3-4，应输入24)：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 50);
		if (Num_You_Want > 0 || Num_You_Want < 51)
			if (IsRunning(hProcess))
				ToDoTheFunction(*ModifyJump);
			else
				printf("没有这一关！\n");
		break;

		//输入d，功能为小游戏跳关
	case 'd':
		MiniGamesList();
		printf("请输入你想去的关卡(1-55)：");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 55);
		if (Num_You_Want > 0 || Num_You_Want < 56)
			if (IsRunning(hProcess))
				ToDoTheFunction(*ModifyMini);
			else
				printf("没有这一关！\n");
		break;

		//输入w，查看正在生效的功能
	case 'w':
		WhatIsDoing();
		break;

		//输入q，功能为退出程序
	case 'q':
		CloseTheProgram();

	default:
		printf("没有此功能的序号，请检查后重新输入！");
		break;
	}

	Sleep(2500);
	system("cls");
}