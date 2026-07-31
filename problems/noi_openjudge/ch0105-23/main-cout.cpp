#include <iostream>
int main(){
	int m,n,a,i,cnt = 0;
	std::cin >> m >> n;
	for(i = 1;i<=n;i++){
		std::cin >> a;
		if( a > m )
			cnt++;
		else
			m = m - a;
	}
	std::cout << cnt;
	return 0;
}
