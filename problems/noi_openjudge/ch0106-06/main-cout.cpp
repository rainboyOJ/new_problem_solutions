#include <iostream>
int l,m;
int a[10005] = {0};
int main(){
    std::cin >> l >> m;
    int i,j;
    for (i=1;i<=m;i++){
        int s,t;
        std::cin >> s >> t;
        for (j=s;j<=t;j++){
            a[j] = 1;
        }
    }
    int cnt = 0;
    for (i=0;i<=l;i++){
        if(!a[i]) cnt++;
    }
    std::cout << cnt << "\n";
    return 0;
}
