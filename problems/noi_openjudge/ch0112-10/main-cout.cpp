#include <iostream>

bool is_prime(int x){
    int i;
    for (i=2;i<x;i++){
        if( x % i == 0)
            return 0;
    }
    return 1;
}
int main(){
    int n;
    std::cin >> n;
    int i,cnt = 0;
    for (i=3;i<=n-2;i++){
        if( is_prime(i) && is_prime(i+2)){
            cnt++;
            std::cout << i << " " << i+2 << "\n";
        }
    }
    if( !cnt)
        std::cout << "empty";
    return 0;
}
