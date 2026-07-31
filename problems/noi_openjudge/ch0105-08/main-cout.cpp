#include <iostream>

int main(){
    int n;
    int sum = 0;
    int i;
    int a=0,b=0,c=0;
    int t1,t2,t3;
    std::cin >> n;
    for (i=1;i<n;i++){
        std::cin >> t1;
        a += t1;
    }
    b = (n-2)*180;
    std::cout << b-a << "\n";
    return 0;
}
