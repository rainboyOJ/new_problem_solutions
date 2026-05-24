/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-21 10:33:15
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];
int f[(1<<22)+5];

void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    memset(f,-1,sizeof(f));
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        //初始化 f[-1][mask]
        // 显然 f[-1][mask] 就要看 是不是存在 a[i] = mask
        f[a[i]] = a[i];
    }


    // 枚举 f[i][mask] 中的i
    for(int i = 0 ;i < 22; i++) {

        // 枚举 mask
        for(int mask = 0;mask < (1<<22) ;++mask ) // mask: 0->22
        {
            // 如果 Bit_i(mask) == 0
            // f[i][mask] = f[i-1][mask]
            // 什么也不用做

            // 如果 Bit_i(mask) == 1
            // f[i][mask] = f[i-1][mask](!=-1) or  f[i-1][mask^(1<<i)](!=-1)

            if( mask & (1<<i) )  {

                if( f[mask] /* f[i][mask]*/ == -1) {
                    // 试一试另外一个
                    f[mask] = f[mask^(1<<i)];

                }
            }
            
        }
    }

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int other = ~a[i] &((1<<22)-1 ); // 补集
        std::cout << f[other] << " ";
    }

    
    return 0;
}
