#pragma once

#include "core.h"

class _clHandle	: public _clPlayer
{
	public:
		void Output_Main();	// ����ȭ���� ����ϴ� �Լ�
		void Output_Explain();	// ���ӹ���� �˷��ִ� �Լ�
		
		bool Playing_Game();	// ������ �����ϴ� �Լ� 
		
		void Output_Life_Stage();	// ����� �������� �����ִ� �Լ� 
		void Output_Claer_Stage();	// ����Ŭ���� ȭ���� �����ִ� �Լ� 
		void Output_Dead_Stage();	// ���ӿ��� ȭ�� ���
			// == �� ���� 
			void Print_Map();	// ���� ����ϴ� �Լ�
			void RePrint_Map();	// ���� �����ϴ� �Լ�
			
			// == �÷��̾� �̵����� 
			int Player_Moving();	// �÷��̾� �� Ű���尪�� �޴� �Լ� 
			
			// == ������ ���� 
			int Check_Fall();	// �÷��̾� ���� ���� ��ȯ 
			int Chack_Up();	// �÷��̾��� ��� ���� ��ȯ 
			
			// == �׼�Ű 
			int Player_Left();	// �������� �÷��̾� �̵� 
			int Player_Right();	// ���������� �÷��̾� �̵� 
			int Player_Jump();	// �����ϴ� �÷��̾� �̵� 
			int Player_Fire();	// ���� �߻��ϴ� �Լ�
			
			// == �Ѿ� �̵� �� �浹
			int Bullet_Moving();	// �Ѿ� �̵� 
		
		// ������ ȣ�� 
		_clHandle();
		~_clHandle();
};
