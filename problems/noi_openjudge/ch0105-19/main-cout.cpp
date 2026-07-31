#include <cmath>
#include <iomanip>
#include <iostream>

double get_time(double x,double y){
    double len  = sqrt(x*x+y*y);
    return 2*len / 50;
}
double get_up_down_time(int num){
    return num +num*0.5;
}
int main(){
    int n;
    std::cin >> n;
    int i;
    double t1,t2;
    int t3;
    double time1 = 0;
    for (i=1;i<=n;i++){
        std::cin >> t1 >> t2 >> t3;
        time1 += get_time(t1,t2);
        time1 += get_up_down_time(t3);
        //std::cout << std::fixed << std::setprecision(6) << time1 << "\n";
    }
        std::cout << (int)ceil(time1) << "\n";
    return 0;
}
