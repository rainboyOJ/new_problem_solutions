#include <cstring>
#include <iostream>
int n;
int cnt[200] = {0};
int a[20009];
int main(){
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        a[i] = t;
        cnt[t] = 1;
    }
    for (i=1;i<=n;i++){
        if( cnt[a[i]]){
            std::cout << a[i] << " ";
            cnt[a[i]]--;
        }
    }
    return 0;
}
