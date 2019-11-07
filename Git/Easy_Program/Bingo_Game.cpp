// This coding is based on the small screen.
// 이 코딩은 작은 화면을 기준으로 작성되었습니다.
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>

using namespace std;

// 빙고 최댓값
#define Bingo_Max	5	// 5 ~ 10 
#define Bingo_Arr	 (Bingo_Max * Bingo_Max)
// 플레이어가 입력할수 있는 최대 숫자 
#define Bingo_Number_Max	((Bingo_Max * Bingo_Max) + (Bingo_Max * 2))
// 대각선 위치를 정의하는 수
#define Bingo_Left_Dir	(Bingo_Max + 1)
#define Bingo_Right_Dir	(Bingo_Max - 1) 

// 가위바위보
enum RPS
{SCISSORS = 1, ROCK, PAPER }; 

// 빙고판을 표시하는 함수
void View_Player(int iPlayer_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int& iPlayer_BINGO);
void View_Ai(int iAi_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int& iAi_BINGO);
// Ai가 선택하는 함수
int Ai_Choice(int iAi_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int iDifficult, int iPlayer_Bingo[Bingo_Arr]);
// 플레이어가 선택하는 함수
int Player_Choice(int iPlayer_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int iAi_Bingo[Bingo_Arr], int iRecentl_Choice);

enum Ai_Number
{
	Nothing = 0, Width = 1, Height = 2, Left_Dir = 3, Right_Dir = 4
};

// 플레이어가 수동으로 배열값을 입력하는 함수 
void Supple_Player(int iPlayer_Bingo[Bingo_Arr])
{
	// 배열에 중복되는 값이 있는지 체크하는 변수
	bool bNumber_Check[Bingo_Number_Max] = {};
	// 배열 에 넣어줄 순번을 입력할 변수
	int iTemp = 0;
	
	while(true)
	{
		int iTemp2;
		 system("cls");
		 system("mode con lines=26 cols=51");
		 // ★ 그림으로 입력하지 않은 자리를 출력
		 cout << "┌───────────────────────┐" << endl;
		 cout << "│                 　　　　　　　　             │" << endl;
		 for(int i = 0; i < Bingo_Max; i++)
		 {
		 	cout << "│\t";
		 	for(int j = 0; j < Bingo_Max; j++)
		 	{
		 		if(iPlayer_Bingo[(Bingo_Max * i) + j] == 0)
		 		{
		 			cout << "★\t";
		 			continue;
				 }
				 cout << iPlayer_Bingo[(Bingo_Max * i) + j] << "\t";
			 }
			 cout << "│" << endl << "│\t\t\t\t\t\t│" <<endl;
		  }
		  cout << "│                 　　　　　　　　             │" << endl;
		  cout << "├───────────────────────┤" << endl;
		  
		  // 모든 값을 입력하면 종료
		if(iTemp == Bingo_Arr)
		{
			cout << "│※       　　　　　　　　　　　　　　　     ※│" << endl;
			cout << "│   　※ 모든 숫자가 입력 완료되었습니다!      │" << endl;
		    cout << "│※       　　　　　　　　　　　　　　　     ※│" << endl;
		    cout << "├───────────────────────┤" << endl;
			cout << "│         빙고판을 완성 하시겠습니까?          │" << endl;
		    cout << "│         1. 예             2. 아니오          │" << endl;
		    cout << "└───────────────────────┘" << endl;
			POS1:
			iTemp2 = getch();
			iTemp2 -= '0';
			if(iTemp2 > 2 || iTemp2 < 1)
			{
				goto POS1;
			}
			else if(iTemp2 == 1)
			{
				cout << " 　┌────────────────────┐" << endl; 
				cout << " 　│※       　　　　　　　　             ※│" << endl;
				cout << " 　│        ※빙고판을 완성하셨습니다!      │" << endl;
		 		cout << "　 │※       　　　　　　　　             ※│" << endl;
		 		cout << "　 └────────────────────┘";
				break;
			}
			else if(iTemp2 == 2)
			{
				cout << " 　┌────────────────────┐" << endl; 
				cout << " 　│※       　　　　　　　　             ※│" << endl;
				cout << " 　│        ※빙고판을 초기화합니다!        │" << endl;
		 		cout << "　 │※       　　　　　　　　             ※│" << endl;
		 		cout << "　 └────────────────────┘";
		 		getch();
				iTemp = 0;
				for(int i = 0; i < Bingo_Arr; i++)
					iPlayer_Bingo[i] = 0;
				for(int i = 0; i < Bingo_Number_Max; i++)
					bNumber_Check[i] = false;
				continue;
			}
		 }
		 
		  // 숫자를 입력받은후 맞는 숫자를 입력했는지 중복되지 않는지를 검사해 대입하고 중복체크 변수의 값을 변경한다
		  while(true)
		  {
		  		int iNumber;
				  cout << "│      1 ~ " << Bingo_Number_Max << " 사이의 숫자를 입력하세요         │" << endl;
				  cout << "│      ※0 을 입력시 입력을 취소합니다         │" << endl;
				  cout << "└───────────────────────┘" << endl;
				  cout << endl;
				  cout << "　　　　　　　　입력 : ";
				   cin >> iNumber;
				   cin.ignore(1000, '\n');
				   cout << endl;
				   if(cin.fail())
				   {
				   		cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※올바르지 않은 값입니다!       │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
				   		cin.clear();
				   		cin.ignore(1000, '\n');
				   		getch();
				   		break;
					}
					if(iNumber < 0 || iNumber > Bingo_Number_Max)
				   {
				   		cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※올바르지 않은 값입니다!       │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
				   		getch();
				   		break;
					} 
					//0 이입력되면 뒤로가기 
					if(iNumber == 0 && iTemp != 0) 
					{
						iTemp--;
						bNumber_Check[iPlayer_Bingo[iTemp] - 1] = false;
						iPlayer_Bingo[iTemp] = 0;
						cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※입력을 취소했습니다!          │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
					  	getch();
						break;
					}
					else if(iNumber == 0 && iTemp == 0 && iPlayer_Bingo[0] != 0)
					{
						bNumber_Check[iPlayer_Bingo[iTemp] - 1] = false;
						iPlayer_Bingo[iTemp] = 0;
						cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※입력을 취소했습니다!          │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
				  		getch();
						break;
					}
					else if(iNumber == 0 && iTemp == 0 && iPlayer_Bingo[0] == 0)
					{
						cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※첫번째 칸입니다!              │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
						getch();
						break;
					}
					// 중복체크 
					if(bNumber_Check[iNumber - 1] == true)
					{
						cout << " 　┌────────────────────┐" << endl; 
						cout << " 　│※       　　　　　　　　             ※│" << endl;
						cout << " 　│        ※이미 입력하신 값입니다!       │" << endl;
		 				cout << "　 │※       　　　　　　　　             ※│" << endl;
		 				cout << "　 └────────────────────┘";
						getch();
						break;
					}
					// 이상이 없으면 배열에 해당값을 입력한다 
					bNumber_Check[iNumber - 1] = true;
					iPlayer_Bingo[iTemp] = iNumber;
					iTemp++;
					break;
		   } 
	} 
}

// 플레이어의 빙고판을 자동으로 입력해주는 함수 
void Supple_Player_Random(int iPlayer_Bingo[Bingo_Arr])
{
	int iMake;
	// 배열에 중복되는 값이 있는지 체크하는 변수
	bool bNumber_Check[Bingo_Number_Max]  = {};
	while(true)
	{
		// 1 ~ Bingo_Arr 까지 랜덤값을 입력한다.
		for(int i = 0; i < Bingo_Arr; i++)
		{
			iPlayer_Bingo[i] = rand() % Bingo_Number_Max + 1;
			// 중복값이 없을떄가지 돌린다.
			while(bNumber_Check[iPlayer_Bingo[i] - 1] == true)
				iPlayer_Bingo[i] = rand() % Bingo_Number_Max + 1;
				bNumber_Check[iPlayer_Bingo[i] - 1]++;
		 } 
		 // 완성된 빙고판 출력 
		 POS2: 
		 system("mode con lines=28 cols=51");
		 system("cls");
		 cout << "┌───────────────────────┐" << endl;
		 cout << "│                 　　　　　　　　             │" << endl;
		 for(int i = 0; i < Bingo_Max; i++)
		 {
		 	cout << "│\t";
		 	for(int j = 0; j < Bingo_Max; j++)
		 	{
		 		cout << iPlayer_Bingo[(Bingo_Max * i) + j] << "\t";
			 }
			 cout << "│" << endl << "│\t\t\t\t\t\t│" <<endl;
		 }
		 cout << "│                 　　　　　　　　             │" << endl;
		 cout << "├───────────────────────┤" << endl;
		 
		 // 빙고판을 사용할건지 물어본다 
	 	 cout << "│         빙고판을 완성 하시겠습니까?          │" << endl;
		 cout << "│         1. 예             2. 다시받기        │" << endl;
		 cout << "└───────────────────────┘" << endl;
		 CC:
		 iMake = getch();
		 iMake -= '0';
		 if(iMake > 2 || iMake < 1)
			{
				goto CC;
			}
			if(iMake == 1)
			{
				cout << " 　┌────────────────────┐" << endl;
				cout << " 　│      빙고판을 완성 하시겠습니까?       │" << endl;
				cout << " 　│      1.예               2.아니오       │" << endl;
				cout << " 　└────────────────────┘";
				iMake = getch();
				if(iMake == '1')
				{
					cout << "　　　 ┌────────────────────┐" << endl;
					cout << "　 │※      　　　　　　　　　　　　　　  ※│" << endl;
					cout << "　 │     　　빙고가 완성되었습니다!         │" << endl;
					cout << "　 │※      　　　　　　　　　　　　　　  ※│" << endl;
					cout << "　 └────────────────────┘";
					getch(); 
					break;
				}
				else if(iMake == '2')
					goto POS2;
				else 
					goto CC;
			}
			else if(iMake == 2)
			{
					cout << "　 ┌────────────────────┐" << endl;
					cout << "　 │      빙고판을 초기화 하시겠습니까?     │" << endl;
					cout << "　 │      1.예               2.아니오       │" << endl;
					cout << "　 └────────────────────┘";
					iMake = getch();
					if(iMake == '1')
					{
						for(int i = 0; i < Bingo_Arr; i++)
							iPlayer_Bingo[i] = 0;
						for(int i = 0; i < Bingo_Number_Max; i++)
							bNumber_Check[i] = false;
						cout << "　　　 ┌────────────────────┐" << endl;
						cout << "　 │※      　　　　　　　　　　　　　　  ※│" << endl;
						cout << "　 │  　　빙고판을 초기화 하였습니다!       │" << endl;
						cout << "　 │※      　　　　　　　　　　　　　　  ※│" << endl;
						cout << "　 └────────────────────┘";
						getch();
						continue; 
					}
				else if(iMake == '2')
						goto POS2;
					else 
						goto CC;
			}
		 
	}
}

// AI 의 빙고판을 만들어주는 함수
void Supple_Ai(int iAi_Bingo[Bingo_Arr])
{
	// 배열에 중복되는 값이 있는지 체크하는 변수
	bool bNumber_Check[Bingo_Number_Max] = {};
	// 1 ~ Bingo_Arr 까지 랜덤값을 입력한다.
	for(int i = 0; i < Bingo_Arr; i++)
	{
		iAi_Bingo[i] = rand() % Bingo_Number_Max + 1;
		// 중복값이 없을떄가지 돌린다.
		while(bNumber_Check[iAi_Bingo[i] - 1] == true) 
			iAi_Bingo[i] = rand() % Bingo_Number_Max + 1;
		bNumber_Check[iAi_Bingo[i] - 1]++;
	 } 
 } 
 
 int main()
 {
 	system("mode con lines=20 cols=63");
 	cout << "┌─────────────────────────────┐" << endl; 
	cout << "│■■■■■■■■■■■■■■■■■■■■■■■■■■■■■│" << endl;
	cout << "│■■□■■■□■■■□■■■■■■■■□□□□□□□■■■│" << endl;
	cout << "│■■□■■■□■■■□■■■■■■■■■■■■■■□■■■│" << endl;
	cout << "│■■□□□□□■■■□■■■■■■■■■■■■■■□■■■│" << endl;
	cout << "│■■□■■■□■■■□■■■■■■■■■■■■■■□■■■│" << endl;
	cout << "│■■□□□□□■■■□■■■■■■■■■■■□■■□■■■│" << endl;
	cout << "│■■■■■■■■■■□■■■■■■■■■■■□■■□■■■│" << endl;
	cout << "│■■■■■■■■■■□■■■■■■■■■■■□■■■■■■│" << endl;
	cout << "│■■■■■■□□■■■■■■■■■■■■■■□■■■■■■│" << endl;
	cout << "│■■■■■□■■□■■■■■■■■■□□□□□□□□□■■│" << endl;
	cout << "│■■■■■□■■□■■■■■■■■■■■■■■■■■■■■│" << endl;
	cout << "│■■■■■■□□■■■■■■■■■■■■■■■■■■■■■│" << endl;
	cout << "│■■■■■■■■■■■■■■■■■■■■■■■■■■■■■│" << endl; 
	cout << "└─────────────────────────────┘" << endl;
	cout << endl << endl;
	cout << "                       Press AnyKey ";
	getch();
 	// srand 함수 현재시간으로 초기화
	 srand((unsigned int)time(0));
	 // 플레이어의 배열과 Ai의 배열 생성 및 초기화
	 int iPlayer_Bingo[Bingo_Arr]  = {};
	 int iAi_Bingo[Bingo_Arr] = {};
	 
	 // 빙고숫자의 중복을 체크하는 변수 
	 bool bNumber_Check[Bingo_Number_Max]  = {};
	 
	 // 플레이어의 배열 초기화 및 셔플
	 // 수동 자동 선택
	 bool bAuto = 0;
	 
	system("cls");
	cout << "┌─────────────────────────────┐" << endl; 
	cout << "│                 　　　　　　　　                         │" << endl;
	cout << "│                 　　< 게임 설명 >                        │" << endl;
	cout << "│                 　　　　　　　　                         │" << endl;
	cout << "│　　　　Ⅰ　 플레이어의 빙고판을 생성한다!　　　　　　　　│" << endl;
	cout << "│　　　　Ⅱ　　 Ai 의 난이도를 선택한다! 　　　　　　　　　│" << endl;
	cout << "│　　　　Ⅲ 　 가위바위보로 순서를 정한다!  　　　　　　 　│" << endl;
	cout << "│　　　　Ⅳ 　     　빙고 시작하기! 　　　　　 　　　　　　│" << endl;
	cout << "│                 　　　　　　　　                         │" << endl;
	cout << "│　　　　　　　　　 　< 게임 방법 >　　　　　　　　　　　　│" << endl;
	cout << "│                 　　　　　　　　                         │" << endl;
	cout << "│　　빙고판의 숫자 들을 가로, 세로, 사선 으로 연결시켜서　 │" << endl;
	cout << "│　　　　Ai 보다 먼저 빙고를 달성하면 승리합니다!　　　　　│" << endl;
	cout << "│                 　　　　　　　　                         │" << endl;
	cout << "└─────────────────────────────┘" << endl;
	
	cout << endl << endl;
	cout << "                       Press AnyKey ";
	getch();
	 
	 while(true) 
	 {
	 	int iAuto;
	 	system("cls");
		cout << "　　　　　　　　　　　　　Choice Mode" << endl;
		cout << endl;
		cout << "┌──────────────┬──────────────┐" << endl;
		cout << "│      < 수동모드 >　 　　 　│　　　  < 자동모드 >        │" << endl; 
		cout << "│                 　　　　　 │　　　                      │" << endl;
		cout << "│ 플레이어가 빙고판을 수동 　│　플레이어의 빙고판을 자동  │" << endl;
		cout << "│     으로 설정합니다.     　│　　　으로 설정합니다.      │" << endl;
		cout << "└──────────────┴──────────────┘" << endl;
		cout << endl;
		cout << "　　　　┌──────┐　　　　　　　┌──────┐" << endl;
		cout << "　　　　│      1   　│　　　　　　　│　    2　　 │" << endl;
		cout << "　　　　└──────┘　　　　　　　└──────┘" << endl;
		cout << endl << endl;
	 	//cout << "입력 : ";
	 	//cin >> iAuto;
	 	iAuto = getch();
	 	iAuto -= '0';
	 	if(cin.fail() || iAuto < 1 || iAuto > 2)
	 		continue;
		 else if(iAuto == 1)
		 {
		 	cout << "　　　　　┌────────────────────┐" << endl; 
			cout << "　　　　　│     수동모드 를 선택하시겠습니까?      │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│      1.예               2.아니오       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
			SS:
			iAuto = getch();

			if(iAuto == '1')
				break;
			else if(iAuto == '2')
				continue;
			else 
				goto SS;
		 }
		 // 자동입력 이면 bAuto 변수를 참으로 바꾸어준다.
		 else if(iAuto == 2) 
		 {
		 	cout << "　　　　　┌────────────────────┐" << endl; 
			cout << "　　　　　│     자동모드 를 선택하시겠습니까?      │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│      1.예               2.아니오       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
			SD:
			iAuto = getch();

			if(iAuto == '1')
			{
				bAuto = true;
				break;
			}
			else if(iAuto == '2')
				continue;
			else 
				goto SD;
		 }
	 }
	 // 수동입력 선택시
	 if(bAuto == false) 
	 	Supple_Player(iPlayer_Bingo);
	// 자동입력 선택시
	else if(bAuto == true)
		Supple_Player_Random(iPlayer_Bingo);
	// Ai 의 빙고판 초기화
	Supple_Ai(iAi_Bingo);
	
// Ai 의 난이도 선택
 int iAi_Difficult = 0;
 
 while(true) 
 {
 	system("mode con lines=29 cols=63");
 	int iDifficult;
 	system("cls");
 	cout << "　　　　　　　　　　　　　Difficult Mode" << endl;
	cout << endl;
	cout << "┌──────────────┬──────────────┐" << endl;
	cout << "│      < EASY모드 >　 　　 　│　　　  < HARD모드 >        │" << endl; 
	cout << "│                 　　　　　 │　　　                      │" << endl;
	cout << "│   Ai 는 랜덤으로 숫자를  　│   Ai 는 자신의 빙고판을    │" << endl;
	cout << "│    입력할 것입니다!      　│　 맞추기 위해 필요한       │" << endl;
	cout << "│                 　　　　　 │　 숫자를 입력할 것입니다!  │" << endl;
	cout << "│                 　　　　　 │　　　                      │" << endl;
	cout << "└────┬────┬────┴────┬────┬────┘" << endl;
	cout << "　　　　　│　  1　 │　　　　　　　　　│　  2　 │" << endl;
	cout << "　　　　　└────┘　　　　　　　　　└────┘" << endl << endl;
	cout << "　　　　　　　 ┌──────────────┐" << endl;
	cout << "　　　　　　　 │ 　    < HELL 모드 >　 　　 │" << endl; 
	cout << "　　　　　　　 │                 　　　　　 │" << endl;
	cout << "　　　　　　　 │   Ai 는 자신에게 유리한  　│" << endl;
	cout << "　　　　　　　 │   숫자만을 입력할 것 입  　│" << endl;
	cout << "　　　　　　　 │          니다!  　　　　　 │" << endl;
	cout << "　　　　　　　 │                 　　　　　 │" << endl;
	cout << "　　　　　　　 └────┬────┬────┘" << endl;
	cout << "　　　　　　　　　　　　 │　  3　 │" << endl;
	cout << "　　　　　　　　　　　　 └────┘" << endl;
	DD:
	iDifficult = getch();
	iDifficult -= '0';
 	if(iDifficult < 1 || iDifficult > 3)
 	{
 		continue;
	 }
	 else if(iDifficult == 1)
	 {
	 		cout << "　　　　　┌────────────────────┐" << endl; 
			cout << "　　　　　│     EASY모드 를 선택하시겠습니까?      │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│      1.예               2.아니오       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
			iDifficult = getch();
				iDifficult -= '0';
			if(iDifficult == 1)
				break;
			else if(iDifficult == 2)
				continue;
			else
				goto DD;
	 }
	 else if(iDifficult == 2)
	 {
	 		cout << "　　　　　┌────────────────────┐" << endl; 
			cout << "　　　　　│     HARD모드 를 선택하시겠습니까?      │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│      1.예               2.아니오       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
		 	iDifficult = getch();
		 		iDifficult -= '0';
			if(iDifficult == 1)
			{
				iAi_Difficult = 1; 
				break;
			}
			else if(iDifficult == 2)
				continue;
			else
				goto DD;
	 }
	 else
	 {
	 		cout << "　　　　　┌────────────────────┐" << endl; 
			cout << "　　　　　│     HELL모드 를 선택하시겠습니까?      │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│      1.예               2.아니오       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
		 	iDifficult = getch();
		 		iDifficult -= '0';
			if(iDifficult == 1)
			{
				iAi_Difficult = 2; 
				break;
			}
			else if(iDifficult == 2)
				continue;
			else
				goto DD;
	 }
}
	 
	 // 가위바위보로 순서를 정한다.
	 bool bOrder = false;
	 
	 int iRPS;
	 while(true) 
	 {
	 	system("mode con lines=30 cols=63");
	 	system("cls");
	 	cout << "┌─────────────────────────────┐" << endl; 
		cout << "│                 　　　　　　　　                         │" << endl;
		cout << "│                　　< 가위 바위 보 >                      │" << endl;
		cout << "│                 　　　　　　　　                         │" << endl;
		cout << "│      순서를 정하기 위해서 가위바위보 를 시작합니다!      │" << endl;
		cout << "│            아래에서 한가지를 선택하세요!           　    │" << endl;
		cout << "│                 　　　　　　　　                         │" << endl;
		cout << "│      1.가위           　2.바위　　　　　　 3.보          │" << endl;
		cout << "└─────────────────────────────┘" << endl;
	 	iRPS = getch();
	 	iRPS -= '0';
	 	int iAi_RPS = rand() % 3 + 1;
	 	if(cin.fail() || iRPS < 1 || iRPS > 3)
	 	{
	 		cout << "　　　　　┌────────────────────┐" << endl; 
	 		cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│  　　  올바른 입력이 아닙니다!　       │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
		 	getch();
	 		continue;
		 }
		 
		 // 승부 판별
		 switch(iRPS) 
		 {
		 	case SCISSORS:
		 		cout << "┌────────────┐" << endl; 
				cout << "│<플레이어> 　　　　　 　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "│　　　　　　　가위 !　　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "└────────────┘" << endl;
		 		break;
		 	case ROCK:
		 		cout << "┌────────────┐" << endl; 
				cout << "│<플레이어> 　　　　　 　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "│　　　　　　　바위 !　　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "└────────────┘" << endl;
		 		break;
			case PAPER:
				cout << "┌────────────┐" << endl; 
				cout << "│<플레이어> 　 　　　　　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "│　　　　　　　　보 !　　│" << endl;
				cout << "│　　　　　　　　　　　　│" << endl;
				cout << "└────────────┘" << endl;
				break;
		 }
		 switch(iAi_RPS) 
		 {
		 	case SCISSORS:
		 		cout << "　　　　　　　　　　　　　　　　　┌────────────┐" << endl; 
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　<AI>　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　가위 !　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　└────────────┘" << endl;
		 		break;
		 	case ROCK:
		 		cout << "　　　　　　　　　　　　　　　　　┌────────────┐" << endl; 
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　<AI>　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　바위 !　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　└────────────┘" << endl;
		 		break;
			case PAPER:
				cout << "　　　　　　　　　　　　　　　　　┌────────────┐" << endl; 
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　<AI>　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　보 !　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　│　　　　　　　　　　　　│" << endl;
				cout << "　　　　　　　　　　　　　　　　　└────────────┘" << endl;
		 		break;
		 }
		 
		 if(iRPS - iAi_RPS == 1 || iRPS - iAi_RPS == -2)
		 {
		 	cout << endl;
		 	cout << "　　　　　┌────────────────────┐" << endl; 
	 		cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│  　　　　  승리하셨습니다!!　　        │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
		 	getch();
		 	bOrder = true;
		 	break;
		 }
		 else if(iRPS - iAi_RPS == 0)
		 {
		 	cout << endl;
		 	cout << "　　　　　┌────────────────────┐" << endl; 
	 		cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│  　　　　 　 비기셨습니다!!　　        │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
			getch();
			continue; 
		 }
		 else
		 {
		 	cout << endl;
		 	cout << "　　　　　┌────────────────────┐" << endl; 
	 		cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　│  　　　　  패배하셨습니다!!　　        │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘";
		 	getch();
		 	break;
		 }
	 }
	 
	 // 유저와 Ai 의 빙고판을 출력
	int iPlayer_BINGO = 0;
	int iAi_BINGO = 0;
	int iAi_CHOICE;
	int iRecentl_Choice = 0; 
	system("mode con lines=50 cols=63");
 	while(true) 
 	{
 		int iFail = false;
 		system("cls");
		
 		// 플레이어와 Ai를 순서대로 출력한다.
		View_Player(iPlayer_Bingo, bNumber_Check, iPlayer_BINGO);
		cout << endl;
		View_Ai(iAi_Bingo, bNumber_Check, iAi_BINGO) ;
		
		// 빙고 체크 및 승부 발표
		cout << "　　　　　┌────────────────────┐" << endl; 
 		cout << "　　　　　│       　　　　　　　　                 │" << endl;
 		cout << "　　　　　│  　 　 당신의 빙고 : " << iPlayer_BINGO  << "    　　         │"<< endl;
		cout << "　　　　　│   　　 Ai  의 빙고 : " << iAi_BINGO << "                 │" << endl; 
 		cout << "　　　　　│   　 　(" << 5 << " 빙고 달성시 승리!)" << "           │" << endl;
		cout << "　　　　　│       　　　　　　　　                 │" << endl;
		cout << "　　　　　└────────────────────┘" << endl; 
 
 		if(iPlayer_BINGO == iAi_BINGO == 5)
 		{
 			system("cls");
 			cout << "┌─────────────────────────────┐" << endl;
 			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　무승부　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　※상대와 동시에 빙고를 달성했습니다!!※ 　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "└─────────────────────────────┘" << endl;
 			
 			//Ai 빙고판 출력 
 			cout << "┌─────────────────────────────┐" << endl;
			cout << "│　　　　　　　　　　　Ai의 빙고판　 　　　　　　　　　　　│" << endl; 
			cout << "├─────┬─────┬─────┬─────┬─────┤" << endl;
			cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
			for(int i = 0; i < Bingo_Max; i++)
				{
					cout << "│　　";
					for(int j = 0; j < Bingo_Max; j++)
					{
						if(j != 0)cout << "　　";
						if(iAi_Bingo[(Bingo_Max * i) + j] == INT_MAX)
						{
							cout << "●　　│";			
							continue;
						}
						if(iAi_Bingo[(Bingo_Max * i) + j] < 10)cout << " " <<iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					else 
						cout << iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					}
					if(i != Bingo_Max -1)
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl;
							cout << "├─────┼─────┼─────┼─────┼─────┤" << endl;
									cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
						}
					else
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
							cout << "└─────┴─────┴─────┴─────┴─────┘" << endl;
						}
				}
 			return 0;
		 }
		 
		 else if (iPlayer_BINGO >= 5)
		 {
		 	system("cls");
		 	cout << "┌─────────────────────────────┐" << endl;
 			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　승　리　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　 ※상대보다 먼저 빙고를 달성했습니다!!※　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "└─────────────────────────────┘" << endl;
 			
 			//Ai 빙고판 출력 
 			cout << "┌─────────────────────────────┐" << endl;
			cout << "│　　　　　　　　　　　Ai의 빙고판　 　　　　　　　　　　　│" << endl; 
			cout << "├─────┬─────┬─────┬─────┬─────┤" << endl;
			cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
			for(int i = 0; i < Bingo_Max; i++)
				{
					cout << "│　　";
					for(int j = 0; j < Bingo_Max; j++)
					{
						if(j != 0)cout << "　　";
						if(iAi_Bingo[(Bingo_Max * i) + j] == INT_MAX)
						{
							cout << "●　　│";			
							continue;
						}
						if(iAi_Bingo[(Bingo_Max * i) + j] < 10)cout << " " <<iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					else 
						cout << iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					}
					if(i != Bingo_Max -1)
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl;
							cout << "├─────┼─────┼─────┼─────┼─────┤" << endl;
									cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
						}
					else
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
							cout << "└─────┴─────┴─────┴─────┴─────┘" << endl;
						}
				}
 			return 0;
		 }
		 
		 else if(iAi_BINGO >= 5)
		 {
		 	system("cls");
		 	cout << "┌─────────────────────────────┐" << endl;
 			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　패　배　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "│　　　　　　 ※상대가 먼저 빙고를 달성했습니다!!※　　　　│" << endl; 
			cout << "│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│" << endl; 
			cout << "└─────────────────────────────┘" << endl;
 			
 			//Ai 빙고판 출력 
 			cout << "┌─────────────────────────────┐" << endl;
			cout << "│　　　　　　　　　　　Ai의 빙고판　 　　　　　　　　　　　│" << endl; 
			cout << "├─────┬─────┬─────┬─────┬─────┤" << endl;
			cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
			for(int i = 0; i < Bingo_Max; i++)
				{
					cout << "│　　";
					for(int j = 0; j < Bingo_Max; j++)
					{
						if(j != 0)cout << "　　";
						if(iAi_Bingo[(Bingo_Max * i) + j] == INT_MAX)
						{
							cout << "●　　│";			
							continue;
						}
						if(iAi_Bingo[(Bingo_Max * i) + j] < 10)cout << " " <<iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					else 
						cout << iAi_Bingo[(Bingo_Max * i) + j] << "　　│";
					}
					if(i != Bingo_Max -1)
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl;
							cout << "├─────┼─────┼─────┼─────┼─────┤" << endl;
									cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
						}
					else
						{
							cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
							cout << "└─────┴─────┴─────┴─────┴─────┘" << endl;
						}
				}
 			
 			return 0;
		 }
		 
		 // 빙고값 0으로 초기화 
		 iPlayer_BINGO = 0;
		 iAi_BINGO = 0; 
		
		cout << "───────────────────────────────" << endl;
		cout << "Ai가 선택한 수 : "<< iRecentl_Choice << "				< 선택된 수 >" << endl << endl;
		int iSpace = 0;
		for(int i = 0; i < Bingo_Number_Max; i++)
		{
			if(bNumber_Check[i] == true)
			{
				if(i < 9)
					cout << " " << i + 1 << " ";
				else
					cout << i + 1 << " ";
				iSpace++;	
			}
			if(iSpace == 10)
			{
				cout << endl;
				iSpace = 0;
			}
		}
		cout << endl << "───────────────────────────────" << endl;
		cout << endl;
		
		// Ai 의 선택 
		if(bOrder == false)
		{
			cout << "┌─────────────────────────────┐" << endl;
			cout << "│　　　　　　　　　　상대 Ai 의 차례!　　　　　　　　　　　│" << endl; 
			cout << "└─────────────────────────────┘" << endl;
			iAi_CHOICE = Ai_Choice(iAi_Bingo, bNumber_Check, iAi_Difficult, iPlayer_Bingo);
			iRecentl_Choice = iAi_CHOICE;
			if(iRecentl_Choice < 10)
			{
				cout << "　　　　　　　　　　│Ai 의 선택 :  "<< iRecentl_Choice << " │" << endl; 
				cout << "　　　　　　　　　　└────────┘" << endl;
				cout << "　　　　　　　　　　　Press AnyKey...";
			}
			else
			{
				cout << "　　　　　　　　　　│Ai 의 선택 : "<< iRecentl_Choice << " │" << endl; 
				cout << "　　　　　　　　　　└────────┘" << endl;
				cout << "　　　　　　　　　　　Press AnyKey...";
			} 
			getch();
			bOrder = true;
		}
		// 플레이어의 선택 
		else
		{
			cout << "┌─────────────────────────────┐" << endl;
			cout << "│　　　　　　　　　　플레이어의 차례!　　　　　　　　　　　│" << endl; 
			cout << "└─────────────────────────────┘" << endl;
			cout << "　　　　　　　　　　숫자를 입력하세요 : ";
			iFail =	Player_Choice(iPlayer_Bingo, bNumber_Check, iAi_Bingo, iRecentl_Choice);
			if(iFail == false)continue;
			bOrder = false;
		}
		 
	 }
 
 cout << " 종료 " << endl; 
 
	 return 0;
	 
 }
 
 // 플레이어가 선택하는 사항 
 int Player_Choice(int iPlayer_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int iAi_Bingo[Bingo_Arr], int iRecentl_Choice)
 {
 	int iTemp;
 	while(true)
 	{
 		cin >> iTemp;
 		cin.clear();
 		cin.ignore(1000, '\n');
 		if(cin.fail() || iTemp < 0 || iTemp > Bingo_Number_Max)
 		{
 			cout << "　　　　　┌────────────────────┐" << endl; 
 			cout << "　　　　　│       　　　　　　　　                 │" << endl;
 			cout << "　　　　　│    　※올바르지 않은 입력입니다※　　  │" << endl;
			cout << "　　　　　│       　　　　　　　　                 │" << endl;
			cout << "　　　　　└────────────────────┘" << endl; 
			cout << "　　　　　　　　　　　　Press AnyKey...";
 			cin.clear();
 			cin.ignore(1000, '\n');
 			return 0;
		 }
		 for(int i = 0; i < Bingo_Arr; i++)
		{
			if(iPlayer_Bingo[i] == iTemp)
			{
				if(bNumber_Check[iPlayer_Bingo[i] - 1] == true)
				{
					cout << "　　　　　┌────────────────────┐" << endl; 
		 			cout << "　　　　　│       　　　　　　　　                 │" << endl;
		 			cout << "　　　　　│    　　※이미 입력한 수입니다※　　　  │" << endl;
					cout << "　　　　　│       　　　　　　　　                 │" << endl;
					cout << "　　　　　└────────────────────┘" << endl; 
					cout << "　　　　　　　　　　　　Press AnyKey...";
					getch();
					return 0; 
				}
				else
				{
					for(int j = 0 ; j < Bingo_Arr; j++)
					{
						if(iAi_Bingo[j] == iTemp)
						{
							iAi_Bingo[j] = INT_MAX;
						}
							
					}
					bNumber_Check[iPlayer_Bingo[i] - 1] = true;
					if(iPlayer_Bingo[i] < 10)
					{
						cout << "　　　　　　　　　　┌────────┐" << endl;
						cout << "　　　　　　　　　　│당신의 선택 :  "<< iPlayer_Bingo[i] << "│" << endl; 
						cout << "　　　　　　　　　　└────────┘" << endl;
						cout << "　　　　　　　　　　　Press AnyKey...";
					}
					else
					{
						cout << "　　　　　　　　　　┌────────┐" << endl;
						cout << "　　　　　　　　　　│당신의 선택 : "<< iPlayer_Bingo[i] << "│" << endl; 
						cout << "　　　　　　　　　　└────────┘" << endl;
						cout << "　　　　　　　　　　　Press AnyKey...";
					} 
					getch();
					iPlayer_Bingo[i] = INT_MAX;
					return 1;
				}
			}
		}
		cout << "　　　　　┌────────────────────┐" << endl; 
		cout << "　　　　　│       　　　　　　　　                 │" << endl;
		cout << "　　　　　│    　※빙고판에 없는 숫자입니다※　　  │" << endl;
		cout << "　　　　　│       　　　　　　　　                 │" << endl;
		cout << "　　　　　└────────────────────┘" << endl; 
		cout << "　　　　　　　　　　　　Press AnyKey...";
		getch();
		 
		return 0;
	 }
 }
 
 // Ai 가 선택하는 함수 
 int Ai_Choice(int iAi_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int iDifficult, int iPlayer_Bingo[Bingo_Arr])
{
	int iTemp;
	int iReturn = 1;
	
	int iAi_Temp = 0;
	// Nothing = 0, Width = 1, Height = 2, Left_Dir = 3, Right_Dir = 4
	static int iAi_Status = Nothing;
	int iAi_Count = 0; 
	static int iWay_i = 0;
	static int iWay_j = 0;
	// 0 = 가로, 1 = 세로, 2 = 왼쪽대각선, 3 = 오른쪽 대각선 
	bool Bingo_State[Bingo_Arr][4] = {};
	
	// HELL 모드 별 숫자 를저장 하는 변수 
	int iSave = 0;
	int iStar = 0;
 	int iStar_H[5] = {}; 
 	int iCount = 0;
 	int iCount_H[5] = {};
 	int iState = 0;
	
	// 대각선이 안되는 수들은 대각선값을 모두 1로 변경 
	for(int i = 0; i < Bingo_Max; i++)
	{
		for(int j = 0; j < Bingo_Max; j++)
		{
			// 왼쪽 대각선 
			if(((Bingo_Max * i) + j) % Bingo_Left_Dir != 0)
			{
				Bingo_State[(Bingo_Max * i) + j][3] = 1;	
			}
			// 오른쪽 대각선 
			// 0 은 오른쪽 대각선을 막는다 
			Bingo_State[0][4] = 1;
			// 마지막 숫자도 마찬가지 
			Bingo_State[Bingo_Arr - 1][4] = 1;
			if(((Bingo_Max * i) + j) % Bingo_Right_Dir != 0 && ((Bingo_Max * i) + j) != 0 && ((Bingo_Max * i) + j) != (Bingo_Max - 1))
			{
				Bingo_State[(Bingo_Max * i) + j][4] = 1;	
			}
		}
	}
	// 쉬움난이도 
	if(iDifficult == 0)
	{
			cout << "　　　　　　　　　　┌────────┐" << endl;
			cout << "　　　　　　　　　　│ 난이도 : EASY  │" << endl; 
			cout << "　　　　　　　　　　├────────┤" << endl;
		// 1 ~ 배열 최대값 까지 구한다
		iTemp = rand() % Bingo_Arr;
		
		// 해당 배열의 값이 중복인지 구하고 중복이면 아닐때 까지 반복 
		while(iAi_Bingo[iTemp] == INT_MAX)
			iTemp = rand() % Bingo_Arr;
		
		// 해당값을 중복으로 표시 
		bNumber_Check[iAi_Bingo[iTemp] - 1] = true;
		
		// 플레이어의 빙고 도 같은수를 표시해준다 
		for(int j = 0 ; j < Bingo_Arr; j++)
			if(iPlayer_Bingo[j] == iAi_Bingo[iTemp])
				iPlayer_Bingo[j] = INT_MAX; 

		iReturn = iAi_Bingo[iTemp];
		iAi_Bingo[iTemp] = INT_MAX;
		return iReturn;
	}
	// 어려움 난이도 
	else if(iDifficult == 1)
	{
			cout << "　　　　　　　　　　┌────────┐" << endl;
			cout << "　　　　　　　　　　│ 난이도 : HARD  │" << endl; 
			cout << "　　　　　　　　　　├────────┤" << endl;
		// 1 ~ 배열 최대값 까지 구한다
		// 방향이 정해저있으면 그뱡항이 끝날때가지 계속 반복 
		if(iAi_Status != Nothing) 
		{
			// 가로 
			if(iAi_Status == Width) 
			{
				for(int j = 0; j < Bingo_Max; j++)
				{
					if(iAi_Bingo[(Bingo_Max * iWay_i) + j] != INT_MAX)
					{
						// 해당값을 중복으로 표시 
						bNumber_Check[iAi_Bingo[(Bingo_Max * iWay_i) + j] - 1] = true;
						// 플레이어의 빙고 도 같은수를 표시해준다 
						for(int t = 0 ; t < Bingo_Arr; t++)
						{
							if(iPlayer_Bingo[t] == iAi_Bingo[(Bingo_Max * iWay_i) + j])
							{
								iPlayer_Bingo[t] = INT_MAX; 
							}
						}
						iReturn = iAi_Bingo[(Bingo_Max * iWay_i) + j];
						iAi_Bingo[(Bingo_Max * iWay_i) + j] = INT_MAX;
						return iReturn;
					}
					iAi_Count++;
				}
			}
			
			// 세로 
			if(iAi_Status == Height) 
			{
				for(int i = 0; i < Bingo_Max; i++)
				{
					if(iAi_Bingo[(Bingo_Max * i) + iWay_j] != INT_MAX)
					{
						// 해당값을 중복으로 표시 
						bNumber_Check[iAi_Bingo[(Bingo_Max * i) + iWay_j] - 1] = true;
						
						// 플레이어의 빙고 도 같은수를 표시해준다 
						for(int t = 0 ; t < Bingo_Arr; t++)
						{
							if(iPlayer_Bingo[t] == iAi_Bingo[(Bingo_Max * i) + iWay_j])
							{
								iPlayer_Bingo[t] = INT_MAX; 
							}
						}
						iReturn = iAi_Bingo[(Bingo_Max * i) + iWay_j];
						iAi_Bingo[(Bingo_Max * i) + iWay_j] = INT_MAX;
						return iReturn;
					}
					iAi_Count++;
				}
			}
			
			// 왼_대 
			if(iAi_Status == Left_Dir) 
			{
				for(int i = 0; i < Bingo_Max; i++)
				{
					for(int j = 0; j < Bingo_Max; j++)
					{
						if(((Bingo_Max * i) + j) % Bingo_Left_Dir == 0 && iAi_Bingo[(Bingo_Max * i) + j] != INT_MAX)
						{
							// 해당값을 중복으로 표시 
							bNumber_Check[iAi_Bingo[(Bingo_Max * i) + j] - 1] = true;
							// 플레이어의 빙고 도 같은수를 표시해준다 
							for(int t = 0 ; t < Bingo_Arr; t++)
							{
								if(iPlayer_Bingo[t] == iAi_Bingo[(Bingo_Max * i) + j])
								{
									iPlayer_Bingo[t] = INT_MAX; 
								}
							}
							iReturn = iAi_Bingo[(Bingo_Max * i) + j];
							iAi_Bingo[(Bingo_Max * i) + j] = INT_MAX;
							return iReturn;
						}
					}
				}
			}
			
			// 오_대 
			if(iAi_Status == Right_Dir) 
			{
				for(int i = 0; i < Bingo_Max; i++)
				{
					for(int j = 0; j < Bingo_Max; j++)
					{
						if(((Bingo_Max * i) + j) % Bingo_Right_Dir == 0 && iAi_Bingo[(Bingo_Max * i) + j] != INT_MAX && iAi_Bingo[(Bingo_Max * i) + j] != 0 && iAi_Bingo[(Bingo_Max * i) + j] != Bingo_Max - 1)
						{
							// 해당값을 중복으로 표시 
							bNumber_Check[iAi_Bingo[(Bingo_Max * i) + j] - 1] = true;
							// 플레이어의 빙고 도 같은수를 표시해준다 
							for(int t = 0 ; t < Bingo_Arr; t++)
							{
								if(iPlayer_Bingo[t] == iAi_Bingo[(Bingo_Max * i) + j])
								{
									iPlayer_Bingo[t] = INT_MAX; 
								}
							}
							iReturn = iAi_Bingo[(Bingo_Max * i) + j];
							iAi_Bingo[(Bingo_Max * i) + j] = INT_MAX;
							return iReturn;
						}
					}
				}
			}
			
			if(iAi_Count == 5)
			iAi_Status = Nothing;
		}
		
		iTemp = rand() % Bingo_Arr;
		
		// 해당 배열의 값이 중복인지 구하고 중복이면 아닐때 까지 반복 
		while(iAi_Bingo[iTemp] == INT_MAX)
		{
			iTemp = rand() % Bingo_Arr;
			iReturn++;
		}

		// 해당값을 중복으로 표시 
		bNumber_Check[iAi_Bingo[iTemp] - 1] = true;
		
		// 가로, 세로 ,대각선을 정해준다 
		while(true)
		{
			(iAi_Temp = rand() % 4) + 1;
			if(Bingo_State[iTemp][iAi_Temp] == false && iAi_Temp == 1)
			{
				iAi_Status = Width;
				break;	
			}
			else if(Bingo_State[iTemp][iAi_Temp] == false && iAi_Temp == 2)
			{
				iAi_Status = Height;
				break;	
			}
			else if(Bingo_State[iTemp][iAi_Temp] == false && iAi_Temp == 3)
			{
				iAi_Status = Left_Dir;
				break;	
			}
			else if(Bingo_State[iTemp][iAi_Temp] == false && iAi_Temp == 4)
			{
				iAi_Status = Right_Dir;
				break;	
			}

		// 해당값을 중복헤제 
		bNumber_Check[iAi_Bingo[iTemp] - 1] = false;
		iTemp = rand() % Bingo_Arr;
		// 해당 배열의 값이 중복인지 구하고 중복이면 아닐때 까지 반복 
		while(iAi_Bingo[iTemp] == INT_MAX)
				iTemp = rand() % Bingo_Arr;
		bNumber_Check[iAi_Bingo[iTemp] - 1] = true;
	}

		// i j 값을 저장한다. 
		for(int i = 0; i < Bingo_Max; i++)
			for(int j = 0; j < Bingo_Max; j++)
			{
				if((Bingo_Max * i) + j == iTemp)
				{
					iWay_i = i;
					iWay_j = j;
				}
			}

		// 플레이어의 빙고 도 같은수를 표시해준다 
		for(int j = 0 ; j < Bingo_Arr; j++)
		{
			if(iPlayer_Bingo[j] == iAi_Bingo[iTemp])
			{
				iPlayer_Bingo[j] = INT_MAX; 
			}
		}
		iReturn = iAi_Bingo[iTemp];
		iAi_Bingo[iTemp] = INT_MAX;
		return iReturn;
	}
	
	// HELL 모드 
	else if(iDifficult == 2)
	{
			cout << "　　　　　　　　　　┌────────┐" << endl;
			cout << "　　　　　　　　　　│ 난이도 : HELL  │" << endl; 
			cout << "　　　　　　　　　　├────────┤" << endl;
			
				iSave = 0;
				for(int i = 0; i < 5; i++)
				{
					for(int j = 0; j < 5; j++)
					{
						// 별개수 세기 
						if(iAi_Bingo[i * 5 + j] == INT_MAX)
						{
							iStar++;
							iStar_H[j]++;
						}													
						// 세로일떄
						if(i == 4 && j == 4)
						{
							for(int t = 0; t < 5; t++)
							{
								if(iStar_H[t] > iSave && iStar_H[t] < 5)
								{
									iSave = iStar_H[t];
									iWay_j = t;
									iState = 2;
								}
								iStar_H[t] = 0;
							}
						}
					}
					// 가로 일떄 
					if(iStar > iSave && iStar < 5)
					{
						iSave = iStar;
						iWay_i = i;
						iState = 1;
					}
					iStar = 0;
				}
				// 왼오 대각 
				for(int i = 0; i < 25; i += 6)
				{
					if(iAi_Bingo[i] == INT_MAX)iStar++;
				}
				if(iStar > iSave && iStar < 5)
				{
					iSave = iStar;
					iState = 3;
				}
				iStar = 0;
				
				// 오왼 대각 
				for(int i = 4; i <= 20; i += 4)
				{
					if(iAi_Bingo[i] == INT_MAX)iStar++;
				}
				if(iStar > iSave && iStar < 5)
				{
					iSave = iStar;
					iState = 4;
				}
				iStar = 0;
				
				switch(iState)
				{
					// 가로 
					case 1:
						for(int j = 0; j < 5; j++)
						{
							if(iAi_Bingo[iWay_i * 5 + j] != INT_MAX)
							{
								iReturn = iAi_Bingo[iWay_i * 5 + j];
								// 입력값을 찾아서 * 로 만든다
								for(int t = 0; t < Bingo_Arr; t++)
								{
									if(iPlayer_Bingo[t] == iReturn)
									{
										bNumber_Check[iReturn - 1] = true;
										iPlayer_Bingo[t] = INT_MAX;
										break;
									}
								}
								for(int t = 0; t < 25; t++)
								{
									if(iAi_Bingo[t] == iReturn)
									{
										iAi_Bingo[t] = INT_MAX;
										return iReturn;
									}
								}
								break;
							}
						}
						break;
					// 세로 
					case 2:
						for(int i = 0; i < 5; i++)
						{
							if(iAi_Bingo[i * 5 + iWay_j] != INT_MAX)
							{
								iReturn = iAi_Bingo[i * 5 + iWay_j];
								// 입력값을 찾아서 * 로 만든다
								for(int t = 0; t < 25; t++)
								{
									if(iPlayer_Bingo[t] == iReturn)
									{
										bNumber_Check[iReturn - 1] = true;
										iPlayer_Bingo[t] = INT_MAX;
										break;
									}
								}
								for(int t = 0; t < Bingo_Arr; t++)
								{
									if(iAi_Bingo[t] == iReturn)
									{
										iAi_Bingo[t] = INT_MAX;
										return iReturn;
									}
								}
								break;
							}
						}
						break;
					// 왼대 
					case 3:
						for(int i = 0; i < Bingo_Arr; i += 6)
						{
							if(iAi_Bingo[i] != INT_MAX)
							{
								iReturn = iAi_Bingo[i];
								for(int t = 0; t < 25; t++)
								{
									if(iPlayer_Bingo[t] == iReturn)
									{
										bNumber_Check[iReturn - 1] = true;
										iPlayer_Bingo[t] = INT_MAX;
										break;
									}
								}
								for(int t = 0; t < 25; t++)
								{
									if(iAi_Bingo[t] == iReturn)
									{
										iAi_Bingo[t] = INT_MAX;
										return iReturn;
									}
								}
								break;
							}
						}
						break;
					// 오대 
					case 4:
						for(int i = 0; i <= 20; i += 4)
						{
							if(iAi_Bingo[i] != INT_MAX)
							{
								iReturn = iAi_Bingo[i];
								for(int t = 0; t < Bingo_Arr; t++)
								{
									if(iPlayer_Bingo[t] == iReturn)
									{
										bNumber_Check[iReturn - 1] = true;
										iPlayer_Bingo[t] = INT_MAX;
										break;
									}
								}
								for(int t = 0; t < Bingo_Arr; t++)
								{
									if(iAi_Bingo[t] == iReturn)
									{
										iAi_Bingo[t] = INT_MAX;
										return iReturn;
									}
								}
								break;
							}
						}
						break;
				}
			// Ai 가 처음일떄 랜덤 숫자 출력 
			iTemp = rand() % Bingo_Arr;
			bNumber_Check[iAi_Bingo[iTemp] - 1] = true;
			for(int j = 0 ; j < Bingo_Arr; j++)
				if(iPlayer_Bingo[j] == iAi_Bingo[iTemp])
					iPlayer_Bingo[j] = INT_MAX; 
			iReturn = iAi_Bingo[iTemp];
			iAi_Bingo[iTemp] = INT_MAX;
			return iReturn;												
	}
}
 
 // 플레이어의 빙고판 출력 밑 빙고 검사 
void View_Player(int iPlayer_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int& iPlayer_BINGO)
{
	// 가로빙고
	int iBingo_Width[Bingo_Max] = {};
	// 세로빙고
	int iBingo_Height[Bingo_Max] = {};
	// 대각선 빙고
	int iBingo_Dir[2] = {};
	bool bBingo_Temp[2] = {}; 

		cout << "┌─────────────────────────────┐" << endl;
		cout << "│　　　　　　　　　　　　　빙고판　　　　　　　　　　　　　│" << endl; 
		cout << "├─────┬─────┬─────┬─────┬─────┤" << endl;
		cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
		for(int i = 0; i < Bingo_Max; i++)
		{
			cout << "│　　";
			for(int j = 0; j < Bingo_Max; j++)
			{
				if(j != 0)cout << "　　";
				if(iPlayer_Bingo[(Bingo_Max * i) + j] == INT_MAX)
				{
					cout << "●　　│";
					// 가로빙고 체크 
					iBingo_Width[i] += 1;
					if(iBingo_Width[i] == Bingo_Max)
						iPlayer_BINGO += 1;
						
					// 세로빙고 체크
					iBingo_Height[j] += 1; 
					if(iBingo_Height[j] == Bingo_Max)
						iPlayer_BINGO += 1; 
						
					// 왼쪽 대각선 빙고 체크
					if(((Bingo_Max * i) + j) % Bingo_Left_Dir == 0)
					{
						iBingo_Dir[0] += 1;
						if(iBingo_Dir[0] == Bingo_Max && bBingo_Temp[0] == false)
						{
							iPlayer_BINGO += 1;
							bBingo_Temp[0] = true;	
						}
					}
						
					// 오른쪽 대각선 빙고 체크 ,마지막 숫자 제외 
					if(((Bingo_Max * i) + j) % Bingo_Right_Dir == 0 && ((Bingo_Max * i) + j) != 0 && ((Bingo_Max * i) + j) != (Bingo_Arr - 1) )
					{
						iBingo_Dir[1] += 1;
						if(iBingo_Dir[1] == Bingo_Max && bBingo_Temp[1] == false)
						{
							iPlayer_BINGO += 1;
							bBingo_Temp[1] = true;	
						}
					}
					continue;
				}
				if(iPlayer_Bingo[(Bingo_Max * i) + j] < 10)cout << " " << iPlayer_Bingo[(Bingo_Max * i) + j] << "　　│";
				else 
					cout << iPlayer_Bingo[(Bingo_Max * i) + j] << "　　│";
			}
			if(i != Bingo_Max -1)
			{
				cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl;
				cout << "├─────┼─────┼─────┼─────┼─────┤" << endl;
				cout << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
			}
			else
			{
				cout << endl << "│　　　　　│　　　　　│　　　　　│　　　　　│　　　　　│" << endl; 
				cout << "└─────┴─────┴─────┴─────┴─────┘" << endl;
			}
		}
}

// Ai 의 빙고판을 출력 밑 빙고검사 
void View_Ai(int iAi_Bingo[Bingo_Arr], bool bNumber_Check[Bingo_Number_Max], int& iAi_BINGO)
{
	// 가로빙고
	int iBingo_Width[Bingo_Max] = {};
	// 세로빙고
	int iBingo_Height[Bingo_Max] = {};
	// 대각선 빙고
	int iBingo_Dir[2] = {};
	bool bBingo_Temp[2] = {}; 
	
		for(int i = 0; i < Bingo_Max; i++)
		{
			for(int j = 0; j < Bingo_Max; j++)
			{
				if(iAi_Bingo[(Bingo_Max * i) + j] == INT_MAX)
				{
					// 가로빙고 체크 
					iBingo_Width[i] += 1;
					if(iBingo_Width[i] == Bingo_Max)
						iAi_BINGO += 1;
						
					// 세로빙고 체크
					iBingo_Height[j] += 1; 
					if(iBingo_Height[j] == Bingo_Max)
						iAi_BINGO += 1; 
						
					// 왼쪽 대각선 빙고 체크
					if(((Bingo_Max * i) + j) % Bingo_Left_Dir == 0)
					{
						iBingo_Dir[0] += 1;
						if(iBingo_Dir[0] == Bingo_Max && bBingo_Temp[0] == false)
						{
							iAi_BINGO += 1;
							bBingo_Temp[0] = true;	
						}
					}
						
					// 오른쪽 대각선 빙고 체크 ,마지막 숫자 제외 
					if(((Bingo_Max * i) + j) % Bingo_Right_Dir == 0 && ((Bingo_Max * i) + j) != 0 && ((Bingo_Max * i) + j) != (Bingo_Arr - 1) )
					{
						iBingo_Dir[1] += 1;
						if(iBingo_Dir[1] == Bingo_Max && bBingo_Temp[1] == false)
						{
							iAi_BINGO += 1;
							bBingo_Temp[1] = true;	
						}
					}
					
					continue;
				}
			}
		}
}
