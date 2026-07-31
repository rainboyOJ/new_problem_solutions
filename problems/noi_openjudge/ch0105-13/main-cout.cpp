#include <iostream>

int main(){
    int a,n;
    std::cin >> a >> n;
    int i;
    int ans = 1;
    for (i=1;i<=n;i++){
        ans = ans *a;
    }
    std::cout << ans << "\n";
    return 0;
}
