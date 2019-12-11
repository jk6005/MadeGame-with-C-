#pragma once
/*
	달리기 게임 V2 
	구현해야 하는것
	1. 맵 읽기	10 x 50	 					(완료) 
	2. 맵 5 x 10 으로 출력					(취소)	: 현재 하려는 방식은 좌표값에 새로운 그림을 삽입 하는 형태이기 떄문에 이방식은 문제가 있다. 추후 강의영상에서 확인 바람 
	3. 시작점 및 도착점 만들기 : 시작점 완성 // 도착점 만들기!!! 
	4. 캐릭터 움직이기	(좌, 우, 점프)// 완서어어엉! 
	5. 블록 및 코인 구현하기	// 코인구현완료 
	6. 강화 아이템 만들기		// 완성 
	7. 총알 및 발사 만들기		// 구현완료 
	8. 몬스터 만들기			// 		낙하 판정이랑 가시판정 그리고 벽 충돌판정(벽뚫고옴;;) 만들어야해! 
	9. 총알 충돌 판정 만들기 	// 오아아아안성!! 
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <unistd.h>

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL

using namespace std;

void gotoxy(int x,int y);	// 맵의 좌표를 읽어서 커서를 대입하는 함수 

void Clean_Cussor();	// 커서를 지우는 함수 

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
		char cMap[11][51];	// 맵을 저장하는 배열 
		char cMap_Cpy[11][51];	// 맵을 저장한 배영을 카피하는 배열 
		int iXpos_ST;	// 시작지점을 저장하는 변수 
		int iYpos_ST; 
		int iXpos_CT;	// 도착지점을 저장하는 변수 
		int iYpos_CT;
		int iStage;
		
		_clMonster MOB[10];	// 몬스터 배열 선언 
		bool bMOB_ACTIVE[10];
		int iUserInfoOutput_Stack[5];	// int OutPutPlayer_INFO();	// 플레이어의 정보를 출력하는 함수 의 값을 저장하는 변수 
		bool bUserInfo_Reprint;	// int OutPutPlayer_INFO() 함수가 죽으면 완전히 재출력하게 정하는 변수 
		
		// -- 함수 
		_clMap();
		~_clMap();
		
		int Check_Wall(char Move, int iType);	// 플레이어의 충돌판정 값 반환 
		
		bool ReadStage(const int iStage_Num);	// 맵을 읽는 함수
		
		void ActiveMOB(int Mob);	// 몹을 활성화하는 함수 
		void UnActiveMOB(int Mob);	// 몹을 비활성화 하는 함수 
		void ResetMOB();	// 몬스터 초기화 
		
};

class _clPlayer	: public _clMap 
{
	public:
		//	이동 및 좌표 
		int iXpos_p;	// 플레이어의 위치를 저장할 변수 
		int iYpos_p;
		int iXpos_op;	// 콘솔 상에서의 플레이어 좌표
		int iYpos_op; 
		int iMoving;	// 플레이어의 이동값을 저장하는 변소 
		
		//	목숨 
		int iLife_p; // 플레이어 목숨
		bool iPlayerDeadCheck_p;	// 플레이어가 죽은지 살앗는지 체크하는 함수 
		
		//	점프 
		bool bJumpState_p;	// 플레이어가 점프중인지 확인하는 변수
		int	iJumpRemain_p;	// 플레이어가 올라가야할 점프 개수 
		int iJumpMax_p;	// 플레이어의 최대 점프치를 정하는 변수 
		
		//	강화 
		bool Upgrade_p;	// 플레이어가 강화됫는지 저장하는 변수
		
		//	코인 
		int CoinStack_p;	// 플레이어가 가진 코인 점수 
		int CoinStackB_p;	// 플레이어가 한스테이지에서 먹은 코인양 
		
		//	 총알 
		int bullet_p;	// 플레이어의 총알 개수를 저장하는 변수 
		int iMovingB_p;	// true = 왼쪽, false = 오른쪽	플레이어가 총알을 발사할때 방향을 저장하는 변수
		
		// == 함수
		_clPlayer();
		~_clPlayer();		
		void SetPos_p(const int Xpos, const int Ypos);	// 플레이어의 위치를 입력하는 함수 
		void SetPos_op(int Xpos, const int Ypos);	// 콘솔사엥서의 플레이어 좌표를 저장하는 함수 
		void Reset_p();	// 플레이어의 상태를 처음으로 만드는 함수
		bool Player_Grade(bool bGrade);	// 플레이어를 업그레이드하거나 취소하는 함수 
		
		// == 맵관련 함수 
		int OutPutPlayer_INFO();	// 플레이어의 정보를 출력하는 함수
		
		//	== 몬스터
		int MOB_LEFT(const int Count);
		int MOB_RIGHT(const int Count); 
		int Search_Move();	// 몹이 움직이는 함수   
};

