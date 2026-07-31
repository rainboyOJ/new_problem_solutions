#include <iomanip>
#include <iostream>

char str[105][105];
int xh[105];
double fs[105];
int n,k;
int main(){
	int i,j;
	std::cin >> n >> k;
	for(i=1;i<=n;i++){
		std::cin >> str[i];
		xh[i] = i;
		std::cin >> fs[i];
	}
	for(i=1;i<=n-1;i++)
		for(j=1;j<=n-i;j++){
			if( fs[j] > fs[j+1]){
				double t = fs[j];
				fs[j] = fs[j+1];
				fs[j+1] = t;
				
				int x = xh[j];
				xh[j] = xh[j+1];
				xh[j+1] = x; 
			} 
		}
	int p = n-k+1;
	std::cout << str[xh[p]] << " " << std::setprecision(6) << fs[p]; 
	
	return 0;
}
