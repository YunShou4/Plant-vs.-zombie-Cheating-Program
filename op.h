#pragma once
#include<Windows.h>

//��ӡ˵����Ϣ
void SendTheMessage();
//����Ϸ����
void OpenTheGame();
//�ж��Ƿ��޸ĳɹ�
void SuccessJudge(DWORD res);
//swich��֧����ǰ���ж�
bool IsRunning(HANDLE hProcess);
//ִ�л���ַ��ƫ�Ƶ�ַ���ۼӹ���
DWORD CalculateAddr(DWORD BaseAdd, BOOL n, ...);
//��ӡС��Ϸ�б�
void MiniGamesList();
//���ƺ�������Ϸ�ж���������һ��������
DWORD LimitNum(DWORD num, DWORD low, DWORD high);
//���ú���������
void ToDoTheFunction(void (*TheFunction)());
//�鿴������Ч�Ĺ���
void WhatIsDoing();
//�˳�����
void CloseTheProgram();