#include "Interface.h"

int main()
{
	Clean_Cussor();
	_clHandle map;
	map.Output_Main();
	map.Output_Explain();
	while(true)
	{
		if(map.Playing_Game() == true)
			continue;
		else break;
	}
	
	return 0;
}
