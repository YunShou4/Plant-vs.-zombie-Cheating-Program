#include"public.h"
#include"op.h"

extern HANDLE hProcess;
extern DWORD Num_You_Want;


extern DWORD res = 0;			//�ж��޸Ľ���ı�־
extern DWORD IsNoCD = 0;		//�ж���CD�����Ƿ���
extern DWORD IsBackRun = 0;		//�жϺ�̨���й����Ƿ���
extern DWORD IsAutoCollect = 0;		//�ж��Զ��ռ������Ƿ���
extern DWORD IsOverlapping = 0;		//�ж�ֲ���ص����ù����Ƿ���


DWORD ADDR = 0x6A9EC0;			//��̬����ַ

//�����ƫ����
DWORD SunShine_offset1 = 0x768;		    //ƫ�Ƶ�ַ1
DWORD SunShine_offset2 = 0x5560;         //ƫ�Ƶ�ַ2

//�����أ�������ڴ��д����ֵΪ�ܽ��������10
DWORD Coin_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Coin_offset2 = 0x28;			//ƫ�Ƶ�ַ2

//ֲ�����������
DWORD Blank_offset1 = 0x768;		    //ƫ�Ƶ�ַ1
DWORD Blank_offset2 = 0x144;			//ƫ�Ƶ�ַ2
DWORD Blank_offset3 = 0x24;			//ƫ�Ƶ�ַ3

//�ǻ����߶����
DWORD Tree_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Tree_offset2 = 0xf4;			//ƫ�Ƶ�ַ2, 4*EAX+0X30

//�ɿ�����أ�����=�ڴ�ֵ-1000
DWORD Chocolate_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Chocolate_offset2 = 0x228;			//ƫ�Ƶ�ַ2

//������أ�����=�ڴ�ֵ-1000
DWORD Fertilizer_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Fertilizer_offset2 = 0x1f8;				//ƫ�Ƶ�ַ2

//ɱ�����أ�����=�ڴ�ֵ-1000
DWORD Pesticides_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Pesticides_offset2 = 0x1fC;			//ƫ�Ƶ�ַ2

//������أ�ð��ģʽ
DWORD Jump_offset1 = 0x82C;		    //ƫ�Ƶ�ַ1
DWORD Jump_offset2 = 0x24;			//ƫ�Ƶ�ַ2

//������أ�С��Ϸ
DWORD Mini_offset1 = 0x7f8;		    //ƫ�Ƶ�ַ1

void ModifySunshine() {

	DWORD Temp_SunShine = CalculateAddr(ADDR, 2, SunShine_offset1, SunShine_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_SunShine, &Num_You_Want, 4, 0);
}

void ModifyCoin() {

	DWORD Temp_Coin = CalculateAddr(ADDR, 2, Coin_offset1, Coin_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Coin, &Num_You_Want, 4, 0);
}

void ModifyBlank() {

	DWORD Temp_Blank = CalculateAddr(ADDR, 3, Blank_offset1, Blank_offset2, Blank_offset3);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Blank, &Num_You_Want, 4, 0);
}

void ModifyNoCD() {
	//������ע��ĵ�ַ��ԭָ��Ϊjle 0x4872AC,����Ϸ�ж��Ƿ���ȴ������ָ��
	//��ԭָ�ע������nopָ�����Ϸ��CD����ƹ�������ʵ����CD
	//nop��ָ����Ϊ0x90
	//jle 0x4872AC��ָ����Ϊ7E 14
	DWORD Temp_CD = 0x487296;
	DWORD NoCD = 0x9090;
	DWORD CD = 0x147E;

	if (!IsNoCD) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_CD, &NoCD, 2, NULL);
		printf("���л�Ϊ��CDģʽ��\n");
		IsNoCD = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_CD, &CD, 2, NULL);
		printf("���л�Ϊ��CDģʽ��\n");
		IsNoCD = 0;
	}
}

void ModifyBackRun() {
	//ret��ָ����Ϊ0xC3
	//push edi��ָ����Ϊ0x57
	DWORD Temp_BackRun = 0x54EBEF;
	DWORD NoBackRun = 0xC3;
	DWORD BackRun = 0x57;

	if (!IsBackRun) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_BackRun, &NoBackRun, 1, NULL);
		printf("���л�Ϊ��̨����ģʽ��\n");
		IsBackRun = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_BackRun, &BackRun, 1, NULL);
		printf("���л�Ϊ��ֹ��̨����ģʽ��\n");
		IsAutoCollect = 0;
	}
}

void ModifyAutoCollect() {
	//������ע��ĵ�ַ��ԭָ��Ϊjnz������Ϸ�ж��Ƿ��������ָ��
	//��ԭָ�ע����������ת��jmpָ�����Ϸ�ĵ������ƹ�������ʵ���Զ��ռ�
	//jmp��ָ����Ϊ0xEB
	//jnz��ָ����Ϊ0x75
	DWORD Temp_AutoCollect = 0x43158F;
	DWORD NoAutoCollect = 0xEB;
	DWORD AutoCollect = 0x75;

	if (!IsAutoCollect) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_AutoCollect, &NoAutoCollect, 1, NULL);
		printf("���л�Ϊ�Զ��ռ�ģʽ��\n");
		IsAutoCollect = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_AutoCollect, &AutoCollect, 1, NULL);
		printf("���л�Ϊ���Զ��ռ�ģʽ��\n");
		IsAutoCollect = 0;
	}
}

void ModifyOverlapping() {
	//������ע��ĵ�ַ��ԭָ��Ϊje 410754������Ϸ�ж��Ƿ���Ϸ���ֲ�������
	//��ԭָ�ע���������ת��jnoָ�����Ϸ�ķ�����������ƹ�������ʵ���ص�����
	//jno 410754��ָ����Ϊ\x0F\x81\x4E\x07\x01\x00
	//je 410754��ָ����Ϊ\x0F\x84\x4E\x07\x01\x00
	DWORD Temp_Overlapping = 0x40FE30;
	DWORD NoOverlapping = 0x81;
	DWORD Overlapping = 0x84;

	if (!IsOverlapping) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_Overlapping, &NoOverlapping, 1, NULL);
		printf("�ѿ����ص�����ģʽ��\n");
		IsOverlapping = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_Overlapping, &Overlapping, 1, NULL);
		printf("�ѹر��ص�����ģʽ��\n");
		IsOverlapping = 0;
	}
}

void ModifyTree() {

	DWORD Temp_Tree = CalculateAddr(ADDR, 2, Tree_offset1, Tree_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Tree, &Num_You_Want, 4, 0);
}

void ModifyChocolate() {

	DWORD Temp_Chocolate = CalculateAddr(ADDR, 2, Chocolate_offset1, Chocolate_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Chocolate, &Num_You_Want, 4, 0);
}

void ModifyFertilizer() {

	DWORD Temp_Fertilizer = CalculateAddr(ADDR, 2, Fertilizer_offset1, Fertilizer_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Fertilizer, &Num_You_Want, 4, 0);
}

void ModifyPesticides() {

	DWORD Temp_Pesticides = CalculateAddr(ADDR, 2, Pesticides_offset1, Pesticides_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Pesticides, &Num_You_Want, 4, 0);
}

void ModifyJump() {

	DWORD Temp_Jump = CalculateAddr(ADDR, 2, Jump_offset1, Jump_offset2);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Jump, &Num_You_Want, 4, 0);
}

void ModifyMini() {
	DWORD Temp_Mini = CalculateAddr(ADDR, 1, Mini_offset1);
	res = WriteProcessMemory(hProcess, (LPVOID)Temp_Mini, &Num_You_Want, 4, 0);
}