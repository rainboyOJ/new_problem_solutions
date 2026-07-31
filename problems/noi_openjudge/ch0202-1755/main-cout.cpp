#include <cstring>
#include <iostream>

int n;

int fac(int n){
    if( n ==2 || n==1)
        return 1;

    return fac(n-1)+fac(n-2);
}

int main(){
    std::cin >> n;
    int i,t;
    for(i=1;i<=n;i++){
        std::cin >> t;
        int ans = fac(t);
        std::cout << ans << "\n";
    }
    return 0;
}
