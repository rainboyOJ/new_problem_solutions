#include <iomanip>
#include <iostream>

double a[] = {0, 28.9 , 32.7 , 45.6, 78 , 35 , 86.2 , 27.8, 43 , 56 , 65 };
double sum = 0;

int main(){
    int i,t;
    for(i=1;i<=10;i++){
        std::cin >> t;
        sum += t*a[i];
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(1) << sum << "\n";
    return 0;
}
