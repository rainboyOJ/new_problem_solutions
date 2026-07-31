#include <iostream>

int main(){
    int k;
    int a=1,b=1,c;
    int i;
    std::cin >> k;
    if( k==1 || k == 2){
        std::cout << "1";
        return 0;
    }

    for (i=3;i<=k;i++){
        c = a +b;
        a = b;
        b = c;
    }
    std::cout << c << "\n";
    return 0;
}
