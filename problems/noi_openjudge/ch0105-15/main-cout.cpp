#include <iostream>

int main(){
    int r,m,y;
    std::cin >> r >> m >> y;
    double lilv = 1+ r*0.01;
    double result = m;
    int i;
    for (i=1;i<=y;i++){
        result = result*lilv;
    }
    std::cout << (int)result << "\n";
    return 0;
}
