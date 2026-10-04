/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:19
 * update_at: 2026-10-05 07:19
 */
// main.cpp：静态区间最大值（RMQ），ST 表（倍增）正解。
// 预处理 O(N log N)，每次询问 O(1)，满足 N <= 2e5、M <= 1e4 的规模。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int LOG = 18; // 2^18 > 2e5，层数够用

typedef long long ll;

int n, m;
ll a[MAXN];        // a[i]：第 i 个数（下标从 1 开始，与题面对应）
ll st[LOG][MAXN];  // st[k][i]：从 i 开始、长度为 2^k 的区间的最大值

// 预处理 ST 表：长度 2^k 的区间由两段长度 2^(k-1) 的区间拼成。
// max 有幂等性（重叠不影响结果），所以查询时允许两块区间重叠。
void build_st() {
    for (int i = 1; i <= n; i++) st[0][i] = a[i];
    for (int k = 1; (1 << k) <= n; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            st[k][i] = max(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
}

// 回答询问 [l, r] 的最大值：取两块长度 2^k 的区间覆盖 [l, r]。
// k = floor(log2(len))，两块起点分别是 l 和 r - 2^k + 1。
ll query_max(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++; // 求 floor(log2(len))，不用浮点
    return max(st[k][l], st[k][r - (1 << k) + 1]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;

    build_st();

    for (int i = 1; i <= m; i++) {
        int A, B;
        cin >> A >> B;
        cout << query_max(A, B) << "\n";
    }

    return 0;
}
