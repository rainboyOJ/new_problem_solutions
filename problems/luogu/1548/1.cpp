/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-02-10 15:04:40
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];

void init(){

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    std::cin >> m;

    ll tot_square = 0;
    int limit = min(n,m);

    for(int i = 1;i <= limit ;++i ) // i: 1->limit
    {
        tot_square += (n - i + 1) * ( m - i + 1);
    }
    std::cout << tot_square << " ";

    ll tot_rect = 0;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 1;j <= m ;++j ) // j: 1->m
        {
            if( i == j) continue;

            tot_rect += (n -i + 1) * ( m - j + 1);
        }
    }
    std::cout << tot_rect << "\n";

    
    
    return 0;
}
