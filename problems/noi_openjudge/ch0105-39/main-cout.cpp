#include <iostream>


int main(){
    int sum = 0;
    int i,n;
    std::cin >> n;
    for (i=1;i<=n;i++){
        if( i % 7 == 0) continue;
        bool flag= false;
        int t= i;
        while( t != 0){
            int a = t % 10;
            if( a == 7){
                flag = 1;
                break;
            }
            t /= 10;
        }
        if( flag) continue;
        sum += i*i;
    }
    std::cout << sum << "\n";
    return 0;
}
