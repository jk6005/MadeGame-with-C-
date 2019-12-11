#include "core.h"

void gotoxy(int x,int y)
{
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void Clean_Cussor()	// Ŀ���� ����� �Լ� 
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

void _clMap::ActiveMOB(int Mob)	// ���� Ȱ��ȭ�ϴ� �Լ� 
{
	MOB[Mob].bActiveMOB = true;
	return;
}

void _clMap::UnActiveMOB(int Mob)	// ���� ��Ȱ��ȭ �ϴ� �Լ� 
{
	MOB[Mob].bActiveMOB = false;
	MOB[Mob].iXpos_m = INT_MAX;
	MOB[Mob].iYpos_m = INT_MAX;
	MOB[Mob].iXpos_om = INT_MAX;
	MOB[Mob].iYpos_om = INT_MAX;
	bMOB_ACTIVE[Mob] = false;
	return;
}

_clMap::_clMap() : iStage(1), bUserInfo_Reprint(false)	// �����ɋ� 1���������� �д´�. 
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

_clMap::Check_Wall(char Move, int iType)	// �÷��̾��� �浹���� �� ��ȯ 
{
	switch(iType)
	{
		case 1:
			if(Move == '1' || Move == '3' || Move == '6')return false;	// ������, ��, ���Ѻ� �̸� ����! 
			else return true;
		case 2:	// �Ѿ˹߽� üũ 
			if(Move == '0' || Move == 'C')
				return true;
			else return false;
		case 3:	// ������ �浹 ����
			if(Move == '1' || Move == '3' || Move == '4' || Move == 'C') 
				return false;
			else return true;
	}
}

bool _clMap::ReadStage(const int iStage_Num)	// ���� �д� �Լ�
{
	FILE *pFile = NULL;
	switch(iStage_Num)	// �Է¹��� ���ڷ� ���� �����Ѵ� 
	{
		case 1:
			fopen_s(&pFile, "stage1.txt", "r+t");
			break;
		case 2:
			fopen_s(&pFile, "stage2.txt", "r+t");
			break;
	}
	if(pFile)	// ���б� �� �����ϸ� ���� �а� true �� ��ȯ�Ѵ� 
	{
		for(int y = 0; y < 10; y++)
			for(int x = 0; x < 50; x++)
			{
				fread(&cMap[y][x], sizeof(char), 1, pFile);
				if(cMap[y][x] == '\n')fread(&cMap[y][x], sizeof(char), 1, pFile);	// �дٰ� ������ �κп� \n �� ������ �����ϰ� �ѹ� �� �б� 
			}
		fclose(pFile);
	}
	else	// ���н� false ��ȯ 
	{
		system("cls");
		cout << "stage" << iStage_Num << ".txt ���б� ����!" << endl;
		return false;
	}
	return true;
	
}

void _clMap::ResetMOB()	// ���� �ʱ�ȭ 
{
	for(int i = 0; i < 10; i++)
	{
		UnActiveMOB(i);
	}
	return;
}

/*
0	"  " ����
1 	"��" ���Ѻ�
2	"��" �÷��̾� 
3	"��" ������
4	"��" ������ 
5	"��" ���� 
6	"��" ���Ѻ� 
7	"��" ��ȭ��
8	"��" ź�� 
9 	"��" ���� �Ѿ� 
A	"��" ���� 
B	"��" ������ �Ѿ�
C	"��" ���� 
*/

// == �÷��̾� Ŭ����

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

void _clPlayer::SetPos_p(const int Xpos, const int Ypos)	// �÷��̾��� ��ġ�� �Է��ϴ� �Լ� 
{
	iXpos_p = Xpos;	// �÷��̾��� ��ġ�� ������ ���� 
	iYpos_p = Ypos;
	return;
}

void _clPlayer::SetPos_op(int Xpos, const int Ypos)	// �ֻܼ翨���� �÷��̾� ��ǥ�� �����ϴ� �Լ� 
{
	if(Xpos > 0)Xpos *= 2;
	iXpos_op = Xpos;	// �÷��̾��� ��ġ�� ������ ���� 
	iYpos_op = Ypos;
	return;
}

void _clPlayer::Reset_p()	// �÷��̾��� ���¸� ó������ ����� �Լ�
{
	iLife_p--;
	iMoving = PM_NONE;
	iMovingB_p = PM_NONE;
	bJumpState_p = false;	// �������� �ƴ� 
	iJumpMax_p = 3;			// �ִ� ����ġ 3 
	Player_Grade(false);		// ��ȭ���� ���� 
	bullet_p = 0;			// �Ѿ˼� 0
	CoinStackB_p = 0;
	iPlayerDeadCheck_p = false;
	SetPos_p(iXpos_ST,iYpos_ST);
	return;
}

bool _clPlayer::Player_Grade(bool bGrade)	// �÷��̾ ���׷��̵��ϰų� ����ϴ� �Լ�
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

_clPlayer::OutPutPlayer_INFO()	// �ʿ� �÷��̾��� ���¸� �˷��ִ� â�� ���� �Լ�
{
	static int iStage_b = 1;
	static int temp = 0;
	temp++;
	gotoxy(34, 13);
	if(iUserInfoOutput_Stack[0] == INT_MAX || bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "����������������������������������";
	gotoxy(34, 14);
	if(iUserInfoOutput_Stack[0] != iStage|| bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "��           STAGE  " << iStage << "           ��";
	gotoxy(34, 15);
	if(iUserInfoOutput_Stack[1] != iLife_p|| bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "��           LIFE  / " << iLife_p << "          ��";
	gotoxy(34, 16);
	if(iUserInfoOutput_Stack[2] != CoinStack_p + CoinStackB_p|| bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "��           COIN  /  " << CoinStack_p + CoinStackB_p;
		if(CoinStack_p < 10)cout << " ";
		cout << "        ��";
	}
	gotoxy(34, 17);
	if(iUserInfoOutput_Stack[3] != bullet_p || bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "��         BULLET  /  " << bullet_p; 
		if(bullet_p < 10)cout << " "; 
		cout << "        ��";
	}
	gotoxy(34, 18);
	if(iUserInfoOutput_Stack[4] != Upgrade_p || bUserInfo_Reprint == true || iStage != iStage_b)
	{
		cout << "��       POWER MODE  /  ";	
		if(Upgrade_p == true)cout << "ON "; 
		else cout <<"OFF"; 
		cout << "     ��";
	}
	gotoxy(34, 19);
	if(iUserInfoOutput_Stack[0] == INT_MAX || bUserInfo_Reprint == true || iStage != iStage_b)
		cout << "����������������������������������";
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
	
	if(Check_Wall(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1], 3) == false)return false;	// ��, ����, ����,�������̸� �̵�����
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m - 1] == '5')return false;	// �ٷο��� ���ø� �̵����� ���� 
	else if(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m - 1] == '5')	// �Ʒ��� ���ø� �����ֱ� 
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
	if(Check_Wall(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1], 3) == false)return false;	// ��, ����, ����,�������̸� �̵����� 
	if(cMap[MOB[Count].iYpos_m][MOB[Count].iXpos_m + 1] == '5')return false;	// �ٷο��� ���ø� �̵����� ���� 
	else if(cMap[MOB[Count].iYpos_m + 1][MOB[Count].iXpos_m + 1] == '5')	// �Ʒ��� ���ø� �����ֱ� 
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
