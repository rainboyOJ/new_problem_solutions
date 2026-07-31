#include <iostream>
int main(){
	int a,b,c;
	std::cin >> a >> b;
	if( a >=-1 && a <=1 && b >=-1 && b <=1 )
		std::cout << "yes";
	else
		std::cout << "no";
	return 0;
}
