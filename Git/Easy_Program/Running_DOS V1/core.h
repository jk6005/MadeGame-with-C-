#pragma once
/*
	�޸��� ���� V2 
	�����ؾ� �ϴ°�
	1. �� �б�	10 x 50	 					(�Ϸ�) 
	2. �� 5 x 10 ���� ���					(���)	: ���� �Ϸ��� ����� ��ǥ���� ���ο� �׸��� ���� �ϴ� �����̱� ������ �̹���� ������ �ִ�. ���� ���ǿ��󿡼� Ȯ�� �ٶ� 
	3. ������ �� ������ ����� : ������ �ϼ� // ������ �����!!! 
	4. ĳ���� �����̱�	(��, ��, ����)// �ϼ�����! 
	5. ��� �� ���� �����ϱ�	// ���α����Ϸ� 
	6. ��ȭ ������ �����		// �ϼ� 
	7. �Ѿ� �� �߻� �����		// �����Ϸ� 
	8. ���� �����			// 		���� �����̶� �������� �׸��� �� �浹����(���հ��;;) ��������! 
	9. �Ѿ� �浹 ���� ����� 	// ���ƾƾƾȼ�!! 
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL

using namespace std;

void gotoxy(int x,int y);	// ���� ��ǥ�� �о Ŀ���� �����ϴ� �Լ� 

void Clean_Cussor();	// Ŀ���� ����� �Լ� 

enum PlAYER_MOVE
{
	PM_NONE,
	PM_LEFT,
	PM_RIGHT,
	PM_JUMP,
	PM_FIRE
};

class _clMonster
{
	public:
		bool bActiveMOB;
		
		int iXpos_m;
		int iYpos_m;
		int iXpos_om;
		int iYpos_om;
		
		int iSearchRange;
		
		int InputPOS_m(const int Xpos, const int Ypos);
		int InputPOS_om(int Xpos, const int Ypos);
		
	_clMonster();
	~_clMonster();
};

class _clMap
{
	public:
		char cMap[11][51];	// ���� �����ϴ� �迭 
		char cMap_Cpy[11][51];	// ���� ������ �迵�� ī���ϴ� �迭 
		int iXpos_ST;	// ���������� �����ϴ� ���� 
		int iYpos_ST; 
		int iXpos_CT;	// ���������� �����ϴ� ���� 
		int iYpos_CT;
		int iStage;
		
		_clMonster MOB[10];	// ���� �迭 ���� 
		bool bMOB_ACTIVE[10];
		int iUserInfoOutput_Stack[5];	// int OutPutPlayer_INFO();	// �÷��̾��� ������ ����ϴ� �Լ� �� ���� �����ϴ� ���� 
		bool bUserInfo_Reprint;	// int OutPutPlayer_INFO() �Լ��� ������ ������ ������ϰ� ���ϴ� ���� 
		
		// -- �Լ� 
		_clMap();
		~_clMap();
		
		int Check_Wall(char Move, int iType);	// �÷��̾��� �浹���� �� ��ȯ 
		
		bool ReadStage(const int iStage_Num);	// ���� �д� �Լ�
		
		void ActiveMOB(int Mob);	// ���� Ȱ��ȭ�ϴ� �Լ� 
		void UnActiveMOB(int Mob);	// ���� ��Ȱ��ȭ �ϴ� �Լ� 
		void ResetMOB();	// ���� �ʱ�ȭ 
		
};

class _clPlayer	: public _clMap 
{
	public:
		//	�̵� �� ��ǥ 
		int iXpos_p;	// �÷��̾��� ��ġ�� ������ ���� 
		int iYpos_p;
		int iXpos_op;	// �ܼ� �󿡼��� �÷��̾� ��ǥ
		int iYpos_op; 
		int iMoving;	// �÷��̾��� �̵����� �����ϴ� ���� 
		
		//	��� 
		int iLife_p; // �÷��̾� ���
		bool iPlayerDeadCheck_p;	// �÷��̾ ������ ��Ѵ��� üũ�ϴ� �Լ� 
		
		//	���� 
		bool bJumpState_p;	// �÷��̾ ���������� Ȯ���ϴ� ����
		int	iJumpRemain_p;	// �÷��̾ �ö󰡾��� ���� ���� 
		int iJumpMax_p;	// �÷��̾��� �ִ� ����ġ�� ���ϴ� ���� 
		
		//	��ȭ 
		bool Upgrade_p;	// �÷��̾ ��ȭ�̴��� �����ϴ� ����
		
		//	���� 
		int CoinStack_p;	// �÷��̾ ���� ���� ���� 
		int CoinStackB_p;	// �÷��̾ �ѽ����������� ���� ���ξ� 
		
		//	 �Ѿ� 
		int bullet_p;	// �÷��̾��� �Ѿ� ������ �����ϴ� ���� 
		int iMovingB_p;	// true = ����, false = ������	�÷��̾ �Ѿ��� �߻��Ҷ� ������ �����ϴ� ����
		
		// == �Լ�
		_clPlayer();
		~_clPlayer();		
		void SetPos_p(const int Xpos, const int Ypos);	// �÷��̾��� ��ġ�� �Է��ϴ� �Լ� 
		void SetPos_op(int Xpos, const int Ypos);	// �ֻܼ翨���� �÷��̾� ��ǥ�� �����ϴ� �Լ� 
		void Reset_p();	// �÷��̾��� ���¸� ó������ ����� �Լ�
		bool Player_Grade(bool bGrade);	// �÷��̾ ���׷��̵��ϰų� ����ϴ� �Լ� 
		
		// == �ʰ��� �Լ� 
		int OutPutPlayer_INFO();	// �÷��̾��� ������ ����ϴ� �Լ�
		
		//	== ����
		int MOB_LEFT(const int Count);
		int MOB_RIGHT(const int Count); 
		int Search_Move();	// ���� �����̴� �Լ�   
};

