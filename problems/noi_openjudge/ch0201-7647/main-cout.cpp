#include <bits/stdc++.h>
using namespace std;

int a,b,c;
int x;

int main(){
    std::cin >> a >> b >> c;
    int i;
    for(i=2;i<=1000005;i++){
        int t1 = a % i;
        int t2 = b % i;
        int t3 = c % i;
        if( t1 == t2 && t2 == t3 && t1 == t3){
            std::cout << i << "\n";
            return 0;
        }
    }
    return 0;
}
