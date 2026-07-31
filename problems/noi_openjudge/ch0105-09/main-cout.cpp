#include <iostream>

int main(){
	int m,n;
	std::cin >> m >> n;
	int i,sum = 0;
	for(i=m;i<=n;i++){
		if( i % 2 == 1)
			sum += i;
	}
	std::cout << sum;
	return 0;
}
