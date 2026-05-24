/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-18 08:59:01
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    } 
    std::cin >> m;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    int ans= 0;
    // baoli 
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = i+1;j <= n ;++j ) // j: 1->n
        {
            if( a[i] + a[j] == m)
            {
                std::cout << a[i] << " ";
                std::cout << a[j] << "\n";

            }
        }
    }

    
    
    return 0;
}
