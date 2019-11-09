#include <iostream>
#include <typeinfo>		//typeid 쓸려면 이헤더 참조해야함
#include <cstdlib>		//srand, rand 함수 쓸려면 이헤더 참조해야함
#include <ctime>		//time 함수 쓸려면 참조해야함
using namespace std;

/*
열거체 : 연속된 숫자에 이름을 부여할수 있는 기능이다.
enum 열거체명 {} 의 형태로 구성된다.
열거체명을 이용해서 열거체 타입의 변수를 선언도 가능하다.
즉, 열거체 자체가 사용자정의 변수 탑이 될 수도 있다.
열거체는 숫자에 이름을 붙여주는 기능이다.
*/
enum NUM
{
	NUM_0 = 1,		// 아무것도 부여하지 않을 경우 0부터 1씩 차례로 값이 부여된다.
	NUM_1,
	NUM_2 = 0x0010,		//값은 자동으로 하나씩 커지지만 중간에 임의값 입력가능 입력하면 그값부터 1 씩증가
	NUM_3
};

enum SRP
{
	SRP_S = 1,
	SRP_R,
	SRP_P,
	SRP_END
};

#define  NUM_4	4

int main()
{
	/*
	switch 문 : 분기문의 한 종류이다. if문이 조건을 체크하는 분기문이라면
	switch문은 값이 뭔지를 체크하는 분기문이다.
	형태 : switch(변수) {} 의 형태로 구성된다. 코드블럭 안에는 case break 구문이
	들어가게 된다. case 상수: 의형태로 처리가 되고 변수값이 무엇인지에 따라서
	case 뒤에오는 상수를 비교하게 된다.
	*/
	int iNumber = 1;
	cout << "숫자를 입력하세요 : ";
	//cin >> iNumber;
	
	switch(iNumber)
	{
		case NUM_0: cout << "이숫자는 1입니다." << endl;
			break;
		case NUM_1: cout << "이숫자는 2입니다." << endl;
			break;
		//switch 에서 if 문의 else 는 default 로 대체된다.
		default: 
			//cin.fail() 은 cin 값에 타입에 맞지않은 값이 오면 1을 반환한다.
			//cin.clear() 은 잘못된 값떄문에 고장난 cin 을 고처준다
			//cin.ignore(1000, '\n') 은 cin 입력버퍼를 비워주는데 가로안은 \n이 나올떄까지 1000칸 지우겟다는 것이다.
			if(cin.fail())
			{
				cout << "숫자만 입력하세요" << endl;
				cin.clear();
				cin.ignore(1000, '\n');
				break;
			}
			cout << "이숫자는 1과 2외의 수입니다." << endl;
			break;
	}
	//열거체 타입의 변수를 선언했다. 열거체타입변수는 무조건 4byte를 차지하게된다.
	// 열게체를 이용해서 선언한 ㅂㄴㄴ수는 값의 푷ㄴ 범위가 열거체에 나열된
	// 값을 안에서 선택해서 사용한다.
	NUM	eNum;
	
	//sizeof(타입 or 변수)를 하게되면 해당 타입 혹은 변수의 메모리 크기르 ㄹ구해준다.
	cout << sizeof(NUM) << endl;
	// typeid(타입 or 변수).name() 을 하게되면 typeid 안에 들어간 타입 혹은
	// 변수의 타입을 문자열로 반환해준다.
	cout << typeid(eNum).name() << endl;
	
	/*
	반복문 : 특정 작업을 반복해서 수행해주는 기능이다.
	종류 : for, while, do while 3종류가 존재한다.
	while(조건식) {} 의 형태로 구성된다.
	while문은 조건식을 체크해서 true 일경우 코드블럭 안의 코드가 동작되고 다시 조ㅓㄴ식을 체크한다. 
	조건식이 false가 되면 while문을 빠저나온게 된다.
	반복문 안에서 break를 만나게되며 해당 반복문을 빠저나오게 된다.
	*/

	//화면을 꺠끗히 지워준다.
	// system("cls"); //구름 IDE 라서 잠시막아놈
	
	// 난수테이블 생성
	srand((unsigned int)time(0));
	
	int iPlayer, iAi;
	
	while(1)
	{
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3. 보" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		cin >> iPlayer;
		
		if(iPlayer < SRP_S || iPlayer > SRP_END)
		{
			cout << "잘못된 값을 입력하였습니다." << endl;
			// 일시정지
			//system("pause");
			continue;
		}
		
		else if(iPlayer == SRP_END)
			break;
		
		// 봇이 선택을 한다.
		iAi = rand() % 3 + SRP_S;
		cout << endl;
		
		switch(iAi)
		{
			case SRP_S:
				cout << "AI : 가위" << endl;
				break;
			case SRP_R:
				cout << "AI : 바위" << endl;
				break;
			case SRP_P:
				cout << "AI : 보" << endl;
				break;
		}
		
		int iWin = iPlayer -iAi;
		
		if(iWin == 1 || iWin == -2)
			cout << "Player 승리" << endl;
		else if(iWin == 0)
			cout << "비김" << endl;
		else
			cout << "AI 승리" << endl;
		cout << endl;
		//system("pause");
	}

		return 0;
}
	