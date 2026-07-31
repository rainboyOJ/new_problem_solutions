#include <iostream>

struct ren {
	char name[100];
	int c;
};
ren a[20];
int n;
int main(){
	std::cin >> n;
	int i,j;
	for(i = 1;i<=n;i++){
		std::cin >> a[i].name;
		std::cin >> a[i].c;
	}
	for(i=1;i<=n-1;i++)
		for(j=1;j<=n-i;j++){
			if( a[j].c > a[j+1].c){
				ren t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	for(i=n;i>=1;i--){
		std::cout << a[i].name << " " << a[i].c << "\n";
	}
	return 0;
}
