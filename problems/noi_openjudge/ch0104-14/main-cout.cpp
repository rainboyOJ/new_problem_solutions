#include <iostream>

int  main(){
	int w,y;
	std::cin >> w;
	y = std::cin.get();
	y = std::cin.get();
	int h = 8;
	if( w - 1000 > 0){
		int c = w - 1000;
		h = h + (c / 500) * 4;
		if( c % 500 != 0){
			h = h +4;
		}
	}
	if( y == 'y')
		h = h + 5;
	std::cout << h;
	return 0;
}
