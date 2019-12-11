#include "Interface.h"

_clHandle::_clHandle()
{
//	cout << "_clHandle()" << endl; 
}
_clHandle::~_clHandle()
{
//	cout << "~_clHandle" << endl; 
}

void _clHandle::Output_Main()	// 메인화면을 출력하는 함수
{
	system("mode con cols=47 lines=13");
	cout << "　　　　　　　　　　　　　　　　　　　　　　　" << endl;
	cout << "　　　□□□□□□□□□□□□□□□□□　　　" << endl;
	cout << "　　□□□□□□□□　Running □□□□□□　　" << endl;
	cout << "　□□□□□□□□□□          □□□□□□　" << endl;
	cout << "□□□□□□□□□□□□　DOS　 □□□□□□□" << endl;
	cout << "□□□□□□□□□□□□□□□□□□□□□□□" << endl;
	cout << "♧　　　　　　　　　　　　　　　　　　　　　♣" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	cout << "□□□□□□□□□□□□□□□□□□□□□□□" << endl;
	cout << "　□□□□ - PRESS ANYKEY - □□□□□□□□　" << endl;
	cout << "　　□□□□□□□□□□□□□□□□□□□　　" << endl;
	cout << "　　　□□□□□□□□□□□□□□□□□　　　" << endl;
	
	int x = 2, y = 6;
	int x_c = x;
	while(1)	// 일직선으로 애니메이션 효 
	{
		Sleep(300);
		if(kbhit() == true)	// 아무키나 입력되면 반복종료 
		{
			getch();
			return;
		}
		gotoxy(x, y);
		cout << "§" ;
		if(x != 2)
		{
			gotoxy(x_c, y);
			cout << "　";
		}
		if(x == 44)
		{
			gotoxy(x, y);
			x = 2;
			cout << "♣";
		}
		x_c = x;
		x += 2;
	}
}

void _clHandle::Output_Explain()	// 게임방법을 알려주는 함수
{
	system("mode con cols=47 lines=15");
	system("cls");
	cout << "　　　　　　　《　How to Play?　》　　　　　　" << endl;
	cout << "　　　　　　　　《　게임방법　》　　　　　　　" << endl;
	cout << "　　　　　　　　　　　　　　　　　　　　　　　" << endl;
	cout << "　　　←　→　　　　　 Z　    　　　　 X　  　" << endl;
	cout << "　　　　　　　　　　　　　　　　　　　　　　　" << endl;
	cout << "　좌우 방향키로　　Z 버튼으로　　 X 버튼으로  " << endl;
	cout << "　　움직이기!　　　　점프!　　　　총알 발사!　" << endl;
	cout << "　　　　　　　　　　　　　　　　　　　　　　　" << endl;
	cout << "　♣ : 이곳에 도착하면 스테이지 클리어! 　　　" << endl;
	cout << "　㉿ : 강화아이템 먹으면 벽돌을 부실수 있다!　" << endl;
	cout << "　＆ : 총알 먹으면 탄약수가 늘어난다!　　　 　" << endl;
	cout << "　♡ : 목숨이 0 에도달하면 게임패배!　　　　　" << endl;		
	cout << "　　　　　　　　　　　　　　　　　　　　　　　" << endl;
	cout << "　　　　　  　- PRESS ANYKEY -  　　　　　　　" << endl;
	getch();

}

void _clHandle::Output_Life_Stage()	// 목숨과 라이프를 보여주는 함수 
{
	system("mode con cols=101 lines=30");
	gotoxy(46, 12);
	cout << "Stage " << iStage << endl;
	gotoxy(44, 14);
	cout << "LIFE ♡ : " << iLife_p << endl;
	sleep(3);
	system("cls");
	return;
}

void _clHandle::Output_Claer_Stage()	// 클리어화면 출력 
{
	system("mode con cols=101 lines=30");
	gotoxy(46, 13);
	cout << "Stage" << iStage <<  " Clear!!" << endl;
	sleep(3);
	system("cls");
	return;
}

void _clHandle::Output_Dead_Stage()	// 게임오버 화면7 출력 
{
	system("mode con cols=101 lines=30");
	gotoxy(46, 13);
	cout << "    YOU DEAD" << endl;
	gotoxy(46, 15);
	cout << "G A M E  O V E R" << endl;
	sleep(3);
	system("cls");
	return;
}

void _clHandle::Print_Map()	// 맵을 출력하는 함수
{
	system("mode con cols=101 lines=30") ;
	int iMob_Count = 0;
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 50; x++)
		{
			if(cMap[y][x] == '0')
				cout << "  ";
			else if(cMap[y][x] == '1') 
				cout << "■";
			else if(cMap[y][x] == '2')
				cout << "§";
			else if(cMap[y][x] == '3')
			{
				cout << "♧";
				iXpos_ST = x;	// 시작점 위치 저장 
				iYpos_ST = y;
			}
			else if(cMap[y][x] == '4')
			{
				cout << "♣"; 
				iXpos_CT = x;	// 도착지점을 저장하는 변수 
				iYpos_CT = y;
			}
			else if(cMap[y][x] == '5')
				cout << "＃"; 
			else if(cMap[y][x] == '6')
				cout << "□"; 
			else if(cMap[y][x] == '7')
				cout << "㉿"; 
			else if(cMap[y][x] == '8')
				cout << "＆"; 
			else if(cMap[y][x] == '9')
				cout << "º"; 
			else if(cMap[y][x] == 'A')
				cout << "○"; 
			else if(cMap[y][x] == 'B')
				cout << "º"; 
			else if(cMap[y][x] == 'C')
			{
				bMOB_ACTIVE[iMob_Count] = true;
				ActiveMOB(iMob_Count);
				MOB[iMob_Count].InputPOS_m(x,y);
				MOB[iMob_Count].InputPOS_om(x,y);
				iMob_Count++;
				cout << "＠"; 
			}
		}
		cout << endl;
	}
	SetPos_p(iXpos_ST, iYpos_ST);	// 맵출력이 완료되면 플레이어의 위치를 시작점으로 맞춘다. 
	SetPos_op(iXpos_ST, iYpos_ST);	// 콘솔좌표상의 플레이어 좌표를 입력한다
	return;
}

void _clHandle::RePrint_Map()	// 맵을 수정하는 함수
{
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 50; x++)
			if(cMap[y][x] != cMap_Cpy[y][x])	// 수정한 맵이 기존에 전에 있던 맵과 다르면 그부븐을 재수정한다. 
			{
				cMap_Cpy[y][x] = cMap[y][x];	// 변경된 값을 같게 만들어준다
				gotoxy(x * 2, y);
				if(cMap[y][x] == '0')
					cout << "  ";
				else if(cMap[y][x] == '1') 
					cout << "■";
				else if(cMap[y][x] == '2')
					cout << "§";
				else if(cMap[y][x] == '3')
					cout << "♧";
				else if(cMap[y][x] == '4')
					cout << "♣"; 
				else if(cMap[y][x] == '5')
					cout << "＃"; 
				else if(cMap[y][x] == '6')
					cout << "□"; 
				else if(cMap[y][x] == '7')
					cout << "㉿"; 
				else if(cMap[y][x] == '8')
					cout << "＆"; 
				else if(cMap[y][x] == '9')
					cout << "º"; 
				else if(cMap[y][x] == 'A')
					cout << "○"; 
				else if(cMap[y][x] == 'B')
					cout << "º"; 
				else if(cMap[y][x] == 'C')
					cout << "＠"; 
			}
	}
}

/*
PlAYER_MOVE
0		PM_NONE
1		PM_LEFT,
2		PM_RIGHT,
3		PM_JUMP,
4		PM_FIRE
*/

int _clHandle::Player_Moving()	// 플레이어 의 키보드값을 받는 함수
{
	if((GetAsyncKeyState(VK_LEFT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000) && (GetAsyncKeyState(0x58) & 0x8000))	// 왼쪽위로 점프 하면서 발사 
	{
		Player_Jump();
		Player_Left();
		Player_Fire();
		return PM_LEFT;
	}
	else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000) && (GetAsyncKeyState(0x58) & 0x8000))	// 오른쪽 위로 점프  하면서 발사 
	{
		Player_Jump();
		Player_Right();
		Player_Fire();
		return PM_RIGHT;
	}
	else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// 왼쪽위로 점프 
	{
		Player_Jump();
		Player_Left();
		return PM_LEFT;
	}
	else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// 오른쪽 위로 점프 
	{
		Player_Jump();
		Player_Right();
		return PM_RIGHT;
	}
	else if((GetAsyncKeyState(0x58) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// 점프하면서  발사
	{
		Player_Jump();
		Player_Fire();
		return iMovingB_p;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000 && (GetAsyncKeyState(VK_RIGHT) & 0x8000))	// 오른쪽으로 움직이면서 발사
	{
		Player_Right();
		Player_Fire();
		return PM_RIGHT;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000 && (GetAsyncKeyState(VK_LEFT) & 0x8000))	// 왼쪽으로 움직이면서 발사 
	{
		Player_Left();
		Player_Fire();
		return PM_LEFT;
	}
	else if(GetAsyncKeyState(VK_LEFT) & 0x8000)	// 왼쪽 방향키 	왼쪽 
	{
		Player_Left();
		return PM_LEFT;
	}
	else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)	// 오른쪽 방향키
	{
		Player_Right();
		return PM_RIGHT;		
	}
	else if(GetAsyncKeyState(0x5A) & 0x8000)	// z 키 	점프 
	{
		Player_Jump();
		return iMovingB_p;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000)	// x 키 	 발사 
	{
		Player_Fire();
		return iMovingB_p;
	}
	else PM_NONE;
}

_clHandle::Check_Fall()	// 플레이어 낙하 판정 반환 
{
	if(iYpos_p == 9 || bJumpState_p == true)	// 플레이어가 점프중이거나 맨바닦일떄는 낙하 하지 않는다. 
		return false;
	if(Check_Wall(cMap[iYpos_p + 1][iXpos_p], 1) != false)	// 플레이어 의 바닥이 통과 가능하다면
	{
		if(cMap[iYpos_p + 1][iXpos_p] == '5')	// 가시판정 
		{
			cMap[iYpos_p][iXpos_p] = '0';
			iPlayerDeadCheck_p = true;
			return 0; 
		}
		else if(cMap[iYpos_p + 1][iXpos_p] == 'A')	// 동전판정
			CoinStackB_p++;
		else if(cMap[iYpos_p + 1][iXpos_p] == '7')	// 강화약 판정 
			Player_Grade(true);
		else if(cMap[iYpos_p + 1][iXpos_p] == '8')	// 탄약 판정
			bullet_p++;
		else if(cMap[iYpos_p + 1][iXpos_p] == 'C')	// 몬스터 밟기
		{
			for(int i = 0; i < 10; i++)
			{
				if((iYpos_p + 1) == MOB[i].iYpos_m && iXpos_p == MOB[i].iXpos_m)
				{
					MOB[i].bActiveMOB = false;
					bMOB_ACTIVE[i] = false;
				}
			}
		} 
		cMap[iYpos_p][iXpos_p] = '0';
		SetPos_p(iXpos_p, iYpos_p + 1);
		cMap[iYpos_p][iXpos_p] = '2';
		SetPos_op(iXpos_p, iYpos_p);
	}
	else return false; 
}

_clHandle::Player_Left()	// 왼쪽으로 플레이어 이동 
{
	if(iXpos_p < 1 || Check_Wall(cMap[iYpos_p][iXpos_p - 1], 1) == false)return false;	// 왼쪽 첫칸일경우 이동불가 
	else if(cMap[iYpos_p][iXpos_p - 1] == '5' || cMap[iYpos_p][iXpos_p - 1] == 'C')	// 가시판정 & 몬스터 판정 
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[iYpos_p][iXpos_p - 1] == '7')	// 강화약 판정 
		Player_Grade(true);
	else if(cMap[iYpos_p][iXpos_p - 1] == 'A')	// 동전판정
		CoinStackB_p++;
	else if(cMap[iYpos_p][iXpos_p - 1] == '8')	// 탄약 판정
		bullet_p++; 
	if(cMap[iYpos_p][iXpos_p] == '3')	// 만약 전칸이 스타트포인트면 지우지않는다.
		cMap[iYpos_p][iXpos_p] = '3';
	else cMap[iYpos_p][iXpos_p] = '0';
	SetPos_p(iXpos_p - 1, iYpos_p);	// 왼쪽으로 한칸이동 
	cMap[iYpos_p][iXpos_p] = '2';
	SetPos_op(iXpos_p, iYpos_p);	// 이미 이동한후이니 대입만 한다 
}

_clHandle::Player_Right()	// 오른쪽으로 플레이어 이동 
{
	if(iXpos_p > 48 || Check_Wall(cMap[iYpos_p][iXpos_p + 1], 1) == false)return false;	// 오른쪽 끝칸일경우 이동불가
	if(cMap[iYpos_p][iXpos_p + 1] == '5' || cMap[iYpos_p][iXpos_p + 1] == 'C')	// 가시판정 & 몬스터 판정 
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[iYpos_p][iXpos_p + 1] == '7')	// 강화약 판정 
		Player_Grade(true);
	else if(cMap[iYpos_p][iXpos_p + 1] == 'A')	// 동전판정
		CoinStackB_p++;
	else if(cMap[iYpos_p][iXpos_p + 1] == '8')	// 탄약 판정
		bullet_p++;
	if(cMap[iYpos_p][iXpos_p] == '3')	// 만약 전칸이 스타트포인트면 지우지않는다.
		cMap[iYpos_p][iXpos_p] = '3';
	else cMap[iYpos_p][iXpos_p] = '0';
	SetPos_p(iXpos_p + 1, iYpos_p); 
	cMap[iYpos_p][iXpos_p] = '2';
	SetPos_op(iXpos_p, iYpos_p);
}

_clHandle::Player_Jump()	// 점프하는 플레이어 이동
{
	if(iYpos_p < 1 || Check_Wall(cMap[iYpos_p - 1][iXpos_p], 1) == false)
	{
		if(cMap[iYpos_p - 1][iXpos_p] == '6' && Upgrade_p == true)	// 아래가 공기가 아니고 바로위에 벽이 있을경우에만 
		{
			if(cMap[iYpos_p + 1][iXpos_p] != '0')
				cMap[iYpos_p - 1][iXpos_p] = '0';
			else if(iJumpRemain_p > 1)
				cMap[iYpos_p - 1][iXpos_p] = '0';
		}
		iJumpRemain_p = 0;
		return false;	// 위칸이 맵의 끝이거나 못움직이는 칸이면 이동불가 + 점프중일떈 점프불가 
	}
	if(iJumpRemain_p > 1 || bJumpState_p == true|| cMap[iYpos_p + 1][iXpos_p] == '0' || cMap[iYpos_p + 1][iXpos_p] == '5' || cMap[iYpos_p + 1][iXpos_p] == 'A' || cMap[iYpos_p + 1][iXpos_p] == 'C')return false;
	bJumpState_p = true;	// 점프상태 활성화 
	iJumpRemain_p = iJumpMax_p;	// 점프부여 
}

_clHandle::Chack_Up()	// 플레이어의 상승 판정 반환
{
	if(iYpos_p < 1 || Check_Wall(cMap[iYpos_p - 1][iXpos_p], 1) == false || bJumpState_p == false || iJumpRemain_p < 1)
	{
		if(iYpos_p < 1 && iJumpRemain_p > 0)	// 천장에 닿앗는데 점프가남앗으면 칸수만 줄이고 내려가진 않는다. 
		{
			iJumpRemain_p--;
			return false;
		}
		if(cMap[iYpos_p - 1][iXpos_p] == '6' && iJumpRemain_p > 0 && Upgrade_p == true)	// 아래가 공기가 아니고 바로위에 벽이 있을경우에만 
			cMap[iYpos_p - 1][iXpos_p] = '0';
		iJumpRemain_p = 0;
		bJumpState_p = false; 
		return false;	// 맵의 정상 부분이거나 벽에 부딕치거나 점프중이 아닐떄는 점프취소 
	}
	if(iJumpRemain_p > 0)
	{
		if(cMap[iYpos_p - 1][iXpos_p] == '5')	// 가시판정 
		{
			cMap[iYpos_p][iXpos_p] = '0';
			iPlayerDeadCheck_p = true;
			return 0; 
		}
		else if(cMap[iYpos_p - 1][iXpos_p] == '7')	// 강화약 판정 
			Player_Grade(true);
		else if(cMap[iYpos_p - 1][iXpos_p] == 'A')	// 동전판정
			CoinStackB_p++;
		else if(cMap[iYpos_p - 1][iXpos_p] == '8')	// 탄약 판정
			bullet_p++;
		if(cMap[iYpos_p][iXpos_p] == '3')	// 만약 전칸이 스타트포인트면 지우지않는다.
			cMap[iYpos_p][iXpos_p] = '3';
		else cMap[iYpos_p][iXpos_p] = '0';
		SetPos_p(iXpos_p, iYpos_p - 1); 
		cMap[iYpos_p][iXpos_p] = '2';
		SetPos_op(iXpos_p, iYpos_p);
		iJumpRemain_p--;
	}
	
	if(Check_Wall(cMap[iYpos_p + 1][iXpos_p], 1) == false && iJumpRemain_p == 0)iJumpRemain_p++;
}

_clHandle::Player_Fire()	// 총을 발사하는 함수 
{
	if(bullet_p < 1)return false;	// 총알이 없으면 실패 
	int iFlag;
	if(iMovingB_p == PM_LEFT)iFlag = -1;else if(iMovingB_p == PM_RIGHT)iFlag = 1;	// 왼쪽이면 -1 오른쪽이면 +1
	bullet_p--;	// 총알 소모
	if(Check_Wall(cMap[iYpos_p][iXpos_p + iFlag], 2) == false)	// 총알이 생성될수 있으면 true 아니면 false
		return false;
	if(iFlag == -1) 
	{
		if(cMap[iYpos_p][iXpos_p + iFlag] == 'C')
		{
			for(int i = 0; i < 10; i++)
			{
				if(iYpos_p == MOB[i].iYpos_m && (iXpos_p + iFlag) == MOB[i].iXpos_m)
				{
					UnActiveMOB(i);
					bMOB_ACTIVE[i] = false;
					cMap[iYpos_p][iXpos_p + iFlag] = '0';
				}
			}
		}
		else
			cMap[iYpos_p][iXpos_p + iFlag] = '9';
	}
	else if(iFlag == 1)
	{
		if(cMap[iYpos_p][iXpos_p + iFlag] == 'C')
		{
			for(int i = 0; i < 10; i++)
			{
				if(iYpos_p == MOB[i].iYpos_m && (iXpos_p + iFlag) == MOB[i].iXpos_m)
				{
					UnActiveMOB(i);
					bMOB_ACTIVE[i] = false;
					cMap[iYpos_p][iXpos_p + iFlag] = '0';
				}
			}
		}
		else
			cMap[iYpos_p][iXpos_p + iFlag] = 'B';	
	}
	return true;
}

_clHandle::Bullet_Moving()	// 총알 이동
{
	int LBullet_C = 0;	// 왼쪽 총알 정보를 저장 
	int LBullet_X[100] = {};
	int LBullet_Y[100] = {};
	int RBullet_C = 0;	// 오른쪽 총알 정보를 저장 
	int RBullet_X[100] = {};
	int RBullet_Y[100] = {};
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 50; x++)
		{
			if(cMap[y][x] == '9')	// 왼쪽 총알 
			{
				LBullet_X[LBullet_C] = x; 
				LBullet_Y[LBullet_C] = y;
				LBullet_C++;
			}
			else if(cMap[y][x] == 'B')	// 오른쪽 총알 
			{
				RBullet_X[RBullet_C] = x; 
				RBullet_Y[RBullet_C] = y;
				RBullet_C++;
			}
		}
	}
	for(int i = 0; i < LBullet_C; i++)	// 왼쪽 총알은 가장 왼쪽에 있는 총알부터 연산
	{
		if(Check_Wall(cMap[LBullet_Y[i]][LBullet_X[i] - 1], 2) == false)
			cMap[LBullet_Y[i]][LBullet_X[i]] = '0';
		else
		{
			if(cMap[LBullet_Y[i]][LBullet_X[i] - 1] == 'C')
			{
				for(int j = 0; j < 10; j++)
				{
					if(LBullet_Y[i] == MOB[j].iYpos_m && (LBullet_X[i] - 1) == MOB[j].iXpos_m)
					{
						UnActiveMOB(j);
						bMOB_ACTIVE[j] = false;
						cMap[LBullet_Y[i]][LBullet_X[i]] = '0';
						cMap[LBullet_Y[i]][LBullet_X[i] - 1] = '0';
					}
				}
			}
			else cMap[LBullet_Y[i]][LBullet_X[i] - 1] = '9';
			cMap[LBullet_Y[i]][LBullet_X[i]] = '0';
		}
	}
	for(int i = RBullet_C - 1; i > -1; i--) 	// 오른쪽 총알은 가장 오른쪽에 있는 총알부터 연산 
	{
		gotoxy(0, 20);
		cout << "RBullet_C = " << RBullet_C << endl;
		cout << "[RBullet_Y[i]] = " << RBullet_Y[i] << endl; 
		cout << "[RBullet_X[i]] = " << RBullet_X[i] << endl;
		if(Check_Wall(cMap[RBullet_Y[i]][RBullet_X[i] + 1], 2) == false)
			cMap[RBullet_Y[i]][RBullet_X[i]] = '0';
		else
		{
			if(cMap[RBullet_Y[i]][RBullet_X[i] + 1] == 'C')
			{
				for(int j = 0; j < 10; j++)
				{
					if(RBullet_Y[i] == MOB[j].iYpos_m && (RBullet_X[i] + 1) == MOB[j].iXpos_m)
					{
						UnActiveMOB(j);
						bMOB_ACTIVE[j] = false;
						cMap[RBullet_Y[i]][RBullet_X[i]] = '0';
						cMap[RBullet_Y[i]][RBullet_X[i] + 1] = '0';
					}
				}
			}
			else cMap[RBullet_Y[i]][RBullet_X[i] + 1] = 'B';
			cMap[RBullet_Y[i]][RBullet_X[i]] = '0';
		}
	}
}

bool _clHandle::Playing_Game()	// 게임을 시작하는 함수 
{
	if(ReadStage(iStage) == false)	// 맵 읽기 
		return false;
	Output_Life_Stage();	// 목숨 및 스테이지 표시 
	Print_Map();		// 맵 출력
	int Temp = 0;
	while(1)
	{
		if(iYpos_p == iYpos_CT && iXpos_p == iXpos_CT)	// 도착점 도착시 
		{
			Output_Claer_Stage();	// 스테이지 클리어 화면으로 전환 및 
			iStage++;	// 스테이지 상승 
			return true; 	// 성공반환 
		}
		Search_Move();
		if(iPlayerDeadCheck_p == true)	// 만약 플레이어가 죽엇으면
		{
			if(iLife_p == 0)	// 목숨을 다하면 게임종료 
			{
				Output_Dead_Stage();
				return false;
			}
			ResetMOB();
			ReadStage(iStage);	// 맵을 다시 읽는다. 
			Reset_p();	// 플레이어 정보를 리셋한다. 
			bUserInfo_Reprint = true;	// 유저 인터페이스를 초기화한다. 
			Output_Life_Stage();	// 로딩맵 출력 
			Print_Map();	// 맵 재출력 
		}
		RePrint_Map();	// 맵을 계속 수정한다.
		Bullet_Moving();	// 총알 이동 
		OutPutPlayer_INFO();	// 플레이어 정보출력 
		
		iMoving = Player_Moving();	// 새로운 이동방향 입력 
		if(iMoving != PM_NONE)iMovingB_p = iMoving;	// 총알 방향 결정을위해 이동방향 저장 
		
		Chack_Up();	// 상승 확인 
		Check_Fall();	// 하강 확인 
		Sleep(150);
	}
	
}
