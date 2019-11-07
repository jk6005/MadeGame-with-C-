#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	// 난수 발생
	srand((unsigned int)time(0));

	int iUpgrade = 0;
	cout << "Upgrade 기본 수치를 입력하세요 : ";
	cin >> iUpgrade;
		
	// 강화 확률을 구한다.
	float fPercent = rand() % 10000 / 100.f;
	
	// 강화확률 : 업그레이드가 0 ~ 3 : 100% 성공 4 ~ 6 : 40 % 7 ~ 9 : 10;
	// 10 ~ 13 : 1% 14 ~ 15 : 0.01%
	cout << "Upgrade : " << iUpgrade << endl;
	
	int t = 0, p = 1;
	
	while(t != 1)
	{
		cout << "Percent : " << fPercent << endl;
	if(iUpgrade <= 3)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
	
	else if(4 <= iUpgrade && iUpgrade <= 6)
	{
		if(fPercent < 40.f)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
		else 
		{
			cout << "강화 실패" << endl;
			fPercent = rand() % 10000 / 100.f;
			p++;
		}
	}
	
	else if(7 <= iUpgrade && iUpgrade <= 9)
	{
		if(fPercent < 10.f)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
		else 
			{
			cout << "강화 실패" << endl;
			fPercent = rand() % 10000 / 100.f;
			p++;
		}
	}
	
	else if(10 <= iUpgrade && iUpgrade <= 13)
	{
		if(fPercent < 1.f)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
		else 
			{
			cout << "강화 실패" << endl;
			fPercent = rand() % 10000 / 100.f;
			p++;
		}
	}
	
	else if(14 <= iUpgrade && iUpgrade <= 15)
	{
		if(fPercent < 0.01f)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
		else 
			{
			cout << "강화 실패" << endl;
			fPercent = rand() % 10000 / 100.f;
			p++;
		}
	}
		
	else if(iUpgrade == 16)
	{
		if(fPercent < 0.25f)
		{
			cout << "강화 성공" << endl;
			t = 1;
		}
		else
		{
			cout << "강화 실패" <<endl;
			fPercent = rand() % 10000/100.f;
			p++;
		}
	}
	}
	cout << "시도횟수 : " << p << endl;
	return 0;
}