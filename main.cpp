#include "dyna.hpp"

typedef struct {
    long x;
    long y;
} POINT;

int main() 
{
        unsigned char byte = 0x06;
        dyna_arr arr(sizeof(POINT));
	for (int i = 0; i < sizeof(POINT); i++)
	{
		arr.write(&byte, sizeof(unsigned char));
	}
	POINT point = arr.reinterpret<POINT>();
	std::cout << point.x << std::endl;
	return 0;
}
