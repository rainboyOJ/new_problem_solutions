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
int cnt[maxn];

void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    memset(cnt,-1,sizeof(cnt));
    // bao li
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= n ;++j ) // j: 1->n
        {
            if( i ==j ) continue;
            if( (a[i] & a[j]) ==0) 
                cnt[i] = a[j];
        }
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cout << cnt[i] << " ";
    }
    
    return 0;
}
