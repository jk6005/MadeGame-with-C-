#pragma once

#include "core.h"

class _clHandle	: public _clPlayer
{
	public:
		void Output_Main();	// 메인화면을 출력하는 함수
		void Output_Explain();	// 게임방법을 알려주는 함수
		
		bool Playing_Game();	// 게임을 시작하는 함수 
		
		void Output_Life_Stage();	// 목숨과 라이프를 보여주는 함수 
		void Output_Claer_Stage();	// 게임클리어 화면을 보여주는 함수 
		void Output_Dead_Stage();	// 게임오버 화면 출력
			// == 맵 관련 
			void Print_Map();	// 맵을 출력하는 함수
			void RePrint_Map();	// 맵을 수정하는 함수
			
			// == 플레이어 이동제어 
			int Player_Moving();	// 플레이어 의 키보드값을 받는 함수 
			
			// == 점프및 낙하 
			int Check_Fall();	// 플레이어 낙하 판정 반환 
			int Chack_Up();	// 플레이어의 상승 판정 반환 
			
			// == 액션키 
			int Player_Left();	// 왼쪽으로 플레이어 이동 
			int Player_Right();	// 오른쪽으로 플레이어 이동 
			int Player_Jump();	// 점프하는 플레이어 이동 
			int Player_Fire();	// 총을 발사하는 함수
			
			// == 총알 이동 및 충돌
			int Bullet_Moving();	// 총알 이동 
		
		// 생성및 호출 
		_clHandle();
		~_clHandle();
};
