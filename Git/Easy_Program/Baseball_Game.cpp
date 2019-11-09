#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// 게임 카운트는 9 이하여야 정상 작동 
#define GameCount 3

/*
야구게임 만들기
1 ~ 9 사이의 랜덤한 숫자 3개를 얻어온다. 단, 숫자는 중복되어서는 안된다.
3개의 숫자는 *	*	* 의 형태로 출력되고 이 3개의 숫자를 맞추는 게임이다.
사용자는 이 3개의 숫자를 맞출떄까지 계속해서 3개씩 숫자를 입력한다.
만약 맞춰야할 숫자가 7	3	8 일경우 
상ㅇ자는 3개의 숫자를 계속 입력한다.
입력 : 1 2 4 를 입력했을 경우 1 2 4는 맞춰야할 숫자중 아무것도 없으므로
Out 을 출력한다.

입력 : 7 5 9를 입력했을 경우 7은 맞춰야할 숫자중 있고 위치도 같으므로
Strike이다. 5 9 는 없으로 출력은 1Strike 0ball 을 출력한다.

입력 : 7 8 6 을 입력햿을 경우 7은 1Strike 8 은 숫자는 있지먼 위치가 다르므로 ball 이된다.
1Strike 11ball 을 출력한다.

이렇게 출력을 하고 입력을 받으면서 최종적으로 3개의 숫자를 자리까지 모두 일치하게 입력하면 게임이 종료된다.
만약 입력받은 숫자 3개중 한개라도 0이 있을 경우 게임을 종료한다.
*/

int main()
{
	// 1 ~ 9 의 상태를 저장할 배열 생성 및 0으로 초기화
	int iRandom_Num[9] ={};
	// 값을 저장할 3개의 배열생성
	int iBaseball[GameCount] = {};
	
	// 플레이어가 입력 할 배열 생성
	int iPlayer[GameCount] = {};
	
	// Strike, Ball 을 저장할 값생성
	int iStrike = 0, iBall = 0;
	
	// 게임 종료 카운트 생성
	bool bGame = 0;
	//srand 함수 time 으로 초기화
	srand((unsigned int)time(0));
	
	// iBaseball 에 랜덤값을 넣는다
	for(int i = 0; i < GameCount; i++)
	{
		iBaseball[i] = rand() % 9 + 1;
		
		while(iRandom_Num[iBaseball[i]] != 0)
		{
			iBaseball[i] = rand() % 9 + 1;
		}
		iRandom_Num[iBaseball[i]]++;
	}
	
	while(1)
	{
		// 시작전에 점수를 초기화한다
		iBall = 0;
		iStrike = 0;
		cout << "===========================" << endl;
		cout << "☆☆☆☆ 야구게임 시작! ☆☆☆☆" << endl;
		cout << "게임종료 -> 0입력! " << endl;
		
		// 게임을 3번 한다
		for(int i = 0; i < GameCount; i++)
		{
			// goto 초기화
			RESET:
			cout << i + 1 << "번쨰 ! : ";
			cin >> iPlayer[i];

			// 숫자이외의 값이 들어오면 경고발생!
			if(cin.fail())
			{
				cout << "숫자만 입력하세요!" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				goto RESET;
			}
			
			// 중복되면 초기화
			if(i > 0)
			{
				for(int t = 0; t < i; t++)
				{
					if(iPlayer[i] == iPlayer[t])
					{
						cout << "중복됩니다!" << endl;
						goto RESET;
					}
				}
			}
			
			// 0 값이 들어오면 게임을 끝낸다.
			if(iPlayer[i] == 0)
			{
				bGame++;
				break;
			}
			
			// 1이상 9이하의 값만 출력!
			if(iPlayer[i] > 10 || iPlayer[i] < 0)
			{
				cout << "0 이상 9이하의 값만 대입하세요" << endl;
				goto RESET;
			}
		}
		
		// 플레이어가 입력한 값과 정답을 비교하고 자릿수와 수가 맞으면 strkie 를 올리고 
		// 자릿수만 다르면 ball 을 올린다.
		for(int i = 0; i < GameCount; i++)
		{
			for(int j = 0; j < GameCount; j++)
			{
				if(iPlayer[i] == iBaseball[j])
					if(i == j)
						iStrike++;
				else
					iBall++;
			}
		}
		// Game 값이 1이면 게임종료
		if(bGame == true)break;
		
		// 맞추면 게임종료
		if(iStrike == GameCount)
		{
			cout << "게임에서 승리하엿습니다!" << endl;
			cout << "===========================" << endl;
			cout << endl;
			break;
		}
		
		// 허나도 못맞추면 아웃 출력
		if(iStrike == 0 && iBall == 0)
		{
			cout << endl;
			cout << "OUT!" << endl;
			cout << "===========================" << endl;
			cout << endl;
			continue;
		}
		cout << endl;
		cout << iStrike << "Strike " << iBall << "Ball" << endl;
		cout << "===========================" << endl << endl;
		
	}
	cout << "----게임 종료됨----" << endl << endl;
	cout << "===========================" << endl << endl;
	return 0;
}