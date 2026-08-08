#include <bits/stdc++.h>
using namespace std;

const long long maxn = 3e5+10;
long long n;
long long w[405];
long long f[2][maxn];
long long up=15;
long long down=-up;

long long mirror(long long j){
    return j + up;
}


int main () {
    std::cin >> n;
    for(long long i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> w[i];
        w[n+i] = -w[i];
    }

    long long pre = 0;
    f[0][mirror(0)] = 1;

    for(long long i = 1;i <= 2*n ;++i ) // i: 1->n
    {
        long long now = pre^1;
        for(long long j = down; j<=up;j++) {
            f[now][mirror(j)] = 0;
            f[now][mirror(j)] = f[pre][mirror(j)] || f[pre][mirror(j-w[i])];
        }
        pre ^=1;
    }

    long long ans = 0;
    for(long long i = 1 ; i<=up;i++)
        ans += f[pre^1][mirror(i)];
    std::cout << ans << "\n";
    
    return 0;
}
