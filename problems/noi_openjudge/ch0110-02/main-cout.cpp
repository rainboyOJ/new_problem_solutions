#include <algorithm>
#include <iostream>
using namespace std;

int n,t;
int a[1000];
int cnt = 0;

int main(){
	std::cin >> n;
	int i;
	for(i=1;i<=n;i++){
		std::cin >> t;
		if( t % 2 == 1){
			cnt++;
			a[cnt] = t;
		}
	}
	sort(a+1,a+cnt+1);
	std::cout << a[1];
	for(i=2;i<=cnt;i++)
		std::cout << "," << a[i];
	

	return 0;
}
