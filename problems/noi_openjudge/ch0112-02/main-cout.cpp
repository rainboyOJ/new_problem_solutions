#include <iomanip>
#include <iostream>
int n;
double sum = 0;

void init(){
    std::cin >> n;
}

double calc(int len){
    int a = len / 70;
    if( len % 70 != 0 )
        a++;
    return a*0.1;
}
int main(){
    init();
    int i,t;
    for (i=1;i<=n;i++){
        std::cin >> t;
        sum += calc(t);
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(1) << sum << "\n";
    return 0;
}
