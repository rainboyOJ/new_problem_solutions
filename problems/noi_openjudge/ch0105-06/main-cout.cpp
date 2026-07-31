#include <iostream>

int main(){
    int n;
    int sum = 0;
    int min = 99999999;
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        if( sum < t)
            sum = t;
        if( min > t)
            min  =t;
    }
    std::cout << sum-min << "\n";
    return 0;
}
