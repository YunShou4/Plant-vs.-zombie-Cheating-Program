#pragma once
#include<Windows.h>

//打印说明信息
void SendTheMessage();
//打开游戏进程
void OpenTheGame();
//判断是否修改成功
void SuccessJudge(DWORD res);
//swich分支进行前的判断
bool IsRunning(HANDLE hProcess);
//执行基地址和偏移地址的累加工作
DWORD CalculateAddr(DWORD BaseAdd, BOOL n, ...);
//打印小游戏列表
void MiniGamesList();
//限制函数，游戏中多项数据有一定的上限
DWORD LimitNum(DWORD num, DWORD low, DWORD high);
//调用函数的整合
void ToDoTheFunction(void (*TheFunction)());
//查看正在生效的功能
void WhatIsDoing();
//退出程序
void CloseTheProgram();