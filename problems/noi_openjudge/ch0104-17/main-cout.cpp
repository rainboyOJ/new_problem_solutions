#include <iostream>
int main(){
	int a,b,c;
	std::cin >> a;
	if(  a % 4 == 0){
		if( a % 100 ==0 && a % 400 != 0 )
			std::cout << "N";
		else
			std::cout << "Y";
	}
	else
		std::cout << "N";
	return 0;
}
