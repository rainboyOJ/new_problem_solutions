#include <iostream>

int main(){
    int a[101];
    int n,m;
    int i;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> a[i];
    }
    std::cin >> m;
    int cnt =0;
    for (i=1;i<=n;i++){
        if( a[i] == m)
            cnt++;
    }
    std::cout << cnt;
    return 0;
}
