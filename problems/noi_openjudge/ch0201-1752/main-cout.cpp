#include <bits/stdc++.h>
using namespace std;


int n;

int main(){
    std::cin >> n;
    int _min = 0x7f7f7f7f;
    int _max=0;

    /* 坑点 */
    if( n % 2 != 0){
        std::cout << 0 << " " << 0 << "\n";
        return 0;
    }

    int i,j;
    int max_chicken= n /2;
    int max_rabit = n/4;

    for(i=0;i<= max_chicken;i++){
        for (j=0;j<=max_rabit;j++){
            if(i * 2 + j * 4 == n){
                _min = min(_min,i+j);
                _max = max(_max, i+j);
            }
        }
    }
    std::cout << _min << " " << _max << "\n";
    return 0;
}
