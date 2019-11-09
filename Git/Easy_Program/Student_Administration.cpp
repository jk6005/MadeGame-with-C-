#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cstring>

#define MAX_STUDENT 100
#define LIST_NUM 5

using namespace std;

static int Student_Count = 0;

enum Choice{ Add = 1, Del, Search, Print, EXIT };
enum Grade_Type{ MATH = 1, KOR, ENG, SCI };
enum Switch{ TURN = 1, OFF};

// 입력값이 fail 이 뜨는지 검사하는 함수 
int Return_cin(int iTemp, int iType)
{
	if(iType == 1)
	{
		if(cin.fail() || iTemp < 0 || iTemp > 100)
		{
			cout << "옳지 않은 입력입니다.(0 ~ 100 사이의 숫자입력)" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			return false;
		}
		return true;	
	}
	if(iType == 2)
	{
		if(cin.fail() || iTemp < 0 || iTemp > 2)
			return false;
		return true;	
	} 
}

// 메뉴화면 출력 
void Menu()
{
	cout << "　　　　  < 메뉴 >　　　　" << endl;
	cout << "1. 학생 추가　　2. 학생 삭제　" << endl;
	cout << "3. 학생 탐색　　4. 학생 출력　" << endl;
	cout << "　　　　　5. 종료" << endl;
}

// 학생들의 정보를 저장하는 클래스 
class clsStudents
{
	private:
	string sName;
	int iNumber; 
	int iMath;
	int iKor;
	int iEng;
	int iSci;
	int iTotal;
	float fAve;
	bool bUse;
	
	public:
	clsStudents() {}
	~clsStudents() {}
	
	// 다른 학생정보를 대입해주는 함수 
	void Swap_Information(clsStudents* ref)
	{
		sName = ref->sName;
		iMath = ref->iMath;
		iKor = ref->iKor;
		iEng = ref->iEng;
		iSci = ref->iSci;
		iTotal = ref->iTotal;
		fAve = ref->fAve;
		bUse = ref->bUse; 
	}
	
	// 입력유무 값을 정해주는 함수
	bool Turn_or_Off(int type)
	{
		if(type == TURN)
			bUse = true;
		else 
			bUse = false;
	} 
	
	bool Return_Use()
	{
		return bUse;
	}
	
	// 학생 정보를 출력해주는 함수
	void Print_Information()
	{
		cout << "Student_NUM." << iNumber << endl; 
		cout << "이름 : " << sName << endl;
		cout << "수학 : " << iMath << endl;
		cout << "국어 : " << iKor << endl;
		cout << "영어 : " << iEng << endl;
		cout << "과학 : " << iSci << endl;
		cout << "평균 : " << fAve << endl;
	} 
	
	// 순서를 넣어주는 함수
	int Add_Number(int number)
	{
		iNumber = number;
	} 
	// 순서를 반환하는 함수
	int Return_Number()
	{
		return iNumber;
	} 
	
	// 이름을 넣는 함수 
	void Input_Name(string name) {sName = name;}
	
	// 이름을 반환하는 함수 
	string return_name()
	{
		return sName;
	}
	
	// 성적을 입력하는 함수
	int Add_Grade(int grade, int type)
	{
		switch(type)
		{
			case MATH:
				iMath = grade;
				break;
			case KOR:
				iKor = grade;
				break;
			case ENG:
				iEng = grade;
				break;
			case SCI:
				iSci = grade;
				break;
		}
	}
	
	// 성적을 반환하는 함수 
	int return_Grade(int type)
	{
		switch(type)
		{
			case MATH:
				return iMath;
			case KOR:
				return iKor;
			case ENG:
				return iEng;
			case SCI:
				return iSci;
		}
	}
	
	// 평균을 반환하는 함수
	float return_Ave()
	{
		return fAve;
	} 
	
	// 성적의 합계와 평균을 입력하는 함수 
	void Add_Total_Ave()
	{
		iTotal = iMath + iKor + iEng + iSci;
		fAve = iTotal / 4.0f;
	}
};

// 학생들의 저장된 정보를 이용하는 클래스 
class clsStudents_Handle
{
	//private: 
	public:
	clsStudents *Handle[MAX_STUDENT];	
	
	public:
	// 선언과 동시에 순서를 넣어준다. 
	// 동시에 사용여부또한 넣어준다. 
	clsStudents_Handle()
	{
		for(int i = 0; i < MAX_STUDENT; i++)
		{
			Handle[i] = new clsStudents;
			Handle[i]->Add_Number(i + 1);
			Handle[i]->Turn_or_Off(OFF);
		}
	}
	~clsStudents_Handle()
	{
		for(int i = 0; i < MAX_STUDENT; i++)
		{
			delete Handle[i];
		}
	}
	
	// 학생을 추가하는 함수 
	bool Add_Student()
	{
		string cName;
		int iTemp; 
		system("cls");
		cout << Handle[Student_Count]->Return_Number() << "번쨰 학생 추가" << endl;
		cout << "이름 : ";
		getline(cin, cName);
		Handle[Student_Count]->Input_Name(cName);
		while(true)
		{
			cout << "수학 : ";
			cin >> iTemp;
			if(Return_cin(iTemp, 1) == true)
				break;
		}
		Handle[Student_Count]->Add_Grade(iTemp, MATH);
		while(true)
		{
			cout << "국어 : ";
			cin >> iTemp;
			if(Return_cin(iTemp, 1) == true)
				break;
		}
		Handle[Student_Count]->Add_Grade(iTemp, KOR);
		while(true)
		{
			cout << "영어 : ";
			cin >> iTemp;
			if(Return_cin(iTemp, 1) == true)
				break;
		}
		Handle[Student_Count]->Add_Grade(iTemp, ENG);
		while(true)
		{
			cout << "과학 : ";
			cin >> iTemp;
			if(Return_cin(iTemp, 1) == true)
				break;
		}
		Handle[Student_Count]->Add_Grade(iTemp, SCI);
		
		// 정보출력 및 확인 유무 
		system("cls");
		Handle[Student_Count]->Add_Total_Ave();
		cout << "Student NUM." << Handle[Student_Count]->Return_Number() << endl;
		cout << "──────────────" << endl; 
		Handle[Student_Count]->Print_Information();
		cout << endl <<"생성을 완료하시겠습니까?" << endl;
		cout << "　1.예　　2.아니오" << endl; 
		int inum;
		while(true)
		{
			inum = getch();
			inum -= '0';
			switch(inum)
			{
				case 1:
					cout << "※ 학생 을 추가하셨습니다! ※" << endl;
					Handle[Student_Count]->Turn_or_Off(TURN);
					getch();
					return true;
				case 2:
					cout << "※ 입력을 취소하였습니다! ※" << endl;
					getch();
					return false;
				default:
					continue;
			}
		}
		
				
	}
	
	bool Delete_Stucent()
	{
		int iChoice;
		int iChoice2;
		int iList = 0;
		int iList_Start = 0; 
		int iNext_Count = 1; 
		int iCount;
		POS1:
		// 추가된 학생이 없으면 false 반환 
		if(Student_Count < 1)
		{
			cout << "※ 추가된 학생이 없습니다! ※" << endl;
			getch();
			return false;
		}
		// 학생 목록 출력 1 ~ 5 
		while(true)
		{
			iCount = 1;
			system("cls");
			cout << "──────────" << endl;
			cout << "　　　<목록>　　　" << endl;
			cout << "──────────" << endl;
			for(int i = iList_Start; i < LIST_NUM * iList + LIST_NUM; i++)
			{
				if(Handle[i]->Return_Use() != false)
				{
					cout << iCount << ". " << Handle[i]->return_name() << endl;
					iCount++;
					if(iCount == 6)iCount = 1;
				}
				else 
				{
					cout << iCount << ". -없음-" << endl;
					iCount++;
					if(iCount == 6)iCount = 1;
				}
			}
			cout << "　　　" << iNext_Count << "PAGE　　　　" << endl; 
			cout << "──────────" << endl;
			cout << "뒤로 : 6　 앞으로 : 7" << endl;
			cout << "그만두기 : 0" << endl;
			iChoice = getch();
			iChoice -= '0';
			switch(iChoice)
			{
				case 0:
					cout << "※ 메뉴로 돌아갑니다. ※" << endl; 
					getch();
					return false; 
				case 1:
					cout << "──────────" << endl;
					Handle[LIST_NUM * iList + 0]->Print_Information();
					cout << "──────────" << endl;
					cout << "삭제하시겠습니까?" << endl;
					cout << "1. 예　　2. 아니오" << endl;
					iChoice2 = getch(); iChoice2 -= '0';
					if(Return_cin(iChoice2, 2) != true)continue;
					if(iChoice2 == 1)
					{
						for(int i = LIST_NUM * iList + 0; i < MAX_STUDENT - 1; i++)
							Handle[i]->Swap_Information(Handle[i + 1]);
						return true;	
					}
					else if(iChoice2 == 2)
					{
						cout << "※ 입력을 취소했습니다. ※" << endl;
						goto POS1; 
					}
				case 2:
					if(Handle[LIST_NUM * iList + 1]->Return_Use() == false)
						continue;
					else
					{
						cout << "──────────" << endl;
						Handle[LIST_NUM * iList + 1]->Print_Information();
						cout << "──────────" << endl;
						cout << "삭제하시겠습니까?" << endl;
						cout << "1. 예　　2. 아니오" << endl;
						iChoice2 = getch(); iChoice2 -= '0';
						if(Return_cin(iChoice2, 2) != true)continue;
						if(iChoice2 == 1)
						{
							for(int i = LIST_NUM * iList + 1; i < MAX_STUDENT - 1; i++)
								Handle[i]->Swap_Information(Handle[i + 1]);
							return true;	
						}
						else if(iChoice2 == 2)
						{
							cout << "※ 입력을 취소했습니다. ※" << endl;
							goto POS1; 
						}
					}
				case 3:
					if(Handle[LIST_NUM * iList + 2]->Return_Use() == false)
						continue;
					else
					{
						cout << "──────────" << endl;
						Handle[LIST_NUM * iList + 2]->Print_Information();
						cout << "──────────" << endl;
						cout << "삭제하시겠습니까?" << endl;
						cout << "1. 예　　2. 아니오" << endl;
						iChoice2 = getch(); iChoice2 -= '0';
						if(Return_cin(iChoice2, 2) != true)continue;
						if(iChoice2 == 1)
							{
								for(int i = LIST_NUM * iList + 2; i < MAX_STUDENT - 1; i++)
									Handle[i]->Swap_Information(Handle[i + 1]);
								return true;	
							}
						else if(iChoice2 == 2)
						{
							cout << "※ 입력을 취소했습니다. ※" << endl;
							goto POS1; 
						}
					}
				case 4:
					if(Handle[LIST_NUM * iList + 3]->Return_Use() == false)
						continue;
					else
					{
						cout << "──────────" << endl;
						Handle[LIST_NUM * iList + 3]->Print_Information();
						cout << "──────────" << endl;
						cout << "삭제하시겠습니까?" << endl;
						cout << "1. 예　　2. 아니오" << endl;
						iChoice2 = getch(); iChoice2 -= '0';
						if(Return_cin(iChoice2, 2) != true)continue;
						if(iChoice2 == 1)
						{
							for(int i = LIST_NUM * iList + 3; i < MAX_STUDENT - 1; i++)
								Handle[i]->Swap_Information(Handle[i + 1]);
							return true;	
						}
						else if(iChoice2 == 2)
						{
							cout << "※ 입력을 취소했습니다. ※" << endl;
							goto POS1; 
						}
					}
				case 5:
					if(Handle[LIST_NUM * iList + 4]->Return_Use() == false)
						continue;
					else
					{
						cout << "──────────" << endl;
						Handle[LIST_NUM * iList + 4]->Print_Information();
						cout << "──────────" << endl;
						cout << "삭제하시겠습니까?" << endl;
						cout << "1. 예　　2. 아니오" << endl;
						iChoice2 = getch(); iChoice2 -= '0';
						if(Return_cin(iChoice2, 2) != true)continue;
						if(iChoice2 == 1)
						{
							for(int i = LIST_NUM * iList + 4; i < MAX_STUDENT - 1; i++)
								Handle[i]->Swap_Information(Handle[i + 1]);
							return true;	
						}
						else if(iChoice2 == 2)
						{
							cout << "※ 입력을 취소했습니다. ※" << endl;
							goto POS1; 
						}
					}
				case 6:
					if(iNext_Count != 1)
					{
						iList--;
						iList_Start -= 5;
						iNext_Count--;
						break;
					}
					break;
				case 7:
					if(Student_Count / (LIST_NUM * iNext_Count ) != 0 && Student_Count % (LIST_NUM * iNext_Count ) != 0)
					{
						iList++;
						iList_Start += 5;
						iNext_Count++;
						break;
					}
					break;
			}
		}
		return false;
	}
	
	// 이름으로 학생을 검색하는 함수 
	bool Search_Student()
	{
		if(Student_Count == 0)
		{
			cout << "※ 저장된 학생이 없습니다 ※" << endl;
			getch();
			return false;
		}
		system("cls");
		string sNAME;
		int iFind_Count = 0;
		int iSave_Finding[MAX_STUDENT] = {};
		int iCount = 0;
		
		cout << "이름으로 학생을 검색합니다..." << endl;
		cout << "입력 : ";
		// 이름을 입력하면 모든 변수에서 해당이름과 동일한 변수를 모두 출력한다. 
		getline(cin, sNAME);
		for(int i = 0; i < MAX_STUDENT; i++)
		{
			if(sNAME == Handle[i]->return_name())
			{
				iFind_Count++;
				iSave_Finding[iCount++] = i;
			}
		}
		if(iFind_Count == 0)
		{
			cout << "일치하는 이름이 없습니다." << endl;
			getch();
			return true;
		}
		else
		{
			cout << "일치하는 이름을 " << iFind_Count << "건 발견했습니다." << endl;
			getch();
			for(int i = 0; i < iFind_Count; i++)
			{
				cout << "─────────────────────" << endl;
				Handle[iSave_Finding[i]]->Print_Information();
				cout << "─────────────────────" << endl;
			}
			getch(); 
			return true;
		}
	}
	
	// 전채학생을 출력하는수 
	bool Print_Student()
	{
		if(Student_Count == 0)
		{
			cout << "※ 저장된 학생이 없습니다 ※" << endl;
			getch();
			return false;
		}
		system("cls");
		cout << "학생 출력" << endl;
		cout << "─────────────────────" << endl;
		for(int i = 0; i < Student_Count; i++)
			{
				cout << "─────────────────────" << endl;
				Handle[i]->Print_Information();
				cout << "─────────────────────" << endl;
			}
			getch();
			return true;
		
	}
	
};

int main()
{
	clsStudents_Handle Handler;
	int iChoice;
	
	while(true)
	{
		system("cls");
		// 메뉴 출력 
		Menu();
		iChoice = getch();
		iChoice -= '0';
		
		// 메뉴 선택
		switch(iChoice)
		{
			case Add:
				if(Handler.Add_Student() == true)
				{
					cin.ignore(1000, '\n'); 
					Student_Count++;	
				}
				else cin.ignore(1000, '\n'); 
				break;
			case Del:
				if(Handler.Delete_Stucent() == true)
					Student_Count--;
				break;
			case Search:
				if(Handler.Search_Student() == true)
					cin.ignore(1000, '\n'); 
				break;
			case Print:
				Handler.Print_Student();
				break;
			case EXIT:
				iChoice = INT_MAX;
				break;
			default:
				continue;
		}
		if(iChoice == INT_MAX)
			break;
		
	}
	cout << endl << "※ 종료되었습니다! ※" << endl;
	getch(); 
	
	return 0;
}