#include <iostream>


int main(){
    int n;
    std::cin >> n;
    int sum=0,i,s = 1;
    for (i=1;i<=n;i++){
        s = s*i;
        sum += s;
    }
    std::cout << sum << "\n";

    return 0;
}
