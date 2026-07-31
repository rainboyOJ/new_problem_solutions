#include <cmath>
#include <iostream>
int n;
int cnt = 0;
void dfs(int f,int a){
    int i,end= (int)sqrt(a);
    for(i=f;i<=end;i++){
        if( a % i ==0){
            int ret = a / i;
            if ( ret >= i){
                cnt++;
                dfs(i,ret);
            }
        }
    }
}
int main(){
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        cnt = 0;
        dfs(2,t);
        std::cout << cnt+1 << "\n";
    }
    return 0;
}
