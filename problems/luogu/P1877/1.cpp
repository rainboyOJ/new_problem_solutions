/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-21 15:02:10
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int f[55][1000+5];
int begin_level,max_level;

void init(){
    std::cin >> n;
    std::cin >> begin_level >> max_level;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    f[0][begin_level] = 1;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 0 ;j<=max_level;j++) {

            // 往上调
            int need_level = j - a[i];
            int t1 = 0;
            if( need_level >= 0)
                t1 = f[i-1][need_level];

            // 往下调
            need_level = j +a[i];
            int t2 = 0;
            if( need_level <= max_level) 
                t2 = f[i-1][need_level];

            f[i][j] = t1 || t2;
            // std::cout << f[i][j] << " ";
        }
        // std::cout  << "\n";
    }

    int ans = -1;
    for(int i = 0;i <= max_level ;++i ) // i: 1->n
    {
        if( f[n][i] == 1) ans = i;
    }
    std::cout << ans << "\n";
    
    return 0;
}
