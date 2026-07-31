#include <cmath>
#include <iostream>

int main(){
    int t,n,i,c;
    t=1;
    while(t--){
        std::cin >> n;
        for (i=n;i>=1;i--){
            std::cin >> c;
            c *= i;
            std::cout << c << " ";
        }
        std::cin >> c;
        if( n == 0){
            std::cout << "0";
        }
        std::cout << "\n";
    }
    return 0;
}
