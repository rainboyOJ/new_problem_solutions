/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-22 19:13:56
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
ll f[maxn];

void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }

    // 背包

    //枚举物品
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        //枚举容量
        for(int j = m; j >= a[i];j--)
            f[j] = max(f[j],f[j-a[i]] + a[i]); 
    }
    std::cout << f[m] << "\n";

    
    return 0;
}
