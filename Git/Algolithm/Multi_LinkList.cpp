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

typedef struct _tagStudent	// �л� ����ü 
{
	char cNAME[NAME_SIZE];
	int iNum;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAve;
}	STUDENT, *PSTUDENT;

typedef struct _tagNode	// �л� ����ü ��� ����ü 
{
	STUDENT Student;
	_tagNode * pNext;
	_tagNode * pPre;
}	NODE, *PNODE;

typedef struct _tagList	// �л���� ����Ʈ ����ü 
{
	PNODE pBegin;
	PNODE pEnd;
	int iCount;
}	LIST, *PLIST;

void SetLIST(PLIST List)	// ����Ʈ ����ü �ʱ�ȭ 
{
	List->pBegin = NULL;
	List->pEnd = NULL;
	List->iCount = 0;
}

int InitInt()	 // int ���� �Է¹޴� �Լ� 
{
	int iInit;
	cin >> iInit;
	if(cin.fail())	// �Է¿� �������� ���� ��ȯ 
	{
		cin.clear();
		cin.ignore(1000, '\n');
		return M_NONE;
	}
	if(iInit < M_NONE || iInit > M_END)	// ���� �ʰ��ϸ� ���� ��ȯ 
		return M_NONE;
	return iInit;	// �����ϸ� �޴����� ��ȯ 
}

void InitChar(char * cString)	// char �迭�� ���� �Է¹޴� �Լ� 
{
	cin.clear();
	cin.ignore(1000, '\n');
	cin.getline(cString, NAME_SIZE - 1);
}

void OutPutMain()	// ���θ޴� ��� 
{
	system("cls");
	cout << "===================�޴�===================" << endl;
	cout << "1. �л� �߰�	2. �л� ���" << endl;
	cout << "3. �л� �˻�	4. �л� ����" << endl;
	cout << "5. ����		�Է� :"; 
}

void AddStudent(PLIST List)
{
	PNODE Stu = new NODE;	// �л� ��� ����
	
	cout << "=================�л� �߰�=================" << endl;	// �л��� ���������� �Է��ϴ� �ڵ� 
	cout << "�̸� : ";
	InitChar(Stu->Student.cNAME); 
	cout << "�й� : " ;
	cin >> Stu->Student.iNum;
	cout << "���� : " ;
	cin >> Stu->Student.iKor;
	cout << "���� : " ;
	cin >> Stu->Student.iEng;
	cout << "���� : " ;
	cin >> Stu->Student.iMath;
	
	Stu->Student.iTotal = Stu->Student.iKor + Stu->Student.iEng + Stu->Student.iMath;
	Stu->Student.fAve = Stu->Student.iTotal / 3.0f;
	
	Stu->pNext = NULL;
	Stu->pPre = NULL;	// ������ ��嵵 �ʱ�ȭ 
	
	if(List->pBegin == NULL)	// ���� ��尡 NULL �̸� Begin ��常 �߰� 
		List->pBegin = Stu;
	else	// Begin ��尡 ������ Next ��忡 ����带 �߰��ϰ� �߰��� ����� Pre ���� End ��� �� �ּҸ� �߰��Ѵ�. 
	{
		List->pEnd->pNext = Stu;
		Stu->pPre = List->pEnd;
	}
	List->pEnd = Stu;	// �Է��� ������ ������ ��带 �������ش�. 
}

void PrintStudent(const PSTUDENT Stu)	// �л������� ����ϴ� �Լ� 
{
	cout << "======================================" << endl;
	cout << "�̸� : " << Stu->cNAME << "\t�й� : " << Stu->iNum << endl;
	cout << "���� : " << Stu->iKor << endl;
	cout << "���� : " << Stu->iEng << endl;
	cout << "���� : " << Stu->iMath << endl;
	cout << "���� : " << Stu->iTotal << "\t��� : " << Stu->fAve << endl; 
}

bool PrintStudent(PLIST List)	// �л������� ���� �ϴ� �Լ� 
{
	PNODE Node = List->pBegin;
	
	if(Node == NULL)return false;	// ���� �߰��� �л��� ������ ���й�ȯ 
	while(Node != NULL)	// ��尪�� NULL ����üũ 
	{
		PrintStudent(&Node->Student);	// ��尪�� �л�����ü�� �����ϸ� ��� 
		Node = Node->pNext;	// ���� ���� ��带 ����Ų��. 
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
			Node = List->pBegin;	// Node �� pBegin �� ���� �����Ѵ� 
			List->pBegin = Node->pNext;	// pBegin �� ���� ��带 ����Ű�� �Ѵ� 
			if(Node->pPre != NULL)	// Node �� ���� ����ϴ� �ּҰ��� ������ �����Ѵ� 
			Node->pPre = NULL;
			delete Node;		// Node ���� 
		}while(List->pBegin != NULL);	// ���� ��尪�� ���� Begin �� NULL �̾ƴϸ� �ݺ��Ѵ�. 
	}
	List->pBegin = NULL;
	List->pEnd = NULL;
}

void SearchStudent(PLIST List)
{
	bool bCount = false;
	char cName[NAME_SIZE];
	cout << "=================�л� �˻�=================" << endl;
	cout << "�л��� �̸� : ";
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
		cout << "�� �л��� �������� �ʽ��ϴ�." << endl; 
	system("pause");
}

bool DeleteSutdent(PLIST List)	// �л��� �����ϴ� �Լ� 
{
	PNODE Node = List->pBegin;
	cout << "=================�л� ����=================" << endl;
	cout << "������ �л��̸� : ";
	char cName[NAME_SIZE];
	InitChar(cName);
	while(Node != NULL)	// ���� ��尡 NULL �� �ƴϿ����� 
	{
		if(strcmp(Node->Student.cNAME, cName) == 0)
		{
			if(Node->pPre == NULL)	// Begin ����ϰ�� 
			{
				if(Node->pNext == NULL)	// ������尡 ������� 
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
				if(Node->pNext == NULL)	// ������ ����ϰ�� 
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
	cout << "�� �л��� �������� �ʽ��ϴ�" << endl;
	system("pause");
	return false;
}

int main()	// �����Լ� 
{
	system("mode con cols=50 lines=40");
	LIST List;
	SetLIST(&List);	// ����Ʈ �ʱ�ȭ
	
	while(true)
	{
		OutPutMain(); // �޴���� 
		int iInit = InitInt();	// �޴��� �Է� 
		
		if(iInit == M_END)break;	// ���ᰪ ������ ���� 
		switch(iInit)
		{
			case M_NONE:	// ���� 
				continue;
			case M_INIT:
				AddStudent(&List);	// �л��߰� 
				break;
			case M_PRINT:
				if(PrintStudent(&List) == false)	// �л� ���� ���� 
				{
					cout << "�� ��ϵ� �л��� �����ϴ�" << endl;
					system("pause");
				}
				break;
			case M_SEARCH:	// �л� �˻� 
				SearchStudent(&List);
				break;
			case M_DELETE:	// �л� ���� 
				if(DeleteSutdent(&List) == true)
				{
					cout << "�� �����Ǿ����ϴ�." << endl;
					system("pause");
				}
				break;
		}
	}
	EndProgram(&List);	// ���α׸��� ���� 
	cout << endl << "�� ���α׷��� ����Ǿ����ϴ�!" << endl;
	return 0;
}
