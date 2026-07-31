#include <iostream>

int main(){
    int n,k;
    std::cin >> n >> k;
    int i;
    double lilv = 1+k*0.01;
    double fangjia= 200;
    for (i=1;i<=20;i++){
        if( n*i*1.0 >= fangjia){
            break;
        }
        fangjia = fangjia * lilv;
    }
    if( i <= 20){
        std::cout << i;
    }
    else
        std::cout << "Impossible";
    return 0;
}
