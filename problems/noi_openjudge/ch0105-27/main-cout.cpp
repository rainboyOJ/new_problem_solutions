#include <iostream>

int main(){
    int k;
    std::cin >> k;
    double sum = 0,kk = k;
    int i;
    for (i=1;1;i++){
        sum += 1.0/i;
        if( sum > k){
            std::cout << i;
            return 0;
        }
    }
    return 0;
}
