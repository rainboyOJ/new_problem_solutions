#include <iostream>

int main(){
    int n;
    int sum = 0;
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        if( sum < t)
            sum = t;
    }
    std::cout << sum << "\n";
    return 0;
}
