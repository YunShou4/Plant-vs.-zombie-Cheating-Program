#include"public.h"
#include"op.h"

extern HANDLE hProcess;
extern DWORD Num_You_Want;


extern DWORD res = 0;			//判断修改结果的标志
extern DWORD IsNoCD = 0;		//判断无CD功能是否开启
extern DWORD IsBackRun = 0;		//判断后台运行功能是否开启
extern DWORD IsAutoCollect = 0;		//判断自动收集功能是否开启
extern DWORD IsOverlapping = 0;		//判断植物重叠放置功能是否开启


DWORD ADDR = 0x6A9EC0;			//静态基地址

//阳光的偏移量
DWORD SunShine_offset1 = 0x768;		    //偏移地址1
DWORD SunShine_offset2 = 0x5560;         //偏移地址2

//金币相关，金币在内存中储存的值为总金币数除以10
DWORD Coin_offset1 = 0x82C;		    //偏移地址1
DWORD Coin_offset2 = 0x28;			//偏移地址2

//植物栏数量相关
DWORD Blank_offset1 = 0x768;		    //偏移地址1
DWORD Blank_offset2 = 0x144;			//偏移地址2
DWORD Blank_offset3 = 0x24;			//偏移地址3

//智慧树高度相关
DWORD Tree_offset1 = 0x82C;		    //偏移地址1
DWORD Tree_offset2 = 0xf4;			//偏移地址2, 4*EAX+0X30

//巧克力相关，数量=内存值-1000
DWORD Chocolate_offset1 = 0x82C;		    //偏移地址1
DWORD Chocolate_offset2 = 0x228;			//偏移地址2

//花肥相关，数量=内存值-1000
DWORD Fertilizer_offset1 = 0x82C;		    //偏移地址1
DWORD Fertilizer_offset2 = 0x1f8;				//偏移地址2

//杀虫剂相关，数量=内存值-1000
DWORD Pesticides_offset1 = 0x82C;		    //偏移地址1
DWORD Pesticides_offset2 = 0x1fC;			//偏移地址2

//跳关相关，冒险模式
DWORD Jump_offset1 = 0x82C;		    //偏移地址1
DWORD Jump_offset2 = 0x24;			//偏移地址2

//跳关相关，小游戏
DWORD Mini_offset1 = 0x7f8;		    //偏移地址1

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
	//将代码注入的地址，原指令为jle 0x4872AC,是游戏判断是否冷却结束的指令
	//向原指令处注入两个nop指令，将游戏的CD检测绕过，即可实现无CD
	//nop的指令码为0x90
	//jle 0x4872AC的指令码为7E 14
	DWORD Temp_CD = 0x487296;
	DWORD NoCD = 0x9090;
	DWORD CD = 0x147E;

	if (!IsNoCD) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_CD, &NoCD, 2, NULL);
		printf("已切换为无CD模式！\n");
		IsNoCD = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_CD, &CD, 2, NULL);
		printf("已切换为有CD模式！\n");
		IsNoCD = 0;
	}
}

void ModifyBackRun() {
	//ret的指令码为0xC3
	//push edi的指令码为0x57
	DWORD Temp_BackRun = 0x54EBEF;
	DWORD NoBackRun = 0xC3;
	DWORD BackRun = 0x57;

	if (!IsBackRun) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_BackRun, &NoBackRun, 1, NULL);
		printf("已切换为后台运行模式！\n");
		IsBackRun = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_BackRun, &BackRun, 1, NULL);
		printf("已切换为禁止后台运行模式！\n");
		IsAutoCollect = 0;
	}
}

void ModifyAutoCollect() {
	//将代码注入的地址，原指令为jnz，是游戏判断是否点击阳光的指令
	//将原指令处注入无条件跳转的jmp指令，将游戏的点击检测绕过，即可实现自动收集
	//jmp的指令码为0xEB
	//jnz的指令码为0x75
	DWORD Temp_AutoCollect = 0x43158F;
	DWORD NoAutoCollect = 0xEB;
	DWORD AutoCollect = 0x75;

	if (!IsAutoCollect) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_AutoCollect, &NoAutoCollect, 1, NULL);
		printf("已切换为自动收集模式！\n");
		IsAutoCollect = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_AutoCollect, &AutoCollect, 1, NULL);
		printf("已切换为非自动收集模式！\n");
		IsAutoCollect = 0;
	}
}

void ModifyOverlapping() {
	//将代码注入的地址，原指令为je 410754，是游戏判断是否符合放置植物的条件
	//将原指令处注入无溢出跳转的jno指令，将游戏的放置条件检测绕过，即可实现重叠放置
	//jno 410754的指令码为\x0F\x81\x4E\x07\x01\x00
	//je 410754的指令码为\x0F\x84\x4E\x07\x01\x00
	DWORD Temp_Overlapping = 0x40FE30;
	DWORD NoOverlapping = 0x81;
	DWORD Overlapping = 0x84;

	if (!IsOverlapping) {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_Overlapping, &NoOverlapping, 1, NULL);
		printf("已开启重叠放置模式！\n");
		IsOverlapping = 1;
	}
	else {
		res = WriteProcessMemory(hProcess, (LPVOID)Temp_Overlapping, &Overlapping, 1, NULL);
		printf("已关闭重叠放置模式！\n");
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