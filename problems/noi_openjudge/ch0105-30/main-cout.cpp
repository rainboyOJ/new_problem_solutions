#include <iostream>


int main(){
    int n,k;
    std::cin >> n >> k;
    if( n % 19 != 0){
        std::cout << "NO";
        return 0;
    }
    int cnt = 0;
    while( n !=0){
        if( n % 10 == 3)
            cnt++;
        n /= 10;
    }
    if( cnt == k)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
