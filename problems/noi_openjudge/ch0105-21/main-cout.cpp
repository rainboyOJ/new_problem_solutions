#include <iostream>

int  main(){
	long long n;
	std::cin >> n;
	while( n != 1) {
		long long  ans;
		if( n % 2 == 1){
			ans = n*3+1;
			std::cout << n << "*3+1=" << ans << "\n";
		}
		else {
			ans =n /2;
			std::cout << n << "/2=" << ans << "\n";
		}
		n = ans;
	}
	std::cout << "End";
	return 0;
}
