/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:58
 * update_at: 2026-10-05 08:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXV = 100005;

typedef long long ll;

ll n;
ll a[MAXN];          // 输入序列（值域 ≤ 1e5，存 ll 与答案类型一致）
int bit[MAXV];       // 树状数组：bit[v] 记录值 v 已经出现过几次

// 单点加：名次 i 处 +delta，沿 lowbit 路径向上传播。
void bit_add(int i, int delta) {
    while (i <= MAXV - 1) {
        bit[i] += delta;
        i += i & -i;
    }
}

// 前缀和查询：[1..i] 上的累计次数，沿 lowbit 路径向下收敛。
int bit_sum(int i) {
    int s = 0;
    while (i > 0) {
        s += bit[i];
        i -= i & -i;
    }
    return s;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

// 思路：把「两两比较」改写成「对每个 a_j 统计左边比它大的个数」。
// 用树状数组维护左侧元素的权值桶；查询 (值 ≤ a_j 的个数) 后再插入 a_j。
// 由于 a_i ≤ 1e5，桶直接开 1e5 即可，无需额外离散化。
void solve() {
    ll total = 0;
    for (ll k = 1; k <= n; k++) {
        ll x = a[k];
        // 已经插进桶里的元素总数 = k - 1（按插入顺序计数）。
        // bit_sum(x) 返回桶里「值 ≤ x」的个数。
        // 二者之差就是「左边比 x 大」的逆序对增量。
        ll seen = k - 1;
        ll le = bit_sum((int)x);
        total += seen - le;

        bit_add((int)x, 1);
    }
    cout << total << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}