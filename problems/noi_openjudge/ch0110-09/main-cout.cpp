#include <iostream>
int n;
int cnt = 0;
int a[1200] = {0};
int main(){
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        if( a[t] == 0){
            cnt++;
            a[t] = 1;
        }
    }

    std::cout << cnt << "\n";
    for (i=1;i<=1000;i++){
        if( a[i] == 1)
            std::cout << i << " ";
    }
    return 0;
}
