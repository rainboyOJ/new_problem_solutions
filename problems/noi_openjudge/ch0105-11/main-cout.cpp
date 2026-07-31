#include <iostream>

int main(){
    int i;
    int n;
    std::cin >> n;
    int a=0,b=0,c=0;

    int t;
    for (i=1;i<=n;i++){
        std::cin >> t;
        if( t == 1)
            a++;
        if( t == 5)
            b++;
        if( t == 10)
            c++;
    }
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << c << "\n";
    return 0;
}
