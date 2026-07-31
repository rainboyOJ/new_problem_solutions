#include <bits/stdc++.h>
using namespace std;

int n;

int main(){
    std::cin >> n;
    int a,b,c;
    int cnt = 0;
    for(c=0;c<=n /5;c++){
        for(b=0;b<=n/2;b++){
            for(a=0;a<=n;a++){
                if( c*5 + b *2 + a == n){
                    cnt++;
                    std::cout << std::setfill('0') << std::setw(3) << cnt << std::setfill(' ') << std::setw(12) << a << std::setw(12) << b << std::setw(12) << c << "\n";
                }
            }
        }
    }
    return 0;
}
