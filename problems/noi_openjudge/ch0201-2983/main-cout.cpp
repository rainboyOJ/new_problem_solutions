#include <bits/stdc++.h>
using namespace std;

int a[205];
int cnt[205]  ={0} ;
int n,m;

int main(){
    std::cin >> n >> m;
    int i,t;
    for(i=1;i<=n;i++){
        std::cin >> t;
        a[i] = t;
        cnt[t]++;
    }
    for(i=1;i<=n;i++){
        if(cnt[ a[i] ] < 2)
            std::cout << "BeiJu\n";
        else
            std::cout << cnt[a[i]]-1 << "\n";
    }
    return 0;
}
