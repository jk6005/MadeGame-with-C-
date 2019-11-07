#include <iostream>
using namespace std;

void Input_num(int &num);	//값을 입력하는 함수
void Show_menu(int num);	//메뉴를 보여주는 함수
void Change_2(int num);		//2진수로 변환하는 함수
void Change_16(int num);	//16진수로 변환하는 함수

int main()	//메인함수
{
	int num;
	int choice;
	Input_num(num);
	while(1)
	{
		Back:
		Show_menu(num);
		cin >> choice;
		if(choice > 4)
		{
			cout << "----------------------" << endl;
			cout << "잘못된값입니다." << endl;
			cout << "----------------------" << endl;
			goto Back;
		}
		cout << endl;
		switch(choice)
		{
			case 1: Change_2(num);
				break;
			case 2: Change_16(num);
				break;
			case 3: Input_num(num);
				break;
			case 4: goto END;
		}
	}
	END:
	cout << endl;
	cout << "----------------------" << endl;
	cout << "Program END" << endl;
	cout << "----------------------" << endl;
	return 0;
}

void Input_num(int &num)
{
	back:
	cout << "----------------------" << endl;
	cout << "10진수 입력 : ";
	cin >> num;
	if(num < 0)
	{
		cout << "0 이상값을 입력하세요" << endl;
		goto back;
	}
	cout << "----------------------" << endl;
	cout << "입력완료" << endl;
	cout << "----------------------" << endl;
}

void Show_menu(int num)
{
	cout << "----------------------" << endl;
	cout << "10진수 : " << dec << num << endl;
	cout << "----------------------" << endl;
	cout << "1.  2진수로 변환 " << endl;
	cout << "2. 16진수로 변환 " << endl;
	cout << "3. 10진수값 변경 " << endl;
	cout << "4. 프로그램 종료" << endl;
	cout << "----------------------" << endl;
	cout << "입력 : ";
}

void Change_2(int num)
{
	int temp[50];
	int i, beat = 0;
	
	cout << "----------------------" << endl;
	cout << "10진수 : " << num << endl;
	cout << "2진수  : ";
	for(i = 0; num > 0; i++)
	{
		temp[i] = num % 2;
		num = num / 2;
	}
	switch(i % 4)
	{
		case 1: 
			for(int b = 0; b < 3; b++)
				cout << "0";
			beat = 3;
			break;
		case 2:
			for(int b = 0; b < 2; b++)
				cout << "0";
			beat = 2;
			break;
		case 3:
			for(int b = 0; b < 1; b++)
				cout << "0";
			beat = 1;
			break;
	}
	for(int j = 1; j <= i; j++)
	{
		cout << temp[i - j];
		beat++;
		if(beat == 4)
		{
			cout << ' ';
			beat = 0;
		}
	}
	cout << endl;
	cout << "----------------------" << endl;
}

void Change_16(int num)
{
	cout << "----------------------" << endl;
	cout << "10진수 : " << num << endl;
	cout << "16진수 : " << hex << uppercase << num << endl;
	cout << "----------------------" << endl;
	
}