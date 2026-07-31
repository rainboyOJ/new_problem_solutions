#include <iostream>

int main(){
    int n;
    int a,b;
    std::cin >> n;
    std::cin >> a >> b;
    double rate_1 = b*1.0/a;
    int i;
    for (i=1;i<n;i++){
        std::cin >> a >> b;
        double rate_2 = b*1.0 / a;
        if( rate_1 - rate_2 > 0.05)
            std::cout << "worse\n";
        else if ( rate_2 - rate_1 > 0.05)
            std::cout << "better\n";
        else
            std::cout << "same\n";
    }
    return 0;
}
