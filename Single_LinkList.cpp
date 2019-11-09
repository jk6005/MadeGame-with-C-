#include <iostream>
#include <cstring>

using namespace std;

#define NAME_SIZE	30

enum OutputMain_S
{
	M_NONE,
	M_INIT,
	M_PRINT,
	M_SEARCH,
	M_DELETE,
	M_END
};

typedef struct _tagSTUDENT
{
	char cStudent_Name[NAME_SIZE];
	int iNum;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAve;
} STUDENT , *PSTUDENTS;

typedef struct _tagNODE
{
	STUDENT Student;
	_tagNODE* pNEXT;
}	NODE, *PNODE;

typedef struct _tagLIST
{
	PNODE pBegin;
	PNODE pEnd;
	int iNum;
} LIST, *PLIST;

void InputLIST(PLIST Students)
{
	Students->pBegin = NULL;
	Students->pEnd = NULL;
	Students->iNum = 0;
}

int InputInt()
{
	int iInput;
	cin >> iInput;
	
	if(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		return M_NONE;
	}
	if(iInput < M_NONE || iInput > M_END)
		return M_NONE;
	
	return iInput;
}

void InputChar(char * Student)
{
	cin.clear();
	cin.ignore(1000, '\n');
	
	cin.getline(Student, NAME_SIZE  - 1);
} 

void OutputMain()
{
	system("cls");
	cout << "1. 학생 입력" << endl;
	cout << "2. 학생 출력" << endl;
	cout << "3. 학생 검색" << endl;
	cout << "4. 학생 삭제" << endl;
	cout << "5. 종료" << endl;
	cout << "=====================" << endl; 
	cout << "입력 : ";
}

void InputStudent(PLIST LIST)
{
	system("cls");
	STUDENT Student;
	
	char cNAME[NAME_SIZE];
	cout << "=========================학생 추가=========================" << endl;
	cout << "학생이름 입력 : ";
	InputChar(cNAME);
	strcpy(Student.cStudent_Name, cNAME);
	
	cout << "학번 : ";
	cin >> Student.iNum;
	cout << "국어 : ";
	cin >> Student.iKor;
	cout << "영어 : ";
	cin >> Student.iEng;
	cout << "수학 : ";
	cin >> Student.iMath;
	Student.iTotal = Student.iKor + Student.iEng + Student.iMath;
	Student.fAve = Student.iTotal / 3.0f;
	
	PNODE NODE_T = new NODE;
	NODE_T->Student = Student;
	NODE_T->pNEXT = NULL;
	
	if(LIST->pBegin == NULL)
		LIST->pBegin = NODE_T;
	
	else
		LIST->pEnd->pNEXT = NODE_T;
		
	LIST->pEnd = NODE_T;
	LIST->iNum++;
}

void OutPrintSudent(const PSTUDENTS Student)
{
	cout << "학생 이름 : " << Student->cStudent_Name << endl;
	cout << "학번 : " << Student->iNum << endl;
	cout << "국어 : " << Student->iKor << endl;
	cout << "영어 : " << Student->iEng << endl;
	cout << "수학 : " << Student->iMath << endl;
	cout << "총점 : " << Student->iTotal << endl;
	cout << "평균 : " << Student->fAve << endl << endl;
}

bool PrintStudent(PLIST LIST)
{
	system("cls");
	PNODE NODE_T = LIST->pBegin;
	if(NODE_T == NULL)
	{
		cout << "학생이 없습니다." << endl;
		system("pause");
		return false;
	}
	cout << "=========================학생 출력=========================" << endl;
	while(NODE_T != NULL)
	{
		OutPrintSudent(&NODE_T->Student);	
		NODE_T = NODE_T->pNEXT;
	}
	system("pause");
	return true;
}

bool SearchStudent(const PLIST List)
{
	system("cls");
	
	PNODE NODE_T = List->pBegin;
	
	char cName[NAME_SIZE] ;
	cout << "=========================학생 검색=========================" << endl;
	cout << "학생 이름을 입력하시오 : ";
	InputChar(cName);
	
	bool bCount = false;

	while(NODE_T != NULL)
	{
		if(strcmp(cName, NODE_T->Student.cStudent_Name) == 0)
		{
			OutPrintSudent(&NODE_T->Student);
			bCount = true;
		}
		NODE_T = NODE_T->pNEXT;
	}
	if(bCount == false)cout << "학생이 존재하지 않습니다" << endl; 
	system("pause");
	return true;
}

void EndProgram(PLIST List) 
{	
	if(List->pBegin !=NULL)
	{
		PNODE NODE_T = List->pBegin->pNEXT;
		while(List->pBegin != NULL)
		{
			NODE_T = List->pBegin->pNEXT;
			delete List->pBegin;
			List->pBegin = NODE_T;
		}		
	}

	List->pBegin = NULL;
	List->pEnd = NULL;
}

bool DeleteStudent(PLIST List)
{
	system("cls");
	cout << "=========================학생 삭제=========================" << endl;
	cout << "삭제할 이름을 입력하세요 : ";
	char cName[NAME_SIZE];
	InputChar(cName);
	
	PNODE NODE_T = List->pBegin;	// 현재노드 
	PNODE NODE_P = NULL;	// 이전노드 
	while(NODE_T != NULL)
	{
		if(strcmp(cName, NODE_T->Student.cStudent_Name) == 0)
		{
			PNODE NODE_N = NODE_T->pNEXT;
			if(NODE_P == NULL)
			{
				delete NODE_T;
				List->pBegin = NODE_N;
				return true;
			}
			else
			{
				if(NODE_T == NULL)
				{
					delete NODE_T;
					NODE_P = NODE_N;
					List->pEnd = NODE_P;
					return true;
				}
				delete NODE_T;
				NODE_P->pNEXT = NODE_N;
				return true;
			}
		}
		NODE_P = NODE_T;
		NODE_T = NODE_T->pNEXT;
	}
	cout << "학생이 존재하지 않습니다" << endl;
	system("pause");
	return true;
}

int main()
{
	LIST Students;
	InputLIST(&Students);
	
	while(true)
	{
		OutputMain();
		int iInput = InputInt();
	
		switch(iInput)
		{
			case M_NONE:
				break;
			case M_INIT:
				InputStudent(&Students);
				break;
			case M_PRINT:
				PrintStudent(&Students);
				break;
			case M_SEARCH:
				SearchStudent(&Students);
				break;
			case M_DELETE:
				DeleteStudent(&Students);
				break;
			case M_END:
				EndProgram(&Students);
				cout << "정상종료됨" << endl;
				return 0;
		}
	}
	
	return 0;
}
