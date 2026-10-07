/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll n, k;
ll parent[MAXN]; // parent[i] 表示第 i 个人所在家庭的代表元
ll cnt[MAXN];    // cnt[代表元] = 该家庭的人数

// 查找 x 所在家庭的代表元，路径减半压缩。
ll find_root(ll x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

// 把 x、y 所在的两个家庭合并。
void union_family(ll x, ll y) {
    ll rx = find_root(x);
    ll ry = find_root(y);
    if (rx != ry) {
        parent[ry] = rx;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 最初每个人自己就是一个家庭。
    for (ll i = 1; i <= n; i++) {
        parent[i] = i;
    }

    // 每读入一个关系就把它看作一条无向边，合并两个家庭。
    for (ll i = 1; i <= k; i++) {
        ll x, y;
        cin >> x >> y;
        union_family(x, y);
    }

    ll families = 0;  // 家庭个数
    ll largest = 0;   // 最大家庭人数
    for (ll i = 1; i <= n; i++) {
        cnt[find_root(i)]++;
    }
    for (ll i = 1; i <= n; i++) {
        if (cnt[i] > 0) {
            families++;
            if (largest < cnt[i]) {
                largest = cnt[i];
            }
        }
    }

    cout << families << " " << largest << "\n";
    return 0;
}
