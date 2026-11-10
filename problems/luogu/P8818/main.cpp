/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 14:48
 * update_at: 2026-11-10 19:55
 */
// main.cpp：用极值对抗统一模型消除分类讨论。
// 小 L 的候选点至多 5 个：{max(A), min(A), 最小正数, 最大负数, 0}。
// 给定小 L 的选择 x，小 Q 必将得分压至 min(x * b_min, x * b_max)；
// 小 L 在区间真实存在的候选点中选择使该值最大的 x 即可。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;
const ll INF64 = (1LL << 62); // 哨兵值，表示"不存在"或比任何真实得分都小

int n, m, q;
ll a[MAXN]; // 数组 A
ll b[MAXN]; // 数组 B

int lg2_table[MAXN];   // lg2_table[i]：floor(log2(i))，ST 表查区间时用
int zero_prefix[MAXN]; // zero_prefix[i]：A[1..i] 中 0 的个数前缀和

ll st_a_max[18][MAXN];    // ST 表：A 区间最大值
ll st_a_min[18][MAXN];    // ST 表：A 区间最小值
ll st_a_posmin[18][MAXN]; // ST 表：A 区间最小正数，不存在时为 INF64
ll st_a_negmax[18][MAXN]; // ST 表：A 区间最大的负数（最接近 0），不存在时为 -INF64

ll st_b_max[18][MAXN]; // ST 表：B 区间最大值
ll st_b_min[18][MAXN]; // ST 表：B 区间最小值

// 查询 st 表区间 [l,r] 的最大值
ll query_max(ll st[18][MAXN], int l, int r) {
    int k = lg2_table[r - l + 1];
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

// 查询 st 表区间 [l,r] 的最小值
ll query_min(ll st[18][MAXN], int l, int r) {
    int k = lg2_table[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}

// 预处理 1..limit 的 log2 下取整表
void build_logs(int limit) {
    lg2_table[1] = 0;
    for (int i = 2; i <= limit; i++) {
        lg2_table[i] = lg2_table[i >> 1] + 1;
    }
}

// 预处理 A 的四张 ST 表和零个数前缀和
void build_st_a() {
    for (int i = 1; i <= n; i++) {
        st_a_max[0][i] = a[i];
        st_a_min[0][i] = a[i];
        st_a_posmin[0][i] = (a[i] > 0 ? a[i] : INF64);
        st_a_negmax[0][i] = (a[i] < 0 ? a[i] : -INF64);
        zero_prefix[i] = zero_prefix[i - 1] + (a[i] == 0);
    }

    for (int k = 1; (1 << k) <= n; k++) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; i++) {
            st_a_max[k][i] = max(st_a_max[k - 1][i], st_a_max[k - 1][i + half]);
            st_a_min[k][i] = min(st_a_min[k - 1][i], st_a_min[k - 1][i + half]);
            st_a_posmin[k][i] = min(st_a_posmin[k - 1][i], st_a_posmin[k - 1][i + half]);
            st_a_negmax[k][i] = max(st_a_negmax[k - 1][i], st_a_negmax[k - 1][i + half]);
        }
    }
}

// 预处理 B 的两张 ST 表
void build_st_b() {
    for (int i = 1; i <= m; i++) {
        st_b_max[0][i] = b[i];
        st_b_min[0][i] = b[i];
    }

    for (int k = 1; (1 << k) <= m; k++) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= m; i++) {
            st_b_max[k][i] = max(st_b_max[k - 1][i], st_b_max[k - 1][i + half]);
            st_b_min[k][i] = min(st_b_min[k - 1][i], st_b_min[k - 1][i + half]);
        }
    }
}

// 极值对抗单次查询：小 L 在候选点中选择使得小 Q 的最差应对得分最大的 x
ll query_game(int l1, int r1, int l2, int r2) {
    ll b_min = query_min(st_b_min, l2, r2), b_max = query_max(st_b_max, l2, r2);
    ll pos_min = query_min(st_a_posmin, l1, r1), neg_max = query_max(st_a_negmax, l1, r1);
    ll cands[5] = {query_max(st_a_max, l1, r1), query_min(st_a_min, l1, r1), pos_min, neg_max, 0};
    bool valid[5] = {true, true, pos_min != INF64, neg_max != -INF64, zero_prefix[r1] > zero_prefix[l1 - 1]};

    ll ans = -INF64;
    for (int i = 0; i < 5; i++) {
        if (valid[i]) ans = max(ans, min(cands[i] * b_min, cands[i] * b_max));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    build_logs(max(n, m));
    build_st_a();
    build_st_b();

    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << query_game(l1, r1, l2, r2) << '\n';
    }

    return 0;
}
