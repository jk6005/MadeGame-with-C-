#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

// Count + 1(보너스) // EX)) Lotto_Count 6 == 7
#define Lotto_Count 6
// 로또 숫자 최댓값
#define Lotto_Max 45
// 최대 티켓 구매수
#define Ticket_MAX 10000
// 티켓 가격
#define Ticket_Money 1000
// 당첨금 15억 최대 21억 원 까지 가능 (int 기준)
#define Lotto_Reward 1500000000 
#define Lotto_1st	(Lotto_Reward / 100) * 75
#define Lotto_2st	(Lotto_Reward / 100) * 12.5
#define Lotto_3st	(Lotto_Reward / 100) * 12.5
#define Lotto_4st	50000
#define Lotto_5st	5000


// 자릿수 표시기
#include <iostream>
using namespace std;

// 32비트 int 형 기준 자릿값 출력기
void int_Money_State(int money)
{
	// 백만 이상값 100의 자릿수 0 추가 유무 ex) 001 011 000
	bool bCipher_Count = false;
	
	// 음수면 - 출력후 양수로 변환
	if(money < 0)
	{
		cout << '-';
		money *= -1;
	}
	
	// 나머지 값을 저장할 temp 변수
	int temp = 0;
	
	// 오직 100 의 자리 일떄만
	if(money < 1000 && bCipher_Count == false)
			cout << money;
	
	// 1000 이상값의 100 의자리
	if(money < 1000 && bCipher_Count == true)
	{
		NEXT_3:
		if(money >= 100)
			cout << money;
		else if(money >= 10 && money < 100)
			cout << '0' << money;
		else
			cout << "00" << money;
	}
	// 일천 이상 백만 미만
	else if(money >= 1000 && money < 1000000)
	{
		NEXT_1:
		cout << money / 1000 << ',';
		temp = money % 1000;
		if(temp >= 100)
			cout << temp;
		// 공백이 생기면 0 으로 채우고 100의자릿수 출력
		else if(temp < 100 && temp > 10)
			cout << '0' << temp;
		else if(temp < 10 && temp > 0)
			cout << "00" << temp;
		else if(temp == 0)
			cout << "000";
	}
	// 백만 이상 십억 미만
	else if(money >= 1000000 && money < 1000000000)
	{
		NEXT_2:
		cout << money / 1000000 << ',';
		temp = money % 1000000;
		if(temp >= 100000 && temp < 1000000)
		{
			// temp 값을 변경한다
			money = temp;
			// 나머지 값은 백만 미만 계산하는 if 문으로 강제이동
			goto NEXT_1;
		}
		else if(temp >= 10000 && temp < 100000)
		{
			cout << '0';
			money = temp;
			goto NEXT_1;
		}
		else if(temp >= 1000 && temp < 10000)
		{
			cout << "00";
			money = temp;
			goto NEXT_1;
		}
		else if(temp < 100)
		{
			cout << "000,";
			money = temp;
			bCipher_Count = true;
			// 중간자리가 모두 0 이므로 강제로 100의자릿수 출력 if 문으로 이동
			goto NEXT_3;
		}
	}
	// 십억 이상 2,147,483,647 이하 (int 형 최댓값)
	else if(money >= 1000000000 && temp <= 2147483647)
	{
		cout << money / 1000000000 << ',';
		temp = money % 1000000000;
		money = temp;
		if(temp >= 100000000)
			goto NEXT_2;
		else if(temp >= 10000000 && temp < 100000000)
		{
			cout << '0';
			goto NEXT_2;
		}
		else if(temp < 10000000)
		{
			cout << "00";
			goto NEXT_2;
		}
	}
}

int main()
{
	// 복권 매수 를 저장하는 변수
	int iTicket = 0;
	// 로또 값을 저장할 배열 생성
	int Lotto[Lotto_Count];
	// 로또 상태값을 저장할 배열
	bool Lotto_Num[Lotto_Max] = {};
	// 자동 뽑기 ㅇ무
	bool Lotto_Auto = 0;
	// 등수 카운팅 
	int iCount[5] = {};
	// 총 당청금
	int iReward = 0;
	
	// srand 함수 time 으로 초기화
	srand((unsigned int)time(0));
	
	while(1)
	{
		cout << "───────────────────────────────────────────────" << endl;
		cout << "			복권뽑기					" << endl;
		cout << "총상금	:	";
		int_Money_State(Lotto_Reward);
		cout << "	원" << endl;
		cout << "1등	:	";
		int_Money_State(Lotto_1st);
		cout << "	원" << endl;
		cout << "2등	:	";
		int_Money_State(Lotto_2st);
		cout << "	원" << endl;
		cout << "3등	:	";
		int_Money_State(Lotto_3st);
		cout << "	원" << endl;
		cout << "4등	:	";
		int_Money_State(Lotto_4st);
		cout << "		원" << endl;
		cout << "5등	:	";
		int_Money_State(Lotto_5st);
		cout << "		원" << endl;
		cout << "가격	:	";
		int_Money_State(Ticket_Money);
		cout << "		원" << endl;
		cout << "※ 1,2,3등은 중복되어도 상금의 변화는 없습니다" << endl;
		cout << "───────────────────────────────────────────────" << endl;
		cout << "자동으로 뽑으시겟습니까?" << endl << "※복권값이 자동으로 설정됩니다!" << endl;
		cout << "1. 예 " << "2. 아니오 " << endl;
		cout << "입력 : ";
		cin >> iTicket;
		if(cin.fail())
		{
			cout << "숫자만 입력하세요 " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		if(iTicket < 1 || iTicket > 2)
		{
			cout << "잘못 입력하셧습니다." << endl;
			iTicket = 0;
		}
		if(iTicket > 0)
		{
			if(iTicket == 1)
			{
				Lotto_Auto++;
				cout << "자동 뽑기로 선택하셧습니다." << endl;
				break;
			}
			else
			{
				cout << "수동 뽑기로 선택하셧습니다! " << endl;
				break;
			}
		}
	}
	iTicket = 0;
	// 몇장 살건지 물어보기
	while(iTicket == 0)
	{
		cout <<"몇장을 구매하시겟습니까? (1 ~ " << Ticket_MAX << " 장 구매가능)" << endl;
		cout << "입력 : ";
		cin >> iTicket;
		if(cin.fail())
		{
			cout << "숫자만 입력하세요 " << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			iTicket = 0;
		}
		if(iTicket < 1 || iTicket > Ticket_MAX)
		{
			cout << "1 ~ 10 장 만 구매하실수 있습니다" << endl;
			iTicket = 0;
		}
	}
			cin.ignore(1000, '\n');
	cout << "---------------------" << endl << iTicket << " 장 구매하셧습니다." << endl << "---------------------" << endl;
	
	// 로또 값 구하기
	for(int i = 0; i < Lotto_Count; i++)
	{
		// Lotto 값에 1 ~ 45 값을 대입
		Lotto[i] = rand() % Lotto_Max + 1;
		
		// i 가 1이상일때 중복되는 숫자를 검사해서 있으면 다시 돌린다.
		if(i > 0)
		{
			while(Lotto_Num[Lotto[i]] == 1)
				Lotto[i] = rand() % Lotto_Max + 1;
		}
		Lotto_Num[Lotto[i]]++;
	}
	
	// 오름차순 정렬
	int temp;
	for(int i = 0; i < Lotto_Count; i++)
	{
		for(int j = 0; j < Lotto_Count - 1; j++)
		{
			if(Lotto[j] > Lotto[j + 1])
			{
				temp = Lotto[j];
				Lotto[j] = Lotto[j + 1];
				Lotto[j + 1] = temp;
			}
		}
	}
	
	// 보너스 번호
	int Bonuse;
	bool bBonuse_state = 0;
	Bonuse = rand() % Lotto_Max + 1;
	while(Lotto_Num[Bonuse] == 1)
		Bonuse = rand() % Lotto_Max + 1;
	
	// 플레이어가 입력할 로또값
	int Lotto_Player[iTicket][Lotto_Count] = {};
	
	if(Lotto_Auto == false)
	{
		// 로또 값 입력
		cout << "로또 맞추기! " << Lotto_Count << "개의 숫자를 입력하세요!(0을 입력하면 종료) " << endl;
		for(int t = 0; t < iTicket; t++)
		{
			cout << t + 1 << "번쨰 복권표" << endl;
			for(int i = 0; i < Lotto_Count; i++)
			{
				RESET:
				cout << i + 1 << "번! : ";
				cin >> Lotto_Player[t][i];
				if(cin.fail())
				{
					cout << "숫자만 입려하세요! " << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					goto RESET;
				}
				if(Lotto_Player[t][i] < 0 || Lotto_Player[t][i] > Lotto_Max)
				{
					cout << "1~" << Lotto_Max << " 의 값만 입력하세요!" << endl;
					cin.ignore(1000, '\n');
				goto RESET;
				}
				if(Lotto_Player[t][i] == 0)
				{
					cout << "종료합니다! " << endl;
					return 0;
				}
				// 중복값 검사
				if(i > 0)
				{
					for(int j = 0; j < i; j++)
						if(Lotto_Player[t][i] == Lotto_Player[t][j])
						{
							cout << "이미 입력한 숫자입니다! " << endl;
							cin.ignore(1000, '\n');
							goto RESET;
						}
				}
				cin.ignore(1000, '\n');	
			}
			cout << endl;
		}
	}
	else if(Lotto_Auto == true)
	{
		for(int t = 0; t < iTicket; t++)
		{
			for(int i = 0; i < Lotto_Count; i++)
			{
				RESET_1:
				Lotto_Player[t][i] = rand() % 45 + 1;
				if(i > 0)
				{
					for(int j = 0; j < i; j++)
					{
						if(Lotto_Player[t][i] == Lotto_Player[t][j])
							goto RESET_1;
					}
				}
			}
		}
	}
	
	// 내번호 오름차순 정리
	for(int t = 0; t < iTicket; t++)
	{
		for(int i = 0; i < Lotto_Count; i++)
		{
			for(int j = 0; j < Lotto_Count - 1; j++)
			{
				if(Lotto_Player[t][j] > Lotto_Player[t][j + 1])
				{
					temp = Lotto_Player[t][j];
					Lotto_Player[t][j] = Lotto_Player[t][j + 1];
					Lotto_Player[t][j + 1] = temp;
				}
			}
		}
	}
	
	// 결과 발표 !!
	cout << "──────────────────────────────────────" << endl;
	cout << "		☆☆☆☆☆☆ 당첨번호 ☆☆☆☆☆☆" << endl;
	for(int i = 0; i < Lotto_Count; i++)
		cout << Lotto[i] << "	";
		cout << "보너스 번호! -> " << Bonuse << endl;
	cout << "──────────────────────────────────────" << endl;
	
	int iStack = 0;
	for(int t = 0; t < iTicket; t++)
		{
			// 내번호 출력
			cout << "		☆☆☆☆☆☆" << t + 1 << "장" << "☆☆☆☆☆☆" << endl << endl;
		for(int i = 0; i < Lotto_Count; i++)
			cout << Lotto_Player[t][i] << "	";
			cout << endl;
		
		
		// 당첨 비교 코드
		for(int i = 0; i < Lotto_Count; i++)
		{
			for(int j = 0; j < Lotto_Count; j++)
				if(Lotto_Player[t][i] == Lotto[j])
				{
					iStack++;
					cout << "( " << Lotto_Player[t][i] << " 맞춤! )";
				}
			if(Lotto_Player[t][i] == Bonuse)
			{
				iStack++;
				cout << "( " << Lotto_Player[t][i] << " 보너스 맞춤! )";
			}
		}
	cout << endl;
		// 등수 출력
		switch(iStack)
		{
			case Lotto_Count:
				if(bBonuse_state = false)
				{
					cout << "			1등 당첨!!!" << endl;
					iCount[0]++;
					break;	
				}
				else if(bBonuse_state = true)
				{
					cout << "			2등 당첨!!!" << endl;
					iCount[1]++;
					break;	
				}
			case Lotto_Count - 1:
				cout << "			3등 당첨!!!" << endl;
				iCount[2]++;
				break;
			case Lotto_Count - 2:
				cout << "			4등 당첨!!!" << endl;
				iCount[3]++;
				break;
			case Lotto_Count - 3:
				cout << "			5등 당첨!!!" << endl;
				iCount[4]++;
				break;
			default:
				cout << "			꽝입니다!!" << endl;
				
		}
		cout << "──────────────────────────────────────" << endl;
		iStack = 0;
	}
	
	// 당첨 결과 확인!
	cout << "내가 구매한 티켓 수 : " << iTicket << endl;
	cout << "1등 : " << iCount[0] << "장 =	";
	if(iCount[0] > 0)
	{
		int_Money_State(Lotto_1st);
		cout << "원" << endl;
		iReward += (Lotto_Reward / 100) * 75;
	}
	else
		cout << "0 원" << endl;
	cout << "2등 : " << iCount[1] << "장 =	";
	
	if(iCount[1] > 0)
	{
		int_Money_State(Lotto_2st);
		cout << " 원" << endl;
		iReward += (Lotto_Reward / 100) * 12.5;
	}
	else
		cout << "0 원" << endl;
	cout << "3등 : " << iCount[2] << "장 =	";
	
	if(iCount[2] > 0)
	{
		int_Money_State(Lotto_3st);
		cout <<  " 원" << endl;
		iReward += (Lotto_Reward / 100) * 12.5;
	}
	else
		cout << "0 원" << endl;
	
	cout << "4등 : " << iCount[3] << "장 =	";
	int_Money_State(Lotto_4st * iCount[3]);
	cout << " 원" << endl;
	iReward +=	50000 * iCount[3];
	
	cout << "5등 : " << iCount[4] << "장 =	";
	int_Money_State(Lotto_5st * iCount[4]);
	cout << " 원" << endl;
	iReward +=	5000 * iCount[4];
	
	// 손익 결과 출력
	cout << "──────────────────────────────────────" << endl;
	cout << "			<손익>" << endl;
	int_Money_State(iReward);
	cout << " 원 - ";
	int_Money_State(Ticket_Money * iTicket);
	cout << " 원" << endl;
	cout << "결과 : ";
	if(iReward - (Ticket_Money * iTicket) > 0)
	{
		cout << "+";
		int_Money_State(iReward - (Ticket_Money * iTicket));
		cout << " 원" << endl;
	}
		else
		{
			int_Money_State(iReward - (Ticket_Money * iTicket));
			cout << " 원" << endl;
		}
	
	return 0;
	
}