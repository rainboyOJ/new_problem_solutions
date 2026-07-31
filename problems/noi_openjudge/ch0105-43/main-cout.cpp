#include <cmath>
#include <iostream>

bool is_prime(int n){
    int i;
    for(i=2;i<=(int)sqrt(n);i++ ){
        if( n % i ==0)
            return 0;
    }
    return 1;
}


int main(){
    int n;
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        if( n % i == 0 && is_prime(i)){
            int a = n / i;
            if( is_prime(a)){
                std::cout << a << "\n";
                return 0;
            }
        }
    }
    return 0;
}
