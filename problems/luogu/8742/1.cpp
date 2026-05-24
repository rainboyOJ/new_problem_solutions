#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5+10;
int n;
int w[405];
int f[maxn];
int up=1e5;
int down=-up;

int mirror(int j){
    return j + up;
}

int main () {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> w[i];
        w[n+i] = -w[i];
    }

    int pre = 0;
    f[0] = 1;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = up ;j>=w[i];j--)
            f[j] = f[j] || f[j-w[i]];
    }
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        for(int j = 0 ;j<=up-w[i];j++)
            f[j] = f[j] || f[j+w[i]];
    }


    int ans = 0;
    for(int i = 1 ; i<=up;i++)
    {
        // std::cout << i << " " << f[i] << "\n";
        ans+=f[i];
    }
    std::cout << ans << "\n";
    
    return 0;
}
