//
#include <bits/stdc++.h>
const int maxn = 1e5+5;
int n;
int a[maxn];
int v[maxn];

int main() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        if( i > 1) {
            v[i-1] = a[i] - a[i-1];
        }
    }

    // 一个容量无限的背包
    int f = 0;
    for(int i = 1;i < n ;++i ) // i: 1->n
    {
        // f[i][j]
        f = std::max(f,f+v[i]);
        // 看起来和原来的贪心就一样了
    }
    std::cout << f << "\n";
    

    return 0;
}
