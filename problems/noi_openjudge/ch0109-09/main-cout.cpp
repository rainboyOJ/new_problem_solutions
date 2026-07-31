#include <cmath>
#include <iostream>
int n;
int cnt[10005] = {0};
int main(){
    std::cin >> n;
    int max=-1;
    int i,t;
    for (i=1;i<=n;i++){
        std::cin >> t;
        cnt[t]++;
        if( max < t)
            max =t;
    }
    for (i=0;i<=max;i++){
        std::cout << cnt[i] << "\n";
    }
    return 0;
}
