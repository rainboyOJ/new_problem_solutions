#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
/*
file:baoli.cpp
4 3
513 598 567 689
500 600 550
*/
const int maxn = 1e5+5;
ll a[maxn];
ll b[maxn];
int m,n;


int bs_find(int l,int r,int key) {
    while (l < r) {
        int mid  = (l+r) /2;
        if( a[mid] >= key) {
            r = mid;
        }
        else 
            l = mid+1;
    }
    return l;
}


int main(){
    std::cin >> m >> n;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        std::cin >> a[i];
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> b[i];
    }

    std::sort(a+1,a+1+m);
    a[m+1] = 2e9;

    ll ans = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int pos = bs_find(1,m+1,b[i]);

        // 注意: 这里没有前面的数了
        if( pos == 1) {
            ans+= a[pos] - b[i];
        }
        else {
            int x = pos-1;
            int y = pos;
            ans += std::min(a[y]-b[i],b[i] - a[x]);
        }
        
    }
    std::cout << ans << "\n";

    return 0;
}
// 
