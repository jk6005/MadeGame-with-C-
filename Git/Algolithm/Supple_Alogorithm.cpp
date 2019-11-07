#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define MAX_Arr	45
#define MAX_Supple 100

int main()
{
	// Shuffle 알고리즘 (섞는 알고리즘)
	// 1 ~ 45 까지의 숫자를 순서대로 저장할 배열을 생성
	int iArr[MAX_Arr] = {};
	for(int i = 0; i < MAX_Arr; i++)
		iArr[i] = i + 1;
	
	// srand 함수 time 으로 초기화
	srand((unsigned int)time(0));
	
	// 서로 바꾸기 위한 변수 2개와 Temp 변수하나
	int iDex1, iDex2, iTemp;
	
	// 100 번 셔플해주는 알고르짐
	for(int i = 0 ; i < MAX_Supple; i++)
	{
		// iDex1,2 값에 45 이하의 랜덤값 부여
		iDex1 = rand() % MAX_Arr;
		iDex2 = rand() % MAX_Arr;
		
		// 서로 바꿔준다
		iTemp = iArr[iDex1];
		iArr[iDex1] = iArr[iDex2];
		iArr[iDex2] = iTemp;
	}
	
	for(int i = 0 ; i < MAX_Arr; i++)
		cout << iArr[i] << ", ";
	
	return 0;
}