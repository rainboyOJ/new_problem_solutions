#include <iostream>
int n,m;
int ans;
void dfs(int dep,int pre,int sheng){
	if( dep == n){
		if( sheng >= pre) ans++;
		return;
	}
	int i;
	for(i=pre;i<=sheng;i++){
		dfs(dep+1,i,sheng-i);
	}
}
int main(){
	int t;
	std::cin >> t;
	while(t--){
		std::cin >> m >> n;
		ans  =0;
		dfs(1,0,m);
		std::cout << ans << "\n";
	}
	return 0;
}
