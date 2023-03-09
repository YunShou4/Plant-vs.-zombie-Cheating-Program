#include"public.h"
#include"op.h"
#include"modify.h"

extern DWORD Num_You_Want = 0;		//�洢�޸�ֵ		
extern HANDLE hProcess = 0;		//�������к�ľ��

static byte Choose;							//������

void ModifyFunctions() {
	//���빦������
	printf("��ѡ��Ҫ���еĲ�����");
	scanf_s("%c", &Choose);

	switch (Choose)
	{
		//����0�����´���Ϸ
	case '0':
		OpenTheGame();
		break;

		//����1������Ϊ�޸�������
	case '1':
		printf("�������޸ĵ���������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 9990);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifySunshine);
		break;

		//����2������Ϊ�޸Ľ����ֵ
	case '2':
		printf("�������޸ĵĽ������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 99990);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyCoin);
		break;

		//����3������Ϊ�޸�ֲ��������
	case '3':
		printf("�������޸ĵ�ֲ����������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 10);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyBlank);
		break;

		//����4������Ϊֲ������ȴ
	case '4':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyNoCD);
		break;

		//����5������Ϊ����/�رպ�̨����
	case '5':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyBackRun);
		break;

		//����6������Ϊ����/�ر��Զ��ռ�
	case '6':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyAutoCollect);
		break;

		//����7������Ϊ����/�ر�ֲ���ص�����
	case '7':
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyOverlapping);
		break;

		//����8������Ϊ�޸��ǻ����߶�
	case '8':
		printf("�������޸ĵ��ǻ����߶ȣ�");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 2147483647);
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyTree);
		break;

		//����9������Ϊ�޸��ɿ�����
	case '9':
		printf("�������޸ĵ��ɿ�������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 10);
		Num_You_Want += 1000;	//��Ϸ�ڵ���ִ洢���ƣ���Ҳ��֪��ΪʲôXD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyChocolate);
		break;

		//����a������Ϊ�޸Ļ�����
	case 'a':
		printf("�������޸ĵĻ�������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 999);
		Num_You_Want += 1000;	//��Ϸ�ڵ���ִ洢���ƣ���Ҳ��֪��ΪʲôXD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyFertilizer);
		break;

		//����b������Ϊ�޸�ɱ�����
	case 'b':
		printf("�������޸ĵ�ɱ�������");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 0, 999);
		Num_You_Want += 1000;	//��Ϸ�ڵ���ִ洢���ƣ���Ҳ��֪��ΪʲôXD
		if (IsRunning(hProcess))
			ToDoTheFunction(*ModifyPesticides);
		break;

		//����c������Ϊð��ģʽ����
	case 'c':
		printf("����������ȥ�Ĺؿ�(1-50��������ȥ3-4��Ӧ����24)��");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 50);
		if (Num_You_Want > 0 || Num_You_Want < 51)
			if (IsRunning(hProcess))
				ToDoTheFunction(*ModifyJump);
			else
				printf("û����һ�أ�\n");
		break;

		//����d������ΪС��Ϸ����
	case 'd':
		MiniGamesList();
		printf("����������ȥ�Ĺؿ�(1-55)��");
		scanf_s("%d", &Num_You_Want);
		Num_You_Want = LimitNum(Num_You_Want, 1, 55);
		if (Num_You_Want > 0 || Num_You_Want < 56)
			if (IsRunning(hProcess))
				ToDoTheFunction(*ModifyMini);
			else
				printf("û����һ�أ�\n");
		break;

		//����w���鿴������Ч�Ĺ���
	case 'w':
		WhatIsDoing();
		break;

		//����q������Ϊ�˳�����
	case 'q':
		CloseTheProgram();

	default:
		printf("û�д˹��ܵ���ţ�������������룡");
		break;
	}

	Sleep(2500);
	system("cls");
}