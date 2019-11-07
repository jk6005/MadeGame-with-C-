#include <iostream>
using namespace std;

int main()
{
	/*
	for문 : 반복문의 한 종류이다.
	형태 : for(초기값; 조건식; 증감값) {} 의 형태로 구성이 된다.
	조건식이 true 이면 코드블럭의 코드가 동작된다.
	무한루프를 돌릴떄는 for(;;) {} 을 해주면 무한으로 돌아가게된다.
	for문에서 초기값은 처음 for문에 진입할떄 딱 1번만 동작된다. 그후에 조건식을 체크하면 조건식이 true이면
	코드블럭의 코드가 동작된 후에 증감값을 처리한다.
	그후 다시 조건을 체크하고 true면 동작되고 증감 -> 조건 -> 증감 -> 조건의 순서로 처리가 되다
	조간이 flase이거나 break를 만나게 되면 for문을 빠저나가게 된다.
	*/
	for(int i = 1; i <= 100; i++)
		if(i % 3 == 0 && i % 7 == 0)cout << i << ' ';
	cout << endl;	
	
	
	long long int p = 1;

	while(1)
	{
		if(((p * 2) / 1000) % 10 == 7)
		{
			cout << "2의 제곱수중 일의 자리가 7인 가장 작은수 : " << p * 2 << endl;
			break;
		}
		p *= 2;
	}
	/*
	        *
		   ***
		  *****
		 *******
		 *******
		  *****
		   ***
		    *
	*/
	int iHigh;
	int iStar_Number = 0;
	cout << "별의 높이 : ";
	cin >> iHigh;
	int iHigh_temp = iHigh;
	
	for(int i = 0 ; i < iHigh ; i++ )
	{
		for(int j = 0; j < iHigh_temp - 1; j++)
			cout << " ";
		cout << '*';
		for(int j = 0; j < iStar_Number; j++)
			cout << '*';
		cout << endl;
		iHigh_temp--;
		iStar_Number += 2;
	}
	
	iHigh_temp = 0;
	iStar_Number -= 2;
	for(int i = 0; i < iHigh; i++)
	{
		for(int j = 0; j < iHigh_temp; j++)
			cout << " ";
		cout << '*';
		for(int j = 0; j < iStar_Number; j++)
			cout << '*';
		cout << endl;
		iHigh_temp++;
		iStar_Number -= 2;
	}
	
	
	/*
	for(int i = 0; i < iHigh; ++i)
	{
		for(int j = 0; j < iHigh - 1 - i; j++)
			cout << " ";
		for(int j = 0; j < 1 + (i * 2); j++)
			cout << "*";
		cout << endl;
	}

	for(int i = 0; i < 3; i++)
	{
		for(int j = 1; j < 10; j++)
		{
			for(int t = 2 + (i * 3); t < 5 + (i * 3); t++)
			{
				cout << t << " * " << j << " = " << t * j <<"	";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	*/
	
	/*
	do while 문 : 반복문의 한 종류이다.
	형태 : do {}while(조건식); 의 형태로 구성된다.
	while문은 처음 진입부터 조건식을 체크하지만 do while은 처음 한번은 무조건 동작이 되고
	그 후에 조건식을 체크해서 true 일 경우 동작되는 반복문이다.
	*/
	int iNumber = 0;
	
	do
	{
		cout << iNumber << endl;
	}while (iNumber > 0);
	return 0;
}