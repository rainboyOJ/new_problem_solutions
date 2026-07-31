#include <iostream>

int main(){
    int n;
    std::cin >> n;
    if( n % 3 ==0 && n % 5 == 0 && n % 7 ==0){
        std::cout << "3 5 7";
    }
    else if(n % 3 ==0 && n % 5 == 0){
        std::cout << "3 5";
    }
    else if(n % 3 ==0 && n % 7 == 0){
        std::cout << "3 7";
    }
    else if(n % 5 ==0 && n % 7 == 0){
        std::cout << "5 7";
    }
    else if ( n % 3 == 0)
        std::cout << "3";
    else if ( n % 5 == 0)
        std::cout << "5";
    else if ( n % 7 == 0)
        std::cout << "7";
    else {
        std::cout << "n";
    }
    return 0;
}
