#include <iostream>

int main(){
    int n;
    int sum = 0;
    int i;
    int a=0,b=0,c=0;
    int t1,t2,t3;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t1 >> t2 >> t3;
        a += t1;
        b += t2;
        c += t3;
    }
    std::cout << a << " " << b << " " << c << " " << a+b+c << "\n";
    return 0;
}
