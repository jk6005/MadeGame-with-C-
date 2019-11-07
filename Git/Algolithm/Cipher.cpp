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
		CIPHER_3:
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
		CIPHER_1:
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
		CIPHER_2:
		cout << money / 1000000 << ',';
		temp = money % 1000000;
		if(temp >= 100000 && temp < 1000000)
		{
			// temp 값을 변경한다
			money = temp;
			// 나머지 값은 백만 미만 계산하는 if 문으로 강제이동
			goto CIPHER_1;
		}
		else if(temp >= 10000 && temp < 100000)
		{
			cout << '0';
			money = temp;
			goto CIPHER_1;
		}
		else if(temp >= 1000 && temp < 10000)
		{
			cout << "00";
			money = temp;
			goto CIPHER_1;
		}
		else if(temp < 100)
		{
			cout << "000,";
			money = temp;
			bCipher_Count = true;
			// 중간자리가 모두 0 이므로 강제로 100의자릿수 출력 if 문으로 이동
			goto CIPHER_3;
		}
	}
	// 십억 이상 2,147,483,647 이하 (int 형 최댓값)
	else if(money >= 1000000000 && temp <= 2147483647)
	{
		cout << money / 1000000000 << ',';
		temp = money % 1000000000;
		money = temp;
		if(temp >= 100000000)
			goto CIPHER_2;
		else if(temp >= 10000000 && temp < 100000000)
		{
			cout << '0';
			goto CIPHER_2;
		}
		else if(temp < 10000000)
		{
			cout << "00";
			goto CIPHER_2;
		}
	}
}

int main()
{
	int_Money_State(1);			// 일
	cout << endl;
	int_Money_State(10);		// 십
	cout << endl;
	int_Money_State(100);		// 백
	cout << endl;
	int_Money_State(1000);		// 천
	cout << endl;
	int_Money_State(10000);		// 만
	cout << endl;
	int_Money_State(100000);	// 십만
	cout << endl;
	int_Money_State(1000000);	// 백만
	cout << endl;
	int_Money_State(10000000);	// 천만
	cout << endl;
	int_Money_State(100000000);	// 일억
	cout << endl;
	int_Money_State(1000000000);	// 십억
	cout << endl;
	
	return 0;
}