#include "Interface.h"

_clHandle::_clHandle()
{
//	cout << "_clHandle()" << endl; 
}
_clHandle::~_clHandle()
{
//	cout << "~_clHandle" << endl; 
}

void _clHandle::Output_Main()	// ����ȭ���� ����ϴ� �Լ�
{
	system("mode con cols=47 lines=13");
	cout << "����������������������������������������������" << endl;
	cout << "�����������������������ࡡ����" << endl;
	cout << "������������ࡡRunning ������ࡡ��" << endl;
	cout << "�������������          ������ࡡ" << endl;
	cout << "������������ࡡDOS�� ��������" << endl;
	cout << "������������������������" << endl;
	cout << "����������������������������������������������" << endl;
	cout << "������������������������" << endl;
	cout << "������������������������" << endl;
	cout << "������� - PRESS ANYKEY - ��������ࡡ" << endl;
	cout << "�����������������������ࡡ��" << endl;
	cout << "�����������������������ࡡ����" << endl;
	
	int x = 2, y = 6;
	int x_c = x;
	while(1)	// ���������� �ִϸ��̼� ȿ 
	{
		Sleep(300);
		if(kbhit() == true)	// �ƹ�Ű�� �ԷµǸ� �ݺ����� 
		{
			getch();
			return;
		}
		gotoxy(x, y);
		cout << "��" ;
		if(x != 2)
		{
			gotoxy(x_c, y);
			cout << "��";
		}
		if(x == 44)
		{
			gotoxy(x, y);
			x = 2;
			cout << "��";
		}
		x_c = x;
		x += 2;
	}
}

void _clHandle::Output_Explain()	// ���ӹ���� �˷��ִ� �Լ�
{
	system("mode con cols=47 lines=15");
	system("cls");
	cout << "������������������How to Play?����������������" << endl;
	cout << "�����������������������ӹ��������������������" << endl;
	cout << "����������������������������������������������" << endl;
	cout << "�������硡�桡�������� Z��    �������� X��  ��" << endl;
	cout << "����������������������������������������������" << endl;
	cout << "���¿� ����Ű�Ρ���Z ��ư���Ρ��� X ��ư����  " << endl;
	cout << "���������̱�!������������!���������Ѿ� �߻�!��" << endl;
	cout << "����������������������������������������������" << endl;
	cout << "���� : �̰��� �����ϸ� �������� Ŭ����! ������" << endl;
	cout << "���� : ��ȭ������ ������ ������ �νǼ� �ִ�!��" << endl;
	cout << "���� : �Ѿ� ������ ź����� �þ��!������ ��" << endl;
	cout << "���� : ����� 0 �������ϸ� �����й�!����������" << endl;		
	cout << "����������������������������������������������" << endl;
	cout << "����������  ��- PRESS ANYKEY -  ��������������" << endl;
	getch();

}

void _clHandle::Output_Life_Stage()	// ����� �������� �����ִ� �Լ� 
{
	system("mode con cols=101 lines=30");
	gotoxy(46, 12);
	cout << "Stage " << iStage << endl;
	gotoxy(44, 14);
	cout << "LIFE �� : " << iLife_p << endl;
	sleep(3);
	system("cls");
	return;
}

void _clHandle::Output_Claer_Stage()	// Ŭ����ȭ�� ��� 
{
	system("mode con cols=101 lines=30");
	gotoxy(46, 13);
	cout << "Stage" << iStage <<  " Clear!!" << endl;
	sleep(3);
	system("cls");
	return;
}

void _clHandle::Output_Dead_Stage()	// ���ӿ��� ȭ��7 ��� 
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

void _clHandle::Print_Map()	// ���� ����ϴ� �Լ�
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
				cout << "��";
			else if(cMap[y][x] == '2')
				cout << "��";
			else if(cMap[y][x] == '3')
			{
				cout << "��";
				iXpos_ST = x;	// ������ ��ġ ���� 
				iYpos_ST = y;
			}
			else if(cMap[y][x] == '4')
			{
				cout << "��"; 
				iXpos_CT = x;	// ���������� �����ϴ� ���� 
				iYpos_CT = y;
			}
			else if(cMap[y][x] == '5')
				cout << "��"; 
			else if(cMap[y][x] == '6')
				cout << "��"; 
			else if(cMap[y][x] == '7')
				cout << "��"; 
			else if(cMap[y][x] == '8')
				cout << "��"; 
			else if(cMap[y][x] == '9')
				cout << "��"; 
			else if(cMap[y][x] == 'A')
				cout << "��"; 
			else if(cMap[y][x] == 'B')
				cout << "��"; 
			else if(cMap[y][x] == 'C')
			{
				bMOB_ACTIVE[iMob_Count] = true;
				ActiveMOB(iMob_Count);
				MOB[iMob_Count].InputPOS_m(x,y);
				MOB[iMob_Count].InputPOS_om(x,y);
				iMob_Count++;
				cout << "��"; 
			}
		}
		cout << endl;
	}
	SetPos_p(iXpos_ST, iYpos_ST);	// ������� �Ϸ�Ǹ� �÷��̾��� ��ġ�� ���������� �����. 
	SetPos_op(iXpos_ST, iYpos_ST);	// �ܼ���ǥ���� �÷��̾� ��ǥ�� �Է��Ѵ�
	return;
}

void _clHandle::RePrint_Map()	// ���� �����ϴ� �Լ�
{
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 50; x++)
			if(cMap[y][x] != cMap_Cpy[y][x])	// ������ ���� ������ ���� �ִ� �ʰ� �ٸ��� �׺κ��� ������Ѵ�. 
			{
				cMap_Cpy[y][x] = cMap[y][x];	// ����� ���� ���� ������ش�
				gotoxy(x * 2, y);
				if(cMap[y][x] == '0')
					cout << "  ";
				else if(cMap[y][x] == '1') 
					cout << "��";
				else if(cMap[y][x] == '2')
					cout << "��";
				else if(cMap[y][x] == '3')
					cout << "��";
				else if(cMap[y][x] == '4')
					cout << "��"; 
				else if(cMap[y][x] == '5')
					cout << "��"; 
				else if(cMap[y][x] == '6')
					cout << "��"; 
				else if(cMap[y][x] == '7')
					cout << "��"; 
				else if(cMap[y][x] == '8')
					cout << "��"; 
				else if(cMap[y][x] == '9')
					cout << "��"; 
				else if(cMap[y][x] == 'A')
					cout << "��"; 
				else if(cMap[y][x] == 'B')
					cout << "��"; 
				else if(cMap[y][x] == 'C')
					cout << "��"; 
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

int _clHandle::Player_Moving()	// �÷��̾� �� Ű���尪�� �޴� �Լ�
{
	if((GetAsyncKeyState(VK_LEFT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000) && (GetAsyncKeyState(0x58) & 0x8000))	// �������� ���� �ϸ鼭 �߻� 
	{
		Player_Jump();
		Player_Left();
		Player_Fire();
		return PM_LEFT;
	}
	else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000) && (GetAsyncKeyState(0x58) & 0x8000))	// ������ ���� ����  �ϸ鼭 �߻� 
	{
		Player_Jump();
		Player_Right();
		Player_Fire();
		return PM_RIGHT;
	}
	else if((GetAsyncKeyState(VK_LEFT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// �������� ���� 
	{
		Player_Jump();
		Player_Left();
		return PM_LEFT;
	}
	else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// ������ ���� ���� 
	{
		Player_Jump();
		Player_Right();
		return PM_RIGHT;
	}
	else if((GetAsyncKeyState(0x58) & 0x8000) && (GetAsyncKeyState(0x5A) & 0x8000))	// �����ϸ鼭  �߻�
	{
		Player_Jump();
		Player_Fire();
		return iMovingB_p;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000 && (GetAsyncKeyState(VK_RIGHT) & 0x8000))	// ���������� �����̸鼭 �߻�
	{
		Player_Right();
		Player_Fire();
		return PM_RIGHT;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000 && (GetAsyncKeyState(VK_LEFT) & 0x8000))	// �������� �����̸鼭 �߻� 
	{
		Player_Left();
		Player_Fire();
		return PM_LEFT;
	}
	else if(GetAsyncKeyState(VK_LEFT) & 0x8000)	// ���� ����Ű 	���� 
	{
		Player_Left();
		return PM_LEFT;
	}
	else if(GetAsyncKeyState(VK_RIGHT) & 0x8000)	// ������ ����Ű
	{
		Player_Right();
		return PM_RIGHT;		
	}
	else if(GetAsyncKeyState(0x5A) & 0x8000)	// z Ű 	���� 
	{
		Player_Jump();
		return iMovingB_p;
	}
	else if(GetAsyncKeyState(0x58) & 0x8000)	// x Ű 	 �߻� 
	{
		Player_Fire();
		return iMovingB_p;
	}
	else PM_NONE;
}

_clHandle::Check_Fall()	// �÷��̾� ���� ���� ��ȯ 
{
	if(iYpos_p == 9 || bJumpState_p == true)	// �÷��̾ �������̰ų� �ǹٴ��ϋ��� ���� ���� �ʴ´�. 
		return false;
	if(Check_Wall(cMap[iYpos_p + 1][iXpos_p], 1) != false)	// �÷��̾� �� �ٴ��� ��� �����ϴٸ�
	{
		if(cMap[iYpos_p + 1][iXpos_p] == '5')	// �������� 
		{
			cMap[iYpos_p][iXpos_p] = '0';
			iPlayerDeadCheck_p = true;
			return 0; 
		}
		else if(cMap[iYpos_p + 1][iXpos_p] == 'A')	// ��������
			CoinStackB_p++;
		else if(cMap[iYpos_p + 1][iXpos_p] == '7')	// ��ȭ�� ���� 
			Player_Grade(true);
		else if(cMap[iYpos_p + 1][iXpos_p] == '8')	// ź�� ����
			bullet_p++;
		else if(cMap[iYpos_p + 1][iXpos_p] == 'C')	// ���� ���
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

_clHandle::Player_Left()	// �������� �÷��̾� �̵� 
{
	if(iXpos_p < 1 || Check_Wall(cMap[iYpos_p][iXpos_p - 1], 1) == false)return false;	// ���� ùĭ�ϰ�� �̵��Ұ� 
	else if(cMap[iYpos_p][iXpos_p - 1] == '5' || cMap[iYpos_p][iXpos_p - 1] == 'C')	// �������� & ���� ���� 
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[iYpos_p][iXpos_p - 1] == '7')	// ��ȭ�� ���� 
		Player_Grade(true);
	else if(cMap[iYpos_p][iXpos_p - 1] == 'A')	// ��������
		CoinStackB_p++;
	else if(cMap[iYpos_p][iXpos_p - 1] == '8')	// ź�� ����
		bullet_p++; 
	if(cMap[iYpos_p][iXpos_p] == '3')	// ���� ��ĭ�� ��ŸƮ����Ʈ�� �������ʴ´�.
		cMap[iYpos_p][iXpos_p] = '3';
	else cMap[iYpos_p][iXpos_p] = '0';
	SetPos_p(iXpos_p - 1, iYpos_p);	// �������� ��ĭ�̵� 
	cMap[iYpos_p][iXpos_p] = '2';
	SetPos_op(iXpos_p, iYpos_p);	// �̹� �̵������̴� ���Ը� �Ѵ� 
}

_clHandle::Player_Right()	// ���������� �÷��̾� �̵� 
{
	if(iXpos_p > 48 || Check_Wall(cMap[iYpos_p][iXpos_p + 1], 1) == false)return false;	// ������ ��ĭ�ϰ�� �̵��Ұ�
	if(cMap[iYpos_p][iXpos_p + 1] == '5' || cMap[iYpos_p][iXpos_p + 1] == 'C')	// �������� & ���� ���� 
	{
		cMap[iYpos_p][iXpos_p] = '0';
		iPlayerDeadCheck_p = true;
		return 0; 
	}
	else if(cMap[iYpos_p][iXpos_p + 1] == '7')	// ��ȭ�� ���� 
		Player_Grade(true);
	else if(cMap[iYpos_p][iXpos_p + 1] == 'A')	// ��������
		CoinStackB_p++;
	else if(cMap[iYpos_p][iXpos_p + 1] == '8')	// ź�� ����
		bullet_p++;
	if(cMap[iYpos_p][iXpos_p] == '3')	// ���� ��ĭ�� ��ŸƮ����Ʈ�� �������ʴ´�.
		cMap[iYpos_p][iXpos_p] = '3';
	else cMap[iYpos_p][iXpos_p] = '0';
	SetPos_p(iXpos_p + 1, iYpos_p); 
	cMap[iYpos_p][iXpos_p] = '2';
	SetPos_op(iXpos_p, iYpos_p);
}

_clHandle::Player_Jump()	// �����ϴ� �÷��̾� �̵�
{
	if(iYpos_p < 1 || Check_Wall(cMap[iYpos_p - 1][iXpos_p], 1) == false)
	{
		if(cMap[iYpos_p - 1][iXpos_p] == '6' && Upgrade_p == true)	// �Ʒ��� ���Ⱑ �ƴϰ� �ٷ����� ���� ������쿡�� 
		{
			if(cMap[iYpos_p + 1][iXpos_p] != '0')
				cMap[iYpos_p - 1][iXpos_p] = '0';
			else if(iJumpRemain_p > 1)
				cMap[iYpos_p - 1][iXpos_p] = '0';
		}
		iJumpRemain_p = 0;
		return false;	// ��ĭ�� ���� ���̰ų� �������̴� ĭ�̸� �̵��Ұ� + �������ϋ� �����Ұ� 
	}
	if(iJumpRemain_p > 1 || bJumpState_p == true|| cMap[iYpos_p + 1][iXpos_p] == '0' || cMap[iYpos_p + 1][iXpos_p] == '5' || cMap[iYpos_p + 1][iXpos_p] == 'A' || cMap[iYpos_p + 1][iXpos_p] == 'C')return false;
	bJumpState_p = true;	// �������� Ȱ��ȭ 
	iJumpRemain_p = iJumpMax_p;	// �����ο� 
}

_clHandle::Chack_Up()	// �÷��̾��� ��� ���� ��ȯ
{
	if(iYpos_p < 1 || Check_Wall(cMap[iYpos_p - 1][iXpos_p], 1) == false || bJumpState_p == false || iJumpRemain_p < 1)
	{
		if(iYpos_p < 1 && iJumpRemain_p > 0)	// õ�忡 ��Ѵµ� �������������� ĭ���� ���̰� �������� �ʴ´�. 
		{
			iJumpRemain_p--;
			return false;
		}
		if(cMap[iYpos_p - 1][iXpos_p] == '6' && iJumpRemain_p > 0 && Upgrade_p == true)	// �Ʒ��� ���Ⱑ �ƴϰ� �ٷ����� ���� ������쿡�� 
			cMap[iYpos_p - 1][iXpos_p] = '0';
		iJumpRemain_p = 0;
		bJumpState_p = false; 
		return false;	// ���� ���� �κ��̰ų� ���� �ε�ġ�ų� �������� �ƴҋ��� ������� 
	}
	if(iJumpRemain_p > 0)
	{
		if(cMap[iYpos_p - 1][iXpos_p] == '5')	// �������� 
		{
			cMap[iYpos_p][iXpos_p] = '0';
			iPlayerDeadCheck_p = true;
			return 0; 
		}
		else if(cMap[iYpos_p - 1][iXpos_p] == '7')	// ��ȭ�� ���� 
			Player_Grade(true);
		else if(cMap[iYpos_p - 1][iXpos_p] == 'A')	// ��������
			CoinStackB_p++;
		else if(cMap[iYpos_p - 1][iXpos_p] == '8')	// ź�� ����
			bullet_p++;
		if(cMap[iYpos_p][iXpos_p] == '3')	// ���� ��ĭ�� ��ŸƮ����Ʈ�� �������ʴ´�.
			cMap[iYpos_p][iXpos_p] = '3';
		else cMap[iYpos_p][iXpos_p] = '0';
		SetPos_p(iXpos_p, iYpos_p - 1); 
		cMap[iYpos_p][iXpos_p] = '2';
		SetPos_op(iXpos_p, iYpos_p);
		iJumpRemain_p--;
	}
	
	if(Check_Wall(cMap[iYpos_p + 1][iXpos_p], 1) == false && iJumpRemain_p == 0)iJumpRemain_p++;
}

_clHandle::Player_Fire()	// ���� �߻��ϴ� �Լ� 
{
	if(bullet_p < 1)return false;	// �Ѿ��� ������ ���� 
	int iFlag;
	if(iMovingB_p == PM_LEFT)iFlag = -1;else if(iMovingB_p == PM_RIGHT)iFlag = 1;	// �����̸� -1 �������̸� +1
	bullet_p--;	// �Ѿ� �Ҹ�
	if(Check_Wall(cMap[iYpos_p][iXpos_p + iFlag], 2) == false)	// �Ѿ��� �����ɼ� ������ true �ƴϸ� false
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

_clHandle::Bullet_Moving()	// �Ѿ� �̵�
{
	int LBullet_C = 0;	// ���� �Ѿ� ������ ���� 
	int LBullet_X[100] = {};
	int LBullet_Y[100] = {};
	int RBullet_C = 0;	// ������ �Ѿ� ������ ���� 
	int RBullet_X[100] = {};
	int RBullet_Y[100] = {};
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 50; x++)
		{
			if(cMap[y][x] == '9')	// ���� �Ѿ� 
			{
				LBullet_X[LBullet_C] = x; 
				LBullet_Y[LBullet_C] = y;
				LBullet_C++;
			}
			else if(cMap[y][x] == 'B')	// ������ �Ѿ� 
			{
				RBullet_X[RBullet_C] = x; 
				RBullet_Y[RBullet_C] = y;
				RBullet_C++;
			}
		}
	}
	for(int i = 0; i < LBullet_C; i++)	// ���� �Ѿ��� ���� ���ʿ� �ִ� �Ѿ˺��� ����
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
	for(int i = RBullet_C - 1; i > -1; i--) 	// ������ �Ѿ��� ���� �����ʿ� �ִ� �Ѿ˺��� ���� 
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

bool _clHandle::Playing_Game()	// ������ �����ϴ� �Լ� 
{
	if(ReadStage(iStage) == false)	// �� �б� 
		return false;
	Output_Life_Stage();	// ��� �� �������� ǥ�� 
	Print_Map();		// �� ���
	int Temp = 0;
	while(1)
	{
		if(iYpos_p == iYpos_CT && iXpos_p == iXpos_CT)	// ������ ������ 
		{
			Output_Claer_Stage();	// �������� Ŭ���� ȭ������ ��ȯ �� 
			iStage++;	// �������� ��� 
			return true; 	// ������ȯ 
		}
		Search_Move();
		if(iPlayerDeadCheck_p == true)	// ���� �÷��̾ �׾�����
		{
			if(iLife_p == 0)	// ����� ���ϸ� �������� 
			{
				Output_Dead_Stage();
				return false;
			}
			ResetMOB();
			ReadStage(iStage);	// ���� �ٽ� �д´�. 
			Reset_p();	// �÷��̾� ������ �����Ѵ�. 
			bUserInfo_Reprint = true;	// ���� �������̽��� �ʱ�ȭ�Ѵ�. 
			Output_Life_Stage();	// �ε��� ��� 
			Print_Map();	// �� ����� 
		}
		RePrint_Map();	// ���� ��� �����Ѵ�.
		Bullet_Moving();	// �Ѿ� �̵� 
		OutPutPlayer_INFO();	// �÷��̾� ������� 
		
		iMoving = Player_Moving();	// ���ο� �̵����� �Է� 
		if(iMoving != PM_NONE)iMovingB_p = iMoving;	// �Ѿ� ���� ���������� �̵����� ���� 
		
		Chack_Up();	// ��� Ȯ�� 
		Check_Fall();	// �ϰ� Ȯ�� 
		Sleep(150);
	}
	
}
