#include "core.h"

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void Clean_Cussor()	// 커서를 지우는 함수 
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

_clMonster::_clMonster() : bActiveMOB(false), iSearchRange(7)
{
	iXpos_m = INT_MAX;
	iYpos_m = INT_MAX;
	iXpos_om = INT_MAX;
	iYpos_om = INT_MAX;
}

_clMonster::~_clMonster()
{
	
}
		
_clMonster::InputPOS_m(const int Xpos, const int Ypos)
{
	iXpos_m = Xpos;
	iYpos_m = Ypos;
	return true;
}

_clMonster::InputPOS_om(int Xpos, const int Ypos)
{
	iXpos_om = Xpos * 2;
	iYpos_om = Ypos;
	return true;
}

void _clMap::ActiveMOB(int Mob)	// 몹을 활성화하는 함수 
{
	MOB[Mob].bActiveMOB = true;
	return;
}

void _clMap::UnActiveMOB(int Mob)	// 몹을 비활성화 하는 함수 
{
	MOB[Mob].bActiveMOB = false;
	MOB[Mob].iXpos_m = INT_MAX;
	MOB[Mob].iYpos_m = INT_MAX;
	MOB[Mob].iXpos_om = INT_MAX;
	MOB[Mob].iYpos_om = INT_MAX;
	bMOB_ACTIVE[Mob] = false;
	return;
}

_clMap::_clMap() : iStage(1), bUserInfo_Reprint(false)	// 생성될떄 1스테이지를 읽는다. 
{
	//ReadStage(1);
	//Print_Map();
	for(int i = 0; i < 10; i++)
		bMOB_ACTIVE[i] = false;
}
_clMap::~_clMap()
{
	//cout << "~_clMap" << endl;
}

_clMap::Check_Wall(char Move, int iType)	// 플레이어의 충돌판정 값 반환 
{
	switch(iType)
	{
		case 1:
			if(Move == '1' || Move == '3' || Move == '6')return false;	// 시작점, 벽, 약한벽 이면 실패! 
			else return true;
		case 2:	// 총알발싸 체크 
			if(Move == '0' || Move == 'C')
				return true;
			else return false;
		case 3:	// 몬스터의 충돌 판정
			if(Move == '1' || Move == '3' || Move == '4' || Move == 'C') 
				return false;
			else return true;
	}
}

bool _clMap::ReadStage(const int iStage_Num)	// 맵을 읽는 함수
{
	FILE *pFile = NULL;
	switch(iStage_Num)	// 입력받은 숫자로 맵을 선택한다 
	{
		case 1:
			fopen_s(&pFile, "stage1.txt", "r+t");
			break;
		case 2:
			fopen_s(&pFile, "stage2.txt", "r+t");
			break;
	}
	if(pFile)	// 맵읽기 에 성공하면 맵을 읽고 true 를 반환한다 
	{
		for(int y = 0; y < 10; y++)
			for(int x = 0; x < 50; x++)
			{
				fread(&cMap[y][x], sizeof(char), 1, pFile);
				if(cMap[y][x] == '\n')fread(&cMap[y][x], sizeof(char), 1, pFile);	// 읽다가 마지막 부분에 \n 가 들어오면 무시하고 한번 더 읽기 
			}
		fclose(pFile);
	}
	else	// 실패시 false 반환 
	{
		system("cls");
		cout << "stage" << iStage_Num << ".txt 맵읽기 실패!" << endl;
		return false;
	}
	return true;
	
}

void _clMap::ResetMOB()	// 몬스터 초기화 
{
	for(int i = 0; i < 10; i++)
	{
		UnActiveMOB(i);
	}
	return;
}

/*
0	"  " 공백
1 	"■" 강한벽
2	"§" 플레이어 
3	"♧" 시작점
4	"♣" 도착점 
5	"＃" 가시 
6	"□" 약한벽 
7	"㉿" 강화약
8	"＆" 탄약 
9 	"º" 왼쪽 총알 
A	"○" 코인 
B	"º" 오른쪽 총알
C	"＠" 몬스터 
*/

// == 플레이어 클래스

_clPlayer::_clPlayer() : iLife_p(3) ,iJumpRemain_p(0), CoinStack_p(0), iPlayerDeadCheck_p(false)
{
//	cout << "Player()" << endl;
	Reset_p();
	for(int i = 0; i < 5 ; i++)
		iUserInfoOutput_Stack[i] = INT_MAX;
}
_clPlayer::~_clPlayer() 
{
//	cout << "~Player()" << endl;
}

void _clPlayer::SetPos_p(const int Xpos, const int Ypos)	// 플레이어의 위치를 입력하는 함수 
{
	iXpos_p = Xpos;	// 플레이어의 위치를 저장할 변수 
	iYpos_p = Ypos;
	return;
}

void _clPlayer::SetPos_op(int Xpos, const int Ypos)	// 콘솔사엥서의 플레이어 좌표를 저장하는 함수 
{
	if(Xpos > 0)Xpos *= 2;
	iXpos_op = Xpos;	// 플레이어의 위치를 저장할 변수 
	iYpos_op = Ypos;
	return;
}

void _clPlayer::Reset_p()	// 플레이어의 상태를 처음으로 만드는 함수
{
	iLife_p--;
	iMoving = PM_NONE;
	iMovingB_p = PM_NONE;
	bJumpState_p = false;	// 점프상태 아님 
	iJumpMax_p = 3;			// 최대 점프치 3 
	Player_Grade(false);		// 강화되지 않음 
	bullet_p = 0;			// 총알수 0
	CoinStackB_p = 0;
	iPlayerDeadCheck_p = false;
	SetPos_p(iXpos_ST,iYpos_ST);
	return;
}

bool _clPlayer::Player_Grade(bool bGrade)	// 플레이어를 업그레이드하거나 취소하는 함수
{
	switch(bGrade)
	{
		case true:
			Upgrade_p = true;
			iJumpMax_p = 4;
			return true;
		case false:
			Upgrade_p = false;
			iJumpMax_p = 3;
			return false;
	}
}

_clPlayer::OutPutPlayer_INFO()	// 맵에 플레이어의 상태를 알려주는 창을 띄우는 함수
{
	static int iStage_b = 1;
	static int temp = 0;
	temp++;
	gotoxy(34, 13);
	if(iUserInfoOutput_Stack[0] == INT_MAX || bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "┌───────────────┐";
	gotoxy(34, 14);
	if(iUserInfoOutput_Stack[0] != iStage|| bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "│           STAGE  " << iStage << "           │";
	gotoxy(34, 15);
	if(iUserInfoOutput_Stack[1] != iLife_p|| bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "│           LIFE  / " << iLife_p << "          │";
	gotoxy(34, 16);
	if(iUserInfoOutput_Stack[2] != CoinStack_p + CoinStackB_p|| bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "│           COIN  /  " << CoinStack_p + CoinStackB_p;
		if(CoinStack_p < 10)cout << " ";
		cout << "        │";
	}
	gotoxy(34, 17);
	if(iUserInfoOutput_Stack[3] != bullet_p || bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "│         BULLET  /  " << bullet_p; 
		if(bullet_p < 10)cout << " "; 
		cout << "        │";
	}
	gotoxy(34, 18);
	if(iUserInfoOutput_Stack[4] != Upgrade_p || bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "│       POWER MODE  /  ";	
		if(Upgrade_p == true)cout << "ON "; 
		else cout <<"OFF"; 
		cout << "     │";
	}
	gotoxy(34, 19);
	if(iUserInfoOutput_Stack[0] == INT_MAX || bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "└───────────────┘";
	gotoxy(34, 20);
	cout << "iMoving : " << iMoving << endl;
	gotoxy(34, 21);
	cout << "iMovingB_p : " << iMovingB_p << endl;
	gotoxy(34, 22);
	cout << "PM_NONE : " << PM_NONE << endl;
	gotoxy(34, 23);
	cout << "PM_LEFT : " << PM_LEFT << endl;
	gotoxy(34, 24);
	cout << "PM_RIGHT : " << PM_RIGHT << endl;
	iUserInfoOutput_Stack[0] = iStage;
	iUserInfoOutput_Stack[1] = iLife_p;
	iUserInfoOutput_Stack[2] = CoinStack_p + CoinStackB_p;
	iUserInfoOutput_Stack[3] = bullet_p;
	iUserInfoOutput_Stack[4] = Upgrade_p;
	bUserInfo_Reprint = false;
	if(iStage_b != iStage)iStage_b = iStage;
}

_clPlayer::MOB_LEFT(const int Count)
{
	
	if(Check_Wall(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1], 3) == false)return false;	// 벽, 몬스터, 시작,도착점이면 이동실패
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] == '5')return false;	// 바로옆이 가시면 이동하지 않음 
	else if(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m - 1] == '5')	// 아래가 가시면 으앙주금 
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		UnActiveMOB(Count);
		return true;
	}
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] == '2')
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] == '9' || cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] == 'B')
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] = '0';
		UnActiveMOB(Count);
		return true;
	}
	cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
	cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] = 'C';
	MOB[Count].InputPOS_m(MOB[Count].iXpos_m - 1, MOB[Count].iYpos_m);
	if(Check_Wall(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m], 3) == true)
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m] = 'C';
		MOB[Count].InputPOS_m(MOB[Count].iXpos_m, MOB[Count].iYpos_m + 1);
	}
	return true;
}

_clPlayer::MOB_RIGHT(const int Count)
{
	if(Check_Wall(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1], 3) == false)return false;	// 벽, 몬스터, 시작,도착점이면 이동실패 
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] == '5')return false;	// 바로옆이 가시면 이동하지 않음 
	else if(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m + 1] == '5')	// 아래가 가시면 으앙주금 
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		UnActiveMOB(Count);
		return true;
	}
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] == '2')
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] == '9' || cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] == 'B')
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] = '0';
		UnActiveMOB(Count);
		return true;
	}
	cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
	cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] = 'C';
	MOB[Count].InputPOS_m(MOB[Count].iXpos_m + 1, MOB[Count].iYpos_m);
	if(Check_Wall(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m], 3) == true)
	{
		cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m] = '0';
		cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m] = 'C';
		MOB[Count].InputPOS_m(MOB[Count].iXpos_m, MOB[Count].iYpos_m + 1);
	}
	return true;
}

_clPlayer::Search_Move()
{
	static int iMOB_MoveCount = 6;
	if(iMOB_MoveCount == 0)
	{
		for(int i = 0; i < 10; i++)
		{
			if(MOB[i].bActiveMOB == true)
			{
				for(int j = 1; j < MOB[i].iSearchRange; j++)
				{
					if(cMap[MOB[i].iYpos_m][MOB[i].iXpos_m - j] == '2' )
						MOB_LEFT(i);
				}
				for(int j = 1; j < MOB[i].iSearchRange; j++)
				{
					if(cMap[MOB[i].iYpos_m][MOB[i].iXpos_m + j] == '2' )
						MOB_RIGHT(i);
				}
			}
		}	
	}
	iMOB_MoveCount++;
	if(iMOB_MoveCount >= 7)iMOB_MoveCount = 0;
}
