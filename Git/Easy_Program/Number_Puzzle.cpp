#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// 빙고 의 가로줄 혹은 세로줄
// 대각선 값은 BingGo_Num +1 들의 조합임
#define BingGo_Num	5
// 빙고의 배열
#define BingGo_Arr (BingGo_Num * BingGo_Num)
// 구름IDE 임시로 50000 을 맥스값으로 지정
//#define INT_MAX 50000

int main()
{
	srand((unsigned int)time(0));
	
	// 빙고 배열 선언및 1부터 오름차순으로 초기화
	int iBingo[BingGo_Arr];
	
	for (int i = 0; i < BingGo_Arr; i++)
		iBingo[i] = i + 1;
	
	// 배열 셔플
	for(int i = 0; i < 100; i++)
	{
		int dex1 = rand() % BingGo_Arr;
		int dex2 = rand() % BingGo_Arr;
		int temp;
		
		temp = iBingo[dex1];
		iBingo[dex1] = iBingo[dex2];
		iBingo[dex2] = temp;
	}
	
	//BingGo 값을 저장할 배열
	// 최대 빙고값은 (BingGo_Num * 2) + 5 
	bool bBingo[ (BingGo_Num * 2) + 5 ] = {}; 
	//가로줄 카운트 
	int iBingo_Width_Count = 0;
	//세로줄 카운트
	int iBingo_Height_Count[BingGo_Num] = {0,};
	// 대각선 카운트 왼쪽 대각 오른쪽 대각 
	int iBingo_Dia_Count[2] = {};
	 
	
	// 가로줄 * 세로줄 출력
	while(1)
	{
		int iBingo_View = 0;
		system("cls");
		for(int i = 0; i < BingGo_Num; i++)
		{
			for(int j = 0; j < BingGo_Num; j++)
			{ 
				// 가로줄의 빙고값이 연속되면 빙고 배열을 증가시킨다. 
				if(iBingo[(i * BingGo_Num) + j] == INT_MAX)
				{
					cout << "*	";
					iBingo_Width_Count++;
					// 왼쪽 대각선 줄 빙고 판독기  BingGo_Num * 2(왼쪽) ~ BingGo_Num * 2 + 1(오른쪽) 
					if(((i * BingGo_Num) + j) % (BingGo_Num + 1) == 0)
					{
						iBingo_Dia_Count[0]++;
						if(iBingo_Dia_Count[0] == BingGo_Num)
							bBingo[BingGo_Num * 2] = true;
					} 
					//오른쪽 대각선 줄 빙고 판독기
					//  1. (BingGo_Num - 1) 로 나누지만 0 은 무엇으로 나누어도 0이기 떄문에 제외한다.
					//	2. BingGo_Num * BingGo_Num 의 형태는  (BingGo_Num - 1) 로 나누어도 결국은 (BingGo_Num - 1) 의 배수가 하나 더 나오기 떄문에
					//	    (BingGo_Num - 1) * BingGo_Num 값보다 적을떄만 계산 하도록 한다. 
					 if(((i * BingGo_Num) + j) % (BingGo_Num - 1) == 0 && ((i * BingGo_Num) + j) != 0 && ((i * BingGo_Num) + j) <= (BingGo_Num - 1) * BingGo_Num)
					 {
					 	iBingo_Dia_Count[1]++;
						if(iBingo_Dia_Count[1] == BingGo_Num)
							bBingo[BingGo_Num * 2 + 1] = true;
					 }
					// 가로 줄 빙고 판독기 0 ~  (BingGo_Num - 1)
					if(iBingo_Width_Count == BingGo_Num)
					{
						iBingo_Width_Count = 0;
						bBingo[i] = true;
					}
					// 세로줄 빙고 판독기  BingGo_Num ~ BingGo_Num + BingGo_Num - 1
					iBingo_Height_Count[j]++;
					//세로줄의 빙고 배열 BingGo_Num ~ BingGo_Num + 4 
					if(iBingo_Height_Count[j] == BingGo_Num)
						bBingo[BingGo_Num + j] = true;
					continue;
				}
				iBingo_Width_Count = 0;
				cout << iBingo[(i * BingGo_Num) + j] << "	";
			}
			cout << endl << endl;
		}
		// 세로줄 빙고 카운트 0으로 초기화 
		for(int j = 0; j < BingGo_Num; j++)
			iBingo_Height_Count[j] = 0;
		// 대각선 빙고 카운트 0으로 초기화
		 for(int j = 0; j < 2; j++)
		 	iBingo_Dia_Count[j] = 0;
		// 숫자를 입력받고 해당숫자를 별 처리한다.
		int iInput;
		for(int t = 0; t < (BingGo_Num * 2) + 5; t++)
		{
			iBingo_View += (int)bBingo[t];
		}
		if(iBingo_View == BingGo_Num)
		{
			system("cls");
			cout << "──────────────────────" << endl;
			cout << BingGo_Num << " 빙고!! 게임에 승리하셧습니다!!" << endl;
			cout << "──────────────────────" << endl;
			break;
		}
		cout << "현재 ";
		cout << iBingo_View << " 빙고! (" << BingGo_Num << " 빙고 달성 시 게임승리)" << endl;
		cout << "1 ~ " << BingGo_Arr << " 입력 : (0 입력시 종료) : ";
		cin >> iInput;
		if(cin.fail())
		{
			cout << "1 ~ " << BingGo_Arr << " 사이의 숫자만 입력하세요." << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			continue;
		}
		if(iInput == 0)
		{
			cout << "종료 되었습니다. " << endl;
			break;
		}
		if(iInput > BingGo_Arr || iInput < 0)
		{
			cout << "1 ~ " << BingGo_Arr << " 사이의 숫자만 입력하세요." << endl;
			continue;
		}
		
		for(int i = 0; i < BingGo_Arr; i++)
			if(iBingo[i] == iInput)
				iBingo[i] = INT_MAX;
				
	}
	
	return 0;
}