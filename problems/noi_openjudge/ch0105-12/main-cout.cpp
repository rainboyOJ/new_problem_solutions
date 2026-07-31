#include <iostream>

int main(){
    int n,m;
    std::cin >> n >> m;
    int i,a,cnt=0;
    for (i=1;i<=n;i++){
        std::cin >> a;
        if ( a== m)
            cnt++;
    }
    std::cout << cnt << "\n";
    return 0;
}
