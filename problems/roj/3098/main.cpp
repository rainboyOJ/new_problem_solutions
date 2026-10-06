/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 16:50
 * update_at: 2026-10-04 22:12
 */
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;

// 返回 f(N) = sum_{i=1}^{N} gcd(i,N)
// 利用积性：f = id * phi，对质因子幂 p^a，局部因子为 p^{a-1} * (p + a*(p-1))
ll solve(ll N) {
    ll ans = 1;
    // 试除法分解质因数，O(sqrt(N))
    for (ll p = 2; p * p <= N; ++p) {
        if (N % p == 0) {
            ll a = 0;
            ll pw = 1; // p^a
            while (N % p == 0) {
                N /= p;
                ++a;
                pw *= p;
            }
            // 局部因子：p^{a-1} * (p + a*(p-1))
            // pw 已经是 p^a，所以 p^{a-1} = pw / p
            ll part = (pw / p) * (p + a * (p - 1));
            ans *= part;
        }
    }
    // 剩余一个大于 sqrt(原N) 的质因子
    if (N > 1) {
        // 此时 a = 1, p = N, p^{a-1} = 1, 局部因子 = 1 * (N + 1*(N-1)) = 2*N - 1
        ll part = 2 * N - 1;
        ans *= part;
    }
    return ans;
}

int main() {
    ll N;
    scanf("%lld", &N);
    printf("%lld\n", solve(N));
    return 0;
}
