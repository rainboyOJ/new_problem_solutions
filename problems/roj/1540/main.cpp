/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:12
 * update_at: 2026-10-05 07:12
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 4097; // 坐标最大到 4096，数组下标要多开一位

ll n, m;
ll tree[MAXN][MAXN]; // tree[i][j] 管辖原矩阵 [i-lowbit(i)+1, i] * [j-lowbit(j)+1, j] 的矩形和

// 单点增加：把 A[x][y] 加上 k，沿两个方向的 lowbit 链向上更新所有管辖它的节点。
void add(ll x, ll y, ll k) {
    for (ll i = x; i <= n; i += i & -i) {
        for (ll j = y; j <= m; j += j & -j) {
            tree[i][j] += k;
        }
    }
}

// 二维前缀和查询：返回 A[1..x][1..y] 的元素和，沿两个方向的 lowbit 链向下累加。
ll query(ll x, ll y) {
    ll res = 0;
    for (ll i = x; i > 0; i -= i & -i) {
        for (ll j = y; j > 0; j -= j & -j) {
            res += tree[i][j];
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    ll op;
    while (cin >> op) {
        if (op == 1) {
            ll x, y, k;
            cin >> x >> y >> k;
            add(x, y, k);
        } else {
            ll a, b, c, d;
            cin >> a >> b >> c >> d;
            // 容斥：子矩阵 [a, c] * [b, d] 的和 = 四个前缀矩形和的加减组合
            ll ans = query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1);
            cout << ans << "\n";
        }
    }

    return 0;
}
