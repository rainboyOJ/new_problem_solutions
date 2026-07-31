#include <iostream>
int a[105];
int n;
int main(){
    std::cin >> n;
    int i;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    for (i=n;i>=1;i--){
        std::cout << a[i] << " ";
    }
    return 0;
}
