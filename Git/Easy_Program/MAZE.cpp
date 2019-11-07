#include <iostream>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define POSITION _clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS]
#define UP _clMAZE.MAZE_Arr[_clMAZE.I_POS - 1][_clMAZE.J_POS]
#define DOWN _clMAZE.MAZE_Arr[_clMAZE.I_POS + 1][_clMAZE.J_POS]
#define LEFT _clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS - 1]
#define RIGHT _clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS + 1]

#define B_UP		_clMAZE.MAZE_Arr[i - 1 - t][j]
#define B_DOWN		_clMAZE.MAZE_Arr[i + 1 + t][j]
#define B_LEFT		_clMAZE.MAZE_Arr[i][j - 1 - t]
#define B_RIGHT		_clMAZE.MAZE_Arr[i][j + 1 + t]
#define B_POSITION	_clMAZE.MAZE_Arr[i][j]

using namespace std;

/*
0 : 벽
1 : 길
2 : 시작점
3 : 도착점 
4 : 플레이어 
5 : 폭탄 
*/

enum MOVE
{
	M_NONE,
	M_UP,
	M_DOWN,
	M_LEFT,
	M_RIGHT,
	M_INSERT,
	M_BOOM, 
	M_PUSH,
	M_END
};

enum ITEM
{
	I_NONE,
	I_POWER,
	I_GHOST,
	I_PUSH
};

class MAZE
{
	public:
		char MAZE_Arr[21][21];
		int I_POS;
		int J_POS;
		int iPower;
		bool bPush;
		bool bPush_S;
		bool bGhost;
		int iPositionType; // 0 = 벽 , 1 = 길 , 2 = 폭탄 
		
	public:
		MAZE() : iPower(1), bPush(false), bPush_S(false), bGhost(false)
		{
			strcpy(MAZE_Arr[0],		"00000000000000000000");
			strcpy(MAZE_Arr[1],		"04111110000001000000");
			strcpy(MAZE_Arr[2],		"01111111111111111110");
			strcpy(MAZE_Arr[3],		"00001110001110010000");
			strcpy(MAZE_Arr[4],		"01101111101111101100");
			strcpy(MAZE_Arr[5],		"01101000000100001100");
			strcpy(MAZE_Arr[6],		"01001011111101111110");
			strcpy(MAZE_Arr[7],		"01111000100100001000");
			strcpy(MAZE_Arr[8],		"01001000100111111000");
			strcpy(MAZE_Arr[9],		"01011000100000100000");
			strcpy(MAZE_Arr[10],	"01110000000000100000");
			strcpy(MAZE_Arr[11],	"00011111110000111000");
			strcpy(MAZE_Arr[12],	"00001000011000100000");
			strcpy(MAZE_Arr[13],	"00001111001100111100");
			strcpy(MAZE_Arr[14],	"00001001000000000100");
			strcpy(MAZE_Arr[15],	"00111101111111000100");
			strcpy(MAZE_Arr[16],	"00001000000001101100");
			strcpy(MAZE_Arr[17],	"00001000000000100000");
			strcpy(MAZE_Arr[18],	"00111011100001111130");
			strcpy(MAZE_Arr[19],	"00000000000000000000");
		}
		
		int SetItem()
		{
			int iTemp;
			iTemp = rand() % 100 + 1;
			
			if(iTemp <= 74)
				return I_NONE;
			else if(iTemp > 74 && iTemp <= 94)
				return I_POWER;
			else if(iTemp > 94 && iTemp <= 97)
				return I_GHOST;
			else return I_PUSH;
		} 
};

void OutPut_MAZE(MAZE& _clMAZE)
{
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			if(_clMAZE.MAZE_Arr[1][1] != '4')
				_clMAZE.MAZE_Arr[1][1] = '2';

			if(_clMAZE.MAZE_Arr[i][j] == '0')
				cout << "■";
				
			else if(_clMAZE.MAZE_Arr[i][j] == '1')	
				cout << "  ";
				
			else if(_clMAZE.MAZE_Arr[i][j] == '2')
				cout << "★";
			
			else if(_clMAZE.MAZE_Arr[i][j] == '3')
				cout << "◎";
			
			else if(_clMAZE.MAZE_Arr[i][j] == '4')
			{
				cout << "☆";
				_clMAZE.I_POS = i;
				_clMAZE.J_POS = j;
			}
			else if(_clMAZE.MAZE_Arr[i][j] == '5')
				cout << "♨";
			
			else if(_clMAZE.MAZE_Arr[i][j] == '6')
				cout << "㈜";		// 파워업 
				
			else if(_clMAZE.MAZE_Arr[i][j] == '7')
				cout << "♬";		// 벽통과
			
			else if(_clMAZE.MAZE_Arr[i][j] == '8') 
				cout << "◈";		// 벽밀기 
		}
		cout << endl; 
	}
	;
	cout << "벽통과 (";
	if(_clMAZE.bGhost == true)cout << "ON)";
	else cout << "OFF)"; 
	cout << " 파워 : " << _clMAZE.iPower << endl;
	cout << "f : 벽밀기 ";
	if(_clMAZE.bPush == true) cout << "(활성화)";
	else cout << "(비활성화)";
	cout << "(";
	if(_clMAZE.bPush_S == true)cout << "ON)";
	else cout << "OFF)";
	cout << endl << "t : 폭탄설치 u : 폭탄 터트리기" << endl; 
	cout << "w : 위로 , a : 왼쪽, s : 아래, d : 오른쪽";
}

int Moving_MAZE(MAZE& _clMAZE, int MOVE)
{	
	int temp = 0;
	switch(MOVE)
		{
			case M_PUSH:
				if(_clMAZE.bPush != true || _clMAZE.iPositionType == 0)return false;
				else
				{
					if(_clMAZE.bPush_S == true)
					{
						_clMAZE.bPush_S = false;
						return true;
					}
					else 
					{
						_clMAZE.bPush_S = true;
						return true;
					}
				}
			case M_UP:
				if(_clMAZE.I_POS > 1 && _clMAZE.bPush_S == true && UP == '0' && _clMAZE.MAZE_Arr[_clMAZE.I_POS - 2][_clMAZE.J_POS] == '1')	// 벽밀기 
				{
					if(_clMAZE.iPositionType == 1)
					{
						POSITION = '1';
						UP = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS - 2][_clMAZE.J_POS] = '0';
						return true;
					}
					else if(_clMAZE.iPositionType == 2)
					{
						POSITION = '5';
						UP = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS - 2][_clMAZE.J_POS] = '0';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				else if(UP != '0' && UP != '2' && UP != '5' && _clMAZE.I_POS > 0 && _clMAZE.iPositionType != 0)
				{
					if(UP == '3')	// 도착 
					{
						POSITION = '1';
						return INT_MAX - 1;
					}
					if(UP == '6')	 // 파워 습득 
					{
						_clMAZE.iPower++;
						if(POSITION != '5')POSITION = '1';
						UP = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(UP == '7')	 // 벽통과 습득 
					{
						_clMAZE.bGhost = true;
						if(POSITION != '5')POSITION = '1';
						UP = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(UP == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						UP = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					
					if(POSITION == '5')	// 폭탄설치후 
					{
						if(UP == '6')_clMAZE.iPower++;
						else if(UP == '7')_clMAZE.bGhost = true;
						UP = '4';
						_clMAZE.iPositionType = 1;
						return INT_MAX - 2;
					}
					
					if(_clMAZE.I_POS > 0)	// 정상이동 
					{
						temp = UP;
						UP = POSITION;
						POSITION = temp;
						_clMAZE.iPositionType = 1;
					}
					return true;
				}
				else if(UP == '0' && _clMAZE.bGhost == true && _clMAZE.bPush_S != true) // 벽통과 
				{
					if(_clMAZE.iPositionType == 1)
					{
						_clMAZE.iPositionType = 0;
						POSITION = '1';
						UP = '4';
						return true; 
					}
					else if(_clMAZE.iPositionType == 0)
					{
						_clMAZE.iPositionType = 0;
						temp = UP;
						UP = POSITION;
						POSITION = temp;
						return true; 
					}
					else if(_clMAZE.iPositionType == 2)
					{
						UP = '4';
						_clMAZE.iPositionType = 0;
						return INT_MAX - 2;
					}
				}
				else if(_clMAZE.iPositionType == 0 && UP != '0')
				{
					if(UP == '5')return false;
					if(UP == '3')	// 도착 
					{
						POSITION = '0';
						return INT_MAX - 1;
					}
					if(UP == '6')	 // 파워 습득 
					{
						_clMAZE.iPower++;
						POSITION = '0';
						UP = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(UP == '7')	 // 벽통과 습득 
					{
						_clMAZE.bGhost = true;
						POSITION = '0';
						UP = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(UP == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						UP = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					if(_clMAZE.I_POS > 0)	// 정상이동 
					{
						UP = '4';
						POSITION = '0';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				break;
				
			case M_DOWN:
				if(_clMAZE.I_POS < 18 && _clMAZE.bPush_S == true && DOWN == '0' && _clMAZE.MAZE_Arr[_clMAZE.I_POS + 2][_clMAZE.J_POS] == '1')	// 벽밀기 
				{
					if(_clMAZE.iPositionType == 1)
					{
						POSITION = '1';
						DOWN = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS + 2][_clMAZE.J_POS] = '0';
						return true;
					}
					else if(_clMAZE.iPositionType == 2)
					{
						POSITION = '5';
						DOWN = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS + 2][_clMAZE.J_POS] = '0';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				else if(DOWN != '0' && DOWN != '2' && DOWN != '5' && _clMAZE.iPositionType != 0)
				{
					if(DOWN == '3')
					{
						POSITION = '1';
						return INT_MAX - 1;
					}
					if(DOWN == '6')
					{
						_clMAZE.iPower++;
						if(POSITION != '5')POSITION = '1';
						DOWN = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(DOWN == '7')	 // 벽통과 
					{
						_clMAZE.bGhost = true;
						if(POSITION != '5')POSITION = '1';
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(DOWN == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					if(POSITION == '5')
					{
						if(DOWN == '6')_clMAZE.iPower++;
						else if(DOWN == '7')_clMAZE.bGhost = true;
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return INT_MAX - 2;
					}
					
					if(_clMAZE.I_POS < 19)
					{
						temp = DOWN;
						DOWN = POSITION;
						POSITION = temp;
						_clMAZE.iPositionType = 1;
					}
					return true;
				}
				else if(DOWN == '0' && _clMAZE.bGhost == true && _clMAZE.bPush_S != true) // 벽통과 
				{
					if(_clMAZE.iPositionType == 1)
					{
						_clMAZE.iPositionType = 0;
						POSITION = '1';
						DOWN = '4';
						return true; 
					}
					else if(_clMAZE.iPositionType == 0)
					{
						_clMAZE.iPositionType = 0;
						temp = DOWN;
						DOWN = POSITION;
						POSITION = temp;
						return true; 
					}
					else if(_clMAZE.iPositionType == 2)
					{
						DOWN = '4';
						POSITION = '5';
						_clMAZE.iPositionType = 0;
						return INT_MAX - 2;
					}
				}
				else if(_clMAZE.iPositionType == 0 && DOWN != '0')
				{
					if(DOWN == '5')return false;					
					if(DOWN == '3')	// 도착 
					{
						POSITION = '0';
						return INT_MAX - 1;
					}
					if(DOWN == '6')	 // 파워 습득 
					{
						_clMAZE.iPower++;
						POSITION = '0';
						DOWN = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(DOWN == '7')	 // 벽통과 습득 
					{
						_clMAZE.bGhost = true;
						POSITION = '0';
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(DOWN == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					if(_clMAZE.I_POS < 19)	// 정상이동 
					{
						POSITION = '0';
						DOWN = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				
				
				break;
				
			case M_LEFT:
				if(_clMAZE.J_POS > 1 && _clMAZE.bPush_S == true && LEFT == '0' && _clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS - 2] == '1')	// 벽밀기 
				{
					if(_clMAZE.iPositionType == 1)
					{
						POSITION = '1';
						LEFT = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS - 2] = '0';
						return true;
					}
					else if(_clMAZE.iPositionType == 2)
					{
						POSITION = '5';
						LEFT = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS - 2] = '0';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				else if(LEFT != '0' && LEFT != '2' && LEFT != '5' && _clMAZE.J_POS > 0 && _clMAZE.iPositionType != 0)
				{
					if(LEFT == '3')
					{
						POSITION = '1';
						return INT_MAX - 1;
					}
					if(LEFT == '6')
					{
						_clMAZE.iPower++;
						if(POSITION != '5')POSITION = '1';
						LEFT = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(LEFT == '7')	 // 벽통과 
					{
						_clMAZE.bGhost = true;
						if(POSITION != '5')POSITION = '1';
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(LEFT == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
						
					if(POSITION == '5')
					{
						if(LEFT == '6')_clMAZE.iPower++;
						else if(LEFT == '7')_clMAZE.bGhost = true;
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return INT_MAX - 2;
					}
					
					if(_clMAZE.J_POS > 0)
					{
						temp = LEFT;
						LEFT = POSITION;
						POSITION = temp;
						_clMAZE.iPositionType = 1;
					}
					return true;
				}
				else if(LEFT == '0' && _clMAZE.bGhost == true && _clMAZE.bPush_S != true) // 벽통과 
				{
					if(_clMAZE.iPositionType == 1)
					{
						_clMAZE.iPositionType = 0;
						POSITION = '1';
						LEFT = '4';
						return true; 
					}
					else if(_clMAZE.iPositionType == 0)
					{
						_clMAZE.iPositionType = 0;
						temp = LEFT;
						LEFT = POSITION;
						POSITION = temp;
						return true; 
					}
					else if(_clMAZE.iPositionType == 2)
					{
						LEFT = '4';
						_clMAZE.iPositionType = 0;
						return INT_MAX - 2;
					}
				}
				else if(_clMAZE.iPositionType == 0 && LEFT != '0')
				{
					if(LEFT == '5')return false;					
					if(LEFT == '3')	// 도착 
					{
						POSITION = '0';
						return INT_MAX - 1;
					}
					if(LEFT == '6')	 // 파워 습득 
					{
						_clMAZE.iPower++;
						POSITION = '0';
						LEFT = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(LEFT == '7')	 // 벽통과 습득 
					{
						_clMAZE.bGhost = true;
						POSITION = '0';
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(LEFT == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					if(_clMAZE.J_POS > 0)	// 정상이동 
					{
						POSITION = '0';
						LEFT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				break;
				
			case M_RIGHT:
				if(_clMAZE.J_POS < 18 && _clMAZE.bPush_S == true && RIGHT == '0' && _clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS + 2] == '1')	// 벽밀기 
				{
					if(_clMAZE.iPositionType == 1)
					{
						POSITION = '1';
						RIGHT = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS + 2] = '0';
						return true;
					}
					else if(_clMAZE.iPositionType == 2)
					{
						POSITION = '5';
						RIGHT = '4';
						_clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS + 2] = '0';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				else if(RIGHT != '0' && RIGHT != '2' && RIGHT != '5' && _clMAZE.iPositionType != 0)
				{
					if(RIGHT == '3')
					{
						POSITION = '1';
						return INT_MAX - 1;
						_clMAZE.iPositionType = 1;
					}
					if(RIGHT == '6')
					{
						_clMAZE.iPower++;
						if(POSITION != '5')POSITION = '1';
						RIGHT = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(RIGHT == '7')	 // 벽통과 
					{
						_clMAZE.bGhost = true;
					if(POSITION != '5')POSITION = '1';
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(RIGHT == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
						
					if(POSITION == '5')
					{
						if(RIGHT == '6')_clMAZE.iPower++;
						else if(RIGHT == '7')_clMAZE.bGhost = true;
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return INT_MAX - 2;
					}
						
					if(_clMAZE.J_POS < 19)
					{
						temp = RIGHT;
						RIGHT = POSITION;
						POSITION = temp;
						_clMAZE.iPositionType = 1;
					}
					return true;
				}
				else if(RIGHT == '0' && _clMAZE.bGhost == true && _clMAZE.bPush_S != true) // 벽통과 
				{
					if(_clMAZE.iPositionType == 1)
					{
						_clMAZE.iPositionType = 0;
						POSITION = '1';
						RIGHT = '4';
						return true; 
					}
					else if(_clMAZE.iPositionType == 0)
					{
						_clMAZE.iPositionType = 0;
						temp = RIGHT;
						RIGHT = POSITION;
						POSITION = temp;
						return true; 
					}
					else if(_clMAZE.iPositionType == 2)
					{
						RIGHT = '4';
						_clMAZE.iPositionType = 0;
						return INT_MAX - 2;
					}
				}
				else if(_clMAZE.iPositionType == 0 && RIGHT != '0')
				{
					if(RIGHT == '5')return false;					
					if(RIGHT == '3')	// 도착 
					{
						POSITION = '0';
						return INT_MAX - 1;
					}
					if(RIGHT == '6')	 // 파워 습득 
					{
						_clMAZE.iPower++;
						POSITION = '0';
						RIGHT = '4';
						if(_clMAZE.iPower > 5)_clMAZE.iPower = 5;
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(RIGHT == '7')	 // 벽통과 습득 
					{
						_clMAZE.bGhost = true;
						POSITION = '0';
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					else if(RIGHT == '8')	 // 벽밀기 습득 
					{
						_clMAZE.bPush = true;
						if(POSITION != '5')POSITION = '1';
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
					
					if(_clMAZE.J_POS < 19)	// 정상이동 
					{
						POSITION = '0';
						RIGHT = '4';
						_clMAZE.iPositionType = 1;
						return true;
					}
				}
				
				break;
		}
}

int Input_Move()
{
	int iInput;
	iInput = getch();
	
	switch(iInput)
	{
		case 'w':
			return M_UP;
		case 'W':
			return M_UP;
			
		case 's':
			return M_DOWN;
		case 'S':
			return M_DOWN;
			
		case 'a':
			return M_LEFT;
		case 'A':
			return M_LEFT;
			
		case 'd':
			return M_RIGHT;
		case 'D':
			return M_RIGHT;
			
		case 't':
			return M_INSERT;
		case 'T':
			return M_INSERT;
			
		case 'u':
			return M_BOOM;
		case 'U':
			return M_BOOM;
			
		case 'f':
			return M_PUSH;
		case 'F':
			return M_PUSH;
		default:
			return M_NONE;
	}
}

int Explosion(MAZE& _clMAZE, int MOVE)
{
	bool bDie = false;
	int iItem;
	switch(MOVE)
	{
		case M_INSERT:
			if(_clMAZE.iPositionType == 0)return false;
			if(_clMAZE.MAZE_Arr[1][1] == '4')
				return true;
			_clMAZE.MAZE_Arr[_clMAZE.I_POS][_clMAZE.J_POS] = '5';
			_clMAZE.iPositionType = 2;
			return true;
		
		case M_BOOM:
			for(int i = 0; i < 20; i++)
			{
				for(int j = 0; j < 20; j++)
				{
					if(B_POSITION == '5')
					{
						for(int t = 0; t < _clMAZE.iPower; t++)
						{
							if(B_UP == '0' && i - t > 0)
							{
								B_UP = '1';
								iItem = _clMAZE.SetItem();
								switch(iItem)
								{
									case I_NONE:
										break;
									case I_POWER:
									B_UP = '6';
										break;
									case I_GHOST:
										B_UP = '7';
										break;
									case I_PUSH:
										B_UP = '8';
										break; 
								}
							}
						
							if(B_DOWN == '0' && i + t < 20)
							{
								B_DOWN = '1';
								iItem = _clMAZE.SetItem();
								switch(iItem)
								{
									case I_NONE:
										break;
									case I_POWER:
										B_DOWN = '6';
										break;
									case I_GHOST:
										B_DOWN = '7';
										break;
									case I_PUSH:
										B_DOWN = '8';
										break; 
								}
							}
							
							if(B_LEFT == '0' && j - t > 0)
							{	
								B_LEFT = '1';
								iItem = _clMAZE.SetItem();
								switch(iItem)
								{
									case I_NONE:
										break;
									case I_POWER:
										B_LEFT = '6';
										break;
									case I_GHOST:
										B_LEFT = '7';
										break;
									case I_PUSH:
										B_LEFT = '8';
										break; 
								}
							}	
						
							if(B_RIGHT == '0' && j + t < 20)
							{	
								B_RIGHT = '1';
								iItem = _clMAZE.SetItem();
								switch(iItem)
								{
									case I_NONE:
										break;
									case I_POWER:
										B_RIGHT = '6';
										break;
									case I_GHOST:
										B_RIGHT = '7';
										break;
									case I_PUSH:
										B_RIGHT = '8';
										break; 
								}
							}
							
							if(B_UP == '4' || B_DOWN == '4' || B_LEFT == '4' || B_RIGHT == '4' || POSITION == '5')
							{
								POSITION = '1';
								bDie = true;
							}
							
							B_POSITION = '1';
						}
					}					
				}
			}
			if(bDie == true)return INT_MAX;
			return true;
	}
}

int main()
{
	system("mode con cols=42 lines=26");
	srand((unsigned int)time(0));
	MAZE _clMAZE;
	
	bool Repeat = true;
	bool Victory = false;
	bool Die = false;
	
	while(Repeat)
	{
		int iState = false;
		system("cls");
		OutPut_MAZE(_clMAZE);
		if(Victory == true)break; 
		
		int iInput = Input_Move();
		
		if(iInput == M_NONE)
			continue;
			
		if(iInput == M_INSERT || iInput == M_BOOM)
			iState = Explosion(_clMAZE, iInput);
		else
			iState = Moving_MAZE(_clMAZE, iInput);
		
		switch(iState)
		{
			case true:
				continue;
				
			case INT_MAX:
				for(int i = 0; i < 20; i++)
					for(int j = 0; j < 20; j++)
						if(_clMAZE.MAZE_Arr[i][j] == '2')
						{
							_clMAZE.I_POS = i;
							_clMAZE.J_POS = j;
							_clMAZE.MAZE_Arr[i][j] = '4';
						}
				break;
				
			case INT_MAX - 1:
				Victory = true;
				break;
		}
	}
	
	if(Victory == true)
	{
		cout << "※ 당신은 승리하셧습니다!" << endl;
		system("pause");
	}
	
	return 0;
	
}
