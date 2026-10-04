/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:24
 * update_at: 2026-10-04 23:24
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 11;
const int MAXSTATE = 1 << MAXN; // n <= 10，子集掩码最多 2^10 种

typedef long long ll;

ll n;
ll a[MAXN];             // a[i]：第 i 个数（下标从 0 开始，与掩码位对应）
ll conflict[MAXN];      // conflict[i]：与第 i 个数不互质（冲突）的下标掩码
ll f[MAXSTATE];         // f[S]：把下标集合 S 划分成合法组所需的最少组数
char independent[MAXSTATE]; // independent[S]：S 内部是否两两互质（0/1），用 char 控制内存

// 求 x 与 y 是否互质。
bool coprime(ll x, ll y) {
    return __gcd(x, y) == 1;
}

// 预处理每个数的冲突掩码，以及全部 2^n 个集合的"是否独立"。
void build_conflict() {
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (i != j && !coprime(a[i], a[j])) {
                conflict[i] |= (1LL << j); // i 与 j 不互质，不能同组
            }
        }
    }

    independent[0] = 1; // 空集独立
    for (ll S = 1; S < (1LL << n); S++) {
        // 取最低位 v：S 独立 <=> S 去掉 v 后独立，且 v 与 S 剩余部分无冲突
        ll v = 0;
        while (!(S & (1LL << v))) v++;
        ll rest = S ^ (1LL << v);
        independent[S] = (independent[rest] && (conflict[v] & rest) == 0) ? 1 : 0;
    }
}

void solve() {
    build_conflict();

    f[0] = 0; // 空集不需要任何组
    for (ll S = 1; S < (1LL << n); S++) {
        // 最优划分中必有一组包含 S 的最低位，枚举包含最低位的独立子集 T 作为第一组
        ll low = 0;
        while (!(S & (1LL << low))) low++;

        f[S] = LLONG_MAX;
        // 枚举 S 的所有子集 t（必含最低位 low）
        for (ll t = S; t > 0; t = (t - 1) & S) {
            if (!(t & (1LL << low))) continue;
            if (!independent[t]) continue; // 同一组内必须两两互质
            if (f[S ^ t] + 1 < f[S]) {
                f[S] = f[S ^ t] + 1;
            }
        }
    }

    cout << f[(1LL << n) - 1] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
