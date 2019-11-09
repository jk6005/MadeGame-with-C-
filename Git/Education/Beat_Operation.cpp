#include <iostream>
using namespace std;

int main()
{										//   2진수
	const int	iAttack = 0x00000001;	//	    1 
	const int	iArmor = 0x00000002;	//	   10
	const int	iHP = 0x00000004;		//	  100
	const int	iMP = 0x00000008;		//	 1000
	const int	iCritical = 0x00000010; //	10000
	
	//  1 | 100 = 101 | 10000 = 10101
	int iBuf = iAttack | iHP | iCritical;
	
	//연산자 축약형 : 연산자를 줄여서 사용할 수 있다.
	// 아래를 풀어서 쓰면 iBuf = iBuf ^ iHP;
	// 10101 ^ 00100 = 10001
	iBuf ^= iHP;
	
	//  10001 ^ 00100 = 10101;
	iBuf ^= iHP;
	
	// & 연산자로 키는게 가능
	// 10101 & 00001 = 00001
	cout <<	"Attack : " << (iBuf & iAttack) << endl;
	cout << "Armor : " << (iBuf & iArmor) << endl;
	cout << "HP : " << (iBuf & iHP) << endl;
	cout << "MP : " << (iBuf & iMP) << endl;
	cout << "Critical : " << (iBuf & iCritical) << endl;
	
	/*
	쉬프트 연산자 : << , >> 값 대 값을 연산하여 값으로 나오게 된다.
	이 연산자 또한 이진수 단위의 연산을 하게 된다.
	20 << 2 = 80		==  20 * 2의2승
	20 << 3 = 160		==	20 * 2의3승
	20 << 4 = 320		==	2- * 2의4승
	20을 2진수로 변환한다.
	1010000
	10100000
	101000000
	
	20 >> 2 = 5
	20 >> 3 = 2
	101
	10
	*/
	int iHigh = 197;
	int iLow = 13560;
	
	int iNumber = iHigh;
	
	//iNumber에는 187이 들어가있다. 이값을 <- 이방향으로 16비트 이동시키면
	//상위 16비트에 값이 들어가게 된다.
	// iNumber = iNumber << 16 대신
	iNumber <<= 16;
	
	// 하위 16비트를 채운다.
	iNumber |= iLow;
	
	//High Low 값을 출력한다.
	// 오른쪽으로 16비트 이동하면 입력된 값만 나온다
	cout << "High : " << (iNumber >> 16) << endl;
	// f 는 2진수로 1111 이기떄문에 입력된 값만 출력된다.
	cout << "Low : " << (iNumber & 0x0000ffff) << endl;
	
	// 증감 연산자 : ++, -- 1증가, 1감소이다.
	
	return 0;
}