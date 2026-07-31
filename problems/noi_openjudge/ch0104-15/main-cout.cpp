#include <iostream>
int main(){
	int a,b,c;
	std::cin >> a >> b >> c;
	if(a < b)
		a = b;
	if( a < c)
		a = c;
	std::cout << a;
	return 0;
}
