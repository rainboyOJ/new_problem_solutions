#include <iostream>
int n;
int a[1005];
int b[1005];

int main(){
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    for (i=1;i<=n;i++){
        std::cin >> b[i];
    }
    int sum = 0;
    for (i=1;i<=n;i++){
        sum += a[i]*b[i];
    }
    std::cout << sum << "\n";
    return 0;
}
