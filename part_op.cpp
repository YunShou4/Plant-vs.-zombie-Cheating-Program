#include"public.h"

#include<tchar.h>

extern DWORD Num_You_Want;	
extern HANDLE hProcess;	
extern DWORD res;			
extern DWORD IsNoCD;		
extern DWORD IsBackRun;		
extern DWORD IsAutoCollect;		
extern DWORD IsOverlapping;	


static HWND hWnd;						//���ھ��
static DWORD pid;					    //���̾��

const char* miniGameList[] = { "����ģʽ������","����ģʽ����ҹ","����ģʽ��Ӿ��","����ģʽ��Ũ��","����ģʽ���ݶ�",
							"����ģʽ�����죨���ѣ�","����ģʽ����ҹ�����ѣ�","����ģʽ��Ӿ�أ����ѣ�","����ģʽ��Ũ�����ѣ�","����ģʽ���ݶ������ѣ�",
							"����ģʽ�����죨�޾���","����ģʽ����ҹ���޾���","����ģʽ��Ӿ�أ��޾���","����ģʽ��Ũ���޾���","����ģʽ���ݶ����޾���",
							"ֲ�ｩʬ","���������ģʽ","�ϻ���","������ֲ��","��ʯ����",
							"����ʳ����","������","��ʬˮ���","��ʯ����תת��","С��ʬ���鷳",
							"����������","�㿴������������һ��","ѩ����","��ʬ����","����ʬ",
							"˭Ц�����","ֲ�ｩʬ2","���������2","�������","������ʿ�ĸ���",
							"�ƹ���","ȫ������","����������","������Ӧ","M����˼�ǽ���",
							"���ӵ����չ�","��Ϸ��","��һ��������Ӧ","��������","�޾�������",
							"���ǽ�ʬ","��Ҳ�ǽ�ʬ","���ܲ�����ô","��ȫɵ��","������ͧ",
							"������","��ʬҡ��","������","������д��Զ��������ҵ�","���ǽ�ʬ�޾���" };

void SendTheMessage() {
	//��������ʹ�õ�������Ϣ
	printf("\n�����ȣ���ȰͲ�\n");
	printf("��ӭʹ�øó���\n");
	printf("�޸���֧�ְ汾��Ӣ��ԭ��\n");
	printf("------------------------------------------------\n");
	printf("0.���´򿪽���\n");
	printf("\n");
	printf("���������޸ģ�\n");
	printf("1.�޸�����\n2.�޸Ľ��\n3.�޸�ֲ��������\n4.ֲ������ȴʱ��(�ٿ�һ��ȡ��)\n"
		"5.�����̨����(�ٿ�һ��ȡ��)\n6.�Զ��ռ�(�ٿ�һ��ȡ��)\n7.ֲ���ص�����(�ٿ�һ��ȡ��)\n");
	printf("\n������԰�޸ģ�\n");
	printf("8.�޸��ǻ����߶�\n9.�޸��ɿ�������\na.�޸ķ�������\nb.�޸�ɱ�������\n");
	printf("\n�����ؿ�ѡ��\n");
	printf("c.ѡ�����߹ؿ�\nd.ѡ��С��Ϸ�ؿ�\n");
	printf("\n");
	printf("w.�鿴������Ч�Ĺ��� \n");
	printf("q.�˳� \n");
	printf("------------------------------------------------\n");
	printf("tips:��ʹ�ùؿ�ѡ���ܣ������������һ���ؿ�����ͣ���ڱ��޸�������\n");
	printf("��Ҫȥ�Ĺؿ��ź�������Ϸ��ѡ��RESTART�����򽫿��ܷ�����ͼ����\n\n");
}

void OpenTheGame() {
	printf("����Ϸ�����С�����������\n");
	//������Ϸ���ڣ�_T()�����ǽ�����ת���ֹ��ȡ����
	hWnd = FindWindow(NULL, _T("Plants vs. Zombies"));
	if (hWnd != 0) {
		//�ҳ���Ϸ���ڵĴ����ߣ������鴢����pid��
		GetWindowThreadProcessId(hWnd, &pid);
		//�򿪽��̣��ɹ��򷵻���Ϸ�����ʧ���򷵻ؿ�
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (hProcess == 0) {
			printf("����Ϸ����ʧ��:<\n");
		}
		else
			printf("����Ϸ���̳ɹ�:>\n");
	}
	else {
		printf("��Ϸû������,����û��ʹ�ù���Ա������б�����!\n");
	}
}

bool IsRunning(HANDLE hProcess) {
	if (hProcess != 0)
		return true;
	else {
		printf("���ȴ���Ϸ����!\n");
		return false;
	}
}

void SuccessJudge(DWORD res) {
	if (res == 0)
		printf("�޸�ʧ��:<\n");
	else
		printf("�޸ĳɹ�:>\n");
}

void CloseTheProgram() {
	exit(1);
}

DWORD CalculateAddr(DWORD BaseAdd, BOOL n, ...) {
	//BaseAdd��ʾ��̬����ַ��n����ƫ�Ƶ�ַ�ļ�����...����n��ƫ�Ƶ�ַ
	va_list ap;
	va_start(ap, n);

	DWORD FinalAddr = BaseAdd;
	for (int i = 0; i < n; i++) {
		ReadProcessMemory(hProcess, (LPVOID)FinalAddr, &FinalAddr, 4, 0);
		FinalAddr += va_arg(ap, DWORD); //�ۼӿɱ�������ڶ�������Ϊ�ɱ����������
	}

	va_end(ap);         //�ͷ�ָ���ڴ�
	return FinalAddr;
}

void MiniGamesList() {
	for (int i = 0; i < 55; i++) {
		printf("%d.%s\n", i + 1, miniGameList[i]);
	}
}

DWORD LimitNum(DWORD num, DWORD low, DWORD high) {
	if (num > high)
		return high;
	else if (num < low)
		return low;
	else
		return num;
}

void ToDoTheFunction(void (*TheFunction)()) {
	TheFunction();

	//�ж��Ƿ��޸ĳɹ�
	SuccessJudge(res);
}

void WhatIsDoing() {
	if (IsNoCD)
		printf("��CD������Ч�У�\n");
	if (IsBackRun)
		printf("��̨���й�����Ч�У�\n");
	if (IsAutoCollect)
		printf("�Զ��ռ�������Ч�У�\n");
	if (IsOverlapping)
		printf("ֲ���ص����ù�����Ч�У�\n");
}