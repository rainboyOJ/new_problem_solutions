#include <bits/stdc++.h>
using namespace std;

int main(){
    int i,j;
    int sum=0;
    int n;
    std::cin >> n;

    for(i=1;1;i++){ // 数量
        sum += i;
        if( sum < n) continue;
        for(j=1;j<=i;j++) { //自己家的门牌
            if( sum-(j*2) == n){
                std::cout << j << " " << i << "\n";
                return 0;
            }
        }
        
    }
    return 0;
}
