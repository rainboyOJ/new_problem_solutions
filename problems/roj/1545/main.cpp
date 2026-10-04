/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:27
 * update_at: 2026-10-05 07:27
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;   // 牛的数量上限 5*10^4
const int MAXLOG = 17;    // 2^16 <= 5*10^4 < 2^17，所以只需 0..16 层

typedef long long ll;

ll n, q;

// 身高最大 10^6，区间极值用 int 存即可，省一半内存
int st_max[MAXLOG][MAXN]; // st_max[k][i]：区间 [i, i+2^k-1] 内的最高身高
int st_min[MAXLOG][MAXN]; // st_min[k][i]：区间 [i, i+2^k-1] 内的最低身高
int lg[MAXN];             // lg[len] = floor(log2(len))

// 倍增建表：长度 2^k 的区间由两个长度 2^(k-1) 的区间拼成。
void build_st() {
    lg[1] = 0;
    for (ll i = 2; i <= n; i++) {
        lg[i] = lg[i / 2] + 1;
    }

    for (ll k = 1; (1LL << k) <= n; k++) {
        ll half = 1LL << (k - 1);
        ll cnt = n - (1LL << k) + 1; // 该层能作为起点的个数
        for (ll i = 1; i <= cnt; i++) {
            st_max[k][i] = max(st_max[k - 1][i], st_max[k - 1][i + half]);
            st_min[k][i] = min(st_min[k - 1][i], st_min[k - 1][i + half]);
        }
    }
}

void solve() {
    cin >> n >> q;

    for (ll i = 1; i <= n; i++) {
        cin >> st_max[0][i];
        st_min[0][i] = st_max[0][i];
    }

    build_st();

    for (ll t = 1; t <= q; t++) {
        ll a, b;
        cin >> a >> b;
        ll len = b - a + 1;
        ll k = lg[len];
        // 两段长度为 2^k 的可重叠区间恰好盖住 [a, b]
        ll tail = b - (1LL << k) + 1;
        int hi = max(st_max[k][a], st_max[k][tail]);
        int lo = min(st_min[k][a], st_min[k][tail]);
        cout << hi - lo << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
