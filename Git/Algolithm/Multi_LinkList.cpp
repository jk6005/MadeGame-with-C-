#include <iostream>
#include <cstring>
using namespace std;

#define NAME_SIZE 30

enum MAIN_MENU
{
	M_NONE,
	M_INIT,
	M_PRINT,
	M_SEARCH,
	M_DELETE,
	M_END
};

typedef struct _tagStudent	// 학생 구조체 
{
	char cNAME[NAME_SIZE];
	int iNum;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAve;
}	STUDENT, *PSTUDENT;

typedef struct _tagNode	// 학생 구조체 노드 구조체 
{
	STUDENT Student;
	_tagNode * pNext;
	_tagNode * pPre;
}	NODE, *PNODE;

typedef struct _tagList	// 학생노드 리스트 구조체 
{
	PNODE pBegin;
	PNODE pEnd;
	int iCount;
}	LIST, *PLIST;

void SetLIST(PLIST List)	// 리스트 구조체 초기화 
{
	List->pBegin = NULL;
	List->pEnd = NULL;
	List->iCount = 0;
}

int InitInt()	 // int 값을 입력받는 함수 
{
	int iInit;
	cin >> iInit;
	if(cin.fail())	// 입력에 오류나면 실패 반환 
	{
		cin.clear();
		cin.ignore(1000, '\n');
		return M_NONE;
	}
	if(iInit < M_NONE || iInit > M_END)	// 값을 초과하면 실패 반환 
		return M_NONE;
	return iInit;	// 성공하면 메뉴값을 반환 
}

void InitChar(char * cString)	// char 배열에 값을 입력받는 함수 
{
	cin.clear();
	cin.ignore(1000, '\n');
	cin.getline(cString, NAME_SIZE - 1);
}

void OutPutMain()	// 메인메뉴 출력 
{
	system("cls");
	cout << "===================메뉴===================" << endl;
	cout << "1. 학생 추가	2. 학생 출력" << endl;
	cout << "3. 학생 검색	4. 학생 삭제" << endl;
	cout << "5. 종료		입력 :"; 
}

void AddStudent(PLIST List)
{
	PNODE Stu = new NODE;	// 학생 노드 생성
	
	cout << "=================학생 추가=================" << endl;	// 학생을 인적사항을 입력하는 코드 
	cout << "이름 : ";
	InitChar(Stu->Student.cNAME); 
	cout << "학번 : " ;
	cin >> Stu->Student.iNum;
	cout << "국어 : " ;
	cin >> Stu->Student.iKor;
	cout << "영어 : " ;
	cin >> Stu->Student.iEng;
	cout << "수학 : " ;
	cin >> Stu->Student.iMath;
	
	Stu->Student.iTotal = Stu->Student.iKor + Stu->Student.iEng + Stu->Student.iMath;
	Stu->Student.fAve = Stu->Student.iTotal / 3.0f;
	
	Stu->pNext = NULL;
	Stu->pPre = NULL;	// 종합후 노드도 초기화 
	
	if(List->pBegin == NULL)	// 시작 노드가 NULL 이면 Begin 노드만 추가 
		List->pBegin = Stu;
	else	// Begin 노드가 있으면 Next 노드에 새노드를 추가하고 추가된 노드의 Pre 에는 End 노드 의 주소를 추가한다. 
	{
		List->pEnd->pNext = Stu;
		Stu->pPre = List->pEnd;
	}
	List->pEnd = Stu;	// 입력이 끝나면 마지막 노드를 변경해준다. 
}

void PrintStudent(const PSTUDENT Stu)	// 학생정보를 축력하는 함수 
{
	cout << "======================================" << endl;
	cout << "이름 : " << Stu->cNAME << "\t학번 : " << Stu->iNum << endl;
	cout << "국어 : " << Stu->iKor << endl;
	cout << "영어 : " << Stu->iEng << endl;
	cout << "수학 : " << Stu->iMath << endl;
	cout << "총점 : " << Stu->iTotal << "\t평균 : " << Stu->fAve << endl; 
}

bool PrintStudent(PLIST List)	// 학생정보를 나열 하는 함수 
{
	PNODE Node = List->pBegin;
	
	if(Node == NULL)return false;	// 만약 추가된 학생이 없으면 실패반환 
	while(Node != NULL)	// 노드값이 NULL 인지체크 
	{
		PrintStudent(&Node->Student);	// 노드값의 학생구조체가 존재하면 출력 
		Node = Node->pNext;	// 노드는 다음 노드를 가르킨다. 
	}
	system("pause");
	return true;
}

void EndProgram(PLIST List)	
{
	PNODE Node = List->pBegin;
	if(List->pBegin != NULL)
	{
		do 
		{
			Node = List->pBegin;	// Node 에 pBegin 의 값을 저장한다 
			List->pBegin = Node->pNext;	// pBegin 은 다음 노드를 가르키게 한다 
			if(Node->pPre != NULL)	// Node 에 전에 사용하던 주소값이 잇으면 제거한다 
			Node->pPre = NULL;
			delete Node;		// Node 제거 
		}while(List->pBegin != NULL);	// 다음 노드값을 받은 Begin 이 NULL 이아니면 반복한다. 
	}
	List->pBegin = NULL;
	List->pEnd = NULL;
}

void SearchStudent(PLIST List)
{
	bool bCount = false;
	char cName[NAME_SIZE];
	cout << "=================학생 검색=================" << endl;
	cout << "학생의 이름 : ";
	InitChar(cName);
	
	PNODE Node = List->pBegin;
	while(Node != NULL)
	{
		if(strcmp(Node->Student.cNAME, cName) == 0)
		{
			PrintStudent(&Node->Student);
			bCount = true;
		}
		Node = Node->pNext;
	}
	if(bCount == false)
		cout << "※ 학생이 존재하지 않습니다." << endl; 
	system("pause");
}

bool DeleteSutdent(PLIST List)	// 학생을 제거하는 함수 
{
	PNODE Node = List->pBegin;
	cout << "=================학생 삭제=================" << endl;
	cout << "삭제할 학생이름 : ";
	char cName[NAME_SIZE];
	InitChar(cName);
	while(Node != NULL)	// 시작 노드가 NULL 이 아니여야함 
	{
		if(strcmp(Node->Student.cNAME, cName) == 0)
		{
			if(Node->pPre == NULL)	// Begin 노드일경우 
			{
				if(Node->pNext == NULL)	// 다음노드가 없을경우 
				{
					delete Node;
					List->pBegin = NULL;
					List->pEnd = NULL;
					return true;
				}
				List->pBegin = Node->pNext;
				delete Node;
				List->pBegin->pPre = NULL;
				return true;
			}
			else
			{
				if(Node->pNext == NULL)	// 마지막 노드일경우 
				{
					PNODE p_Node = Node->pPre;
					p_Node->pNext = NULL;	
					delete Node;
					List->pEnd = p_Node;
					return true;
				}
				PNODE p_NODE = Node->pPre;
				PNODE n_NODE = Node->pNext;
				delete Node;
				p_NODE->pNext = n_NODE;
				n_NODE->pPre = p_NODE;
				return true;
			}
		}
		Node = Node->pNext;
	}
	cout << "※ 학생이 존재하지 않습니다" << endl;
	system("pause");
	return false;
}

int main()	// 메인함수 
{
	system("mode con cols=50 lines=40");
	LIST List;
	SetLIST(&List);	// 리스트 초기화
	
	while(true)
	{
		OutPutMain(); // 메뉴출력 
		int iInit = InitInt();	// 메뉴값 입력 
		
		if(iInit == M_END)break;	// 종료값 나오면 종료 
		switch(iInit)
		{
			case M_NONE:	// 실패 
				continue;
			case M_INIT:
				AddStudent(&List);	// 학생추가 
				break;
			case M_PRINT:
				if(PrintStudent(&List) == false)	// 학생 정보 나열 
				{
					cout << "※ 등록된 학생이 없습니다" << endl;
					system("pause");
				}
				break;
			case M_SEARCH:	// 학생 검색 
				SearchStudent(&List);
				break;
			case M_DELETE:	// 학생 삭제 
				if(DeleteSutdent(&List) == true)
				{
					cout << "※ 삭제되었습니다." << endl;
					system("pause");
				}
				break;
		}
	}
	EndProgram(&List);	// 프로그르램 종료 
	cout << endl << "※ 프로그램이 종료되었습니다!" << endl;
	return 0;
}
