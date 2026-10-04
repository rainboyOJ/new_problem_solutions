/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:36
 * update_at: 2026-10-04 21:36
 */
// main.cpp：工资降序后，m>=2 时把最小的 n-x-y 人连续两年拿 C 开除，
// 幸存者恰 x+y 人年年涨薪，答案为 3^m*S_x + 2^m*(S_{x+y}-S_x)；m=1 无人被开除需补上拿 C 者的原工资。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;   // n 的上界
const ll MOD = 1000000007; // 答案模数

ll salary[MAXN]; // salary[i] 表示工资降序后第 i 大的初始工资（下标从 1 开始）
ll pre[MAXN];    // pre[j] 表示工资最高的前 j 人的工资之和

// 快速幂：返回 base^exp mod MOD，用于计算 m 年的总倍数 3^m、2^m
ll power(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, x, y;
    cin >> n >> m >> x >> y;
    for (ll i = 1; i <= n; i++) {
        cin >> salary[i];
    }

    // 涨薪名额总是给当前工资最高的人最划算，故按工资从大到小排序
    sort(salary + 1, salary + n + 1, greater<ll>());
    for (ll i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + salary[i];
    }

    ll ans;
    if (m == 1) {
        // 只有一年：不可能连续两年拿 C，无人被开除，拿 C 的人照领原工资
        ans = 3 * (pre[x] % MOD) % MOD;
        ans = (ans + 2 * ((pre[x + y] - pre[x]) % MOD)) % MOD;
        ans = (ans + (pre[n] - pre[x + y]) % MOD) % MOD;
    } else {
        // 让最小的 k = n - x - y 人前两年连续拿 C 被开除，
        // 此后在职者恰好 x + y 人年年涨薪：前 x 大总倍数 3^m，接下来 y 大总倍数 2^m
        ll three = power(3, m);
        ll two = power(2, m);
        ans = three * (pre[x] % MOD) % MOD;
        ans = (ans + two * ((pre[x + y] - pre[x]) % MOD)) % MOD;
    }

    cout << ans % MOD << '\n';
    return 0;
}
