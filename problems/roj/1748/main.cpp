/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:02
 * update_at: 2026-10-07 21:02
 */

// 一本通 1748《大数计数》
// 题意：长度为 n 的大数 S_1..S_n，S_1 是最高位所以不能为 0；
//       给出 m 条限制 (l1,r1,l2,r2)，要求子串 S[l1..r1] 与 S[l2..r2] 完全相同；
//       求满足全部限制的 n 位数个数，模 1e9+7。
//
// 模型：把 n 个位置看成 n 个变量，每条限制等价于"对应位置两两相等"，
//       于是用并查集维护位置的相等关系；设最终连通块数为 t，
//       最高位所在块只能取 1..9，其余每块取 0..9，答案 = 9 * 10^(t-1)。
//
// 瓶颈：朴素地逐位合并，一条长为 L 的限制要 O(L) 次合并，总代价 O(nm)。
// 破法：倍增（ST 表思想）+ 并查集。第 k 层并查集刻画"以 i 开头、长度 2^k
//       的区间"之间的相等关系。一条长为 L 的限制取 k = floor(log2 L)，
//       用两段长度 2^k 的重叠区间把 [l1,r1] 与 [l2,r2] 各自盖满，等价性不变。
//       最后自顶向下把高层关系下放到低两层（逆用 ST 表），
//       统计第 0 层连通块数即可。
//
// 复杂度 O((n+m) log n α(n))，空间 O(n log n)。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;  // n 的上限
const int LOG = 18;       // 2^17 = 131072 > 1e5，层号 0..17 足够
const int MOD = 1000000007;

typedef long long ll;

// 一层并查集：第 k 层上的元素是区间 [i, i + 2^k - 1]，i 取 1..n-2^k+1
struct Layer {
    int fa[MAXN];  // fa[i]：区间 [i, i+2^k-1] 的代表元
    int sz[MAXN];  // 按大小合并时的连通块大小
};

Layer layer[LOG];  // layer[k] 就是第 k 层
int pw[LOG];       // pw[k] = 2^k

ll n, m;
int max_log;  // floor(log2 n)，实际用到的最高层号

// 第 k 层上找 x 的代表元（迭代路径压缩，避免递归过深）
int find_layer(int k, int x) {
    int root = x;
    while (layer[k].fa[root] != root) {
        root = layer[k].fa[root];
    }
    while (layer[k].fa[x] != root) {
        int nxt = layer[k].fa[x];
        layer[k].fa[x] = root;
        x = nxt;
    }
    return root;
}

// 第 k 层上合并两个区间，按大小启发式
void unite_layer(int k, int a, int b) {
    a = find_layer(k, a);
    b = find_layer(k, b);
    if (a == b) {
        return;
    }
    if (layer[k].sz[a] < layer[k].sz[b]) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    layer[k].fa[b] = a;
    layer[k].sz[a] += layer[k].sz[b];
}

void read_input() {
    cin >> n >> m;
}

void solve() {
    pw[0] = 1;
    for (int k = 1; k < LOG; k++) {
        pw[k] = pw[k - 1] << 1;
    }

    max_log = 0;
    while (max_log + 1 < LOG && pw[max_log + 1] <= n) {
        max_log++;
    }

    // 每层初始化：区间自己成一个集合
    for (int k = 0; k <= max_log; k++) {
        for (int i = 1; i <= n; i++) {
            layer[k].fa[i] = i;
            layer[k].sz[i] = 1;
        }
    }

    // 加入限制：k = floor(log2 L)，用两段 2^k 区间盖住整段，等价性不变
    for (ll q = 1; q <= m; q++) {
        ll l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        int len = r1 - l1 + 1;
        int k = 0;
        while (pw[k + 1] <= len) {
            k++;
        }
        unite_layer(k, l1, l2);
        unite_layer(k, r1 - pw[k] + 1, r2 - pw[k] + 1);
    }

    // 逆用 ST 表：自顶向下把"两个 2^k 区间相等"拆成两个"2^(k-1) 区间相等"
    for (int k = max_log; k >= 1; k--) {
        int half = pw[k - 1];
        for (ll i = 1; i + pw[k] - 1 <= n; i++) {
            int p = find_layer(k, i);
            if (p == i) {
                continue;  // 自己就是代表元，下放没有信息可传
            }
            unite_layer(k - 1, i, p);
            unite_layer(k - 1, i + half, p + half);
        }
    }

    // 统计第 0 层（一个个位置）的连通块数
    ll blocks = 0;
    for (ll i = 1; i <= n; i++) {
        if (find_layer(0, i) == i) {
            blocks++;
        }
    }

    ll ans = 9;  // 最高位所在块：1..9
    for (ll i = 1; i < blocks; i++) {
        ans = ans * 10 % MOD;  // 其余每块：0..9
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
