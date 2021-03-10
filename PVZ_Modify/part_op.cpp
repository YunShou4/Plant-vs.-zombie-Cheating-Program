#include"public.h"

#include<tchar.h>

extern DWORD Num_You_Want;	
extern HANDLE hProcess;	
extern DWORD res;			
extern DWORD IsNoCD;		
extern DWORD IsBackRun;		
extern DWORD IsAutoCollect;		
extern DWORD IsOverlapping;	


static HWND hWnd;						//窗口句柄
static DWORD pid;					    //进程句柄

const char* miniGameList[] = { "生存模式：白天","生存模式：黑夜","生存模式：泳池","生存模式：浓雾","生存模式：屋顶",
							"生存模式：白天（困难）","生存模式：黑夜（困难）","生存模式：泳池（困难）","生存模式：浓雾（困难）","生存模式：屋顶（困难）",
							"生存模式：白天（无尽）","生存模式：黑夜（无尽）","生存模式：泳池（无尽）","生存模式：浓雾（无尽）","生存模式：屋顶（无尽）",
							"植物僵尸","坚果保龄球模式","老虎机","雨中种植物","宝石迷阵",
							"隐形食脑者","看星星","僵尸水族馆","宝石迷阵转转看","小僵尸大麻烦",
							"保护传送门","你看，他们像柱子一样","雪橇区","僵尸快跑","锤僵尸",
							"谁笑到最后","植物僵尸2","坚果保龄球2","跳跳舞会","僵王博士的复仇",
							"破罐者","全部留下","第三个罐子","连锁反应","M的意思是金属",
							"胆怯的制陶工","变戏法","另一个连锁反应","罐子王牌","无尽的试炼",
							"我是僵尸","我也是僵尸","你能铲了它么","完全傻了","死亡飞艇",
							"我烂了","僵尸摇摆","三连击","你的所有大脑都是属于我的","我是僵尸无尽版" };

void SendTheMessage() {
	//辅助程序使用的文字信息
	printf("\n歪比歪比，歪比巴卜\n");
	printf("欢迎使用该程序！\n");
	printf("修改器支持版本：英文原版\n");
	printf("------------------------------------------------\n");
	printf("0.重新打开进程\n");
	printf("\n");
	printf("——常规修改：\n");
	printf("1.修改阳光\n2.修改金币\n3.修改植物栏数量\n4.植物无冷却时间(再开一次取消)\n"
		"5.允许后台运行(再开一次取消)\n6.自动收集(再开一次取消)\n7.植物重叠放置(再开一次取消)\n");
	printf("\n——花园修改：\n");
	printf("8.修改智慧树高度\n9.修改巧克力数量\na.修改肥料数量\nb.修改杀虫剂数量\n");
	printf("\n——关卡选择：\n");
	printf("c.选择主线关卡\nd.选择小游戏关卡\n");
	printf("\n");
	printf("w.查看正在生效的功能 \n");
	printf("q.退出 \n");
	printf("------------------------------------------------\n");
	printf("tips:若使用关卡选择功能，请先任意进入一个关卡后暂停，在本修改器中输\n");
	printf("入要去的关卡号后，再在游戏中选择RESTART，否则将可能发生贴图错误！\n\n");
}

void OpenTheGame() {
	printf("打开游戏进程中······\n");
	//搜索游戏窗口，_T()作用是将中文转码防止读取错误
	hWnd = FindWindow(NULL, _T("Plants vs. Zombies"));
	if (hWnd != 0) {
		//找出游戏窗口的创建者，将数组储存在pid中
		GetWindowThreadProcessId(hWnd, &pid);
		//打开进程，成功则返回游戏句柄，失败则返回空
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		if (hProcess == 0) {
			printf("打开游戏进程失败:<\n");
		}
		else
			printf("打开游戏进程成功:>\n");
	}
	else {
		printf("游戏没有运行,或者没有使用管理员身份运行本程序!\n");
	}
}

bool IsRunning(HANDLE hProcess) {
	if (hProcess != 0)
		return true;
	else {
		printf("请先打开游戏进程!\n");
		return false;
	}
}

void SuccessJudge(DWORD res) {
	if (res == 0)
		printf("修改失败:<\n");
	else
		printf("修改成功:>\n");
}

void CloseTheProgram() {
	exit(1);
}

DWORD CalculateAddr(DWORD BaseAdd, BOOL n, ...) {
	//BaseAdd表示静态基地址，n代表偏移地址的级数，...代表n级偏移地址
	va_list ap;
	va_start(ap, n);

	DWORD FinalAddr = BaseAdd;
	for (int i = 0; i < n; i++) {
		ReadProcessMemory(hProcess, (LPVOID)FinalAddr, &FinalAddr, 4, 0);
		FinalAddr += va_arg(ap, DWORD); //累加可变参数，第二个参数为可变参数的类型
	}

	va_end(ap);         //释放指针内存
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

	//判断是否修改成功
	SuccessJudge(res);
}

void WhatIsDoing() {
	if (IsNoCD)
		printf("无CD功能生效中！\n");
	if (IsBackRun)
		printf("后台运行功能生效中！\n");
	if (IsAutoCollect)
		printf("自动收集功能生效中！\n");
	if (IsOverlapping)
		printf("植物重叠放置功能生效中！\n");
}