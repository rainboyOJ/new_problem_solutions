/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05
 * update_at: 2026-08-05
 */
// 前缀和 + ST 表 RMQ + 堆：每次弹出当前最大子段和，分裂区间后补入次大。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int LOG = 20;

int n, k, L, R;
long long S[MAXN];          // 前缀和
int st[MAXN][LOG];          // ST 表存下标
int lg[MAXN];               // 预处理 log

void build_st() {
    for (int i = 1; i <= n; i++) st[i][0] = i;
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            int a = st[i][j - 1];
            int b = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (S[a] >= S[b]) ? a : b;
        }
}

// 返回 [l, r] 中 S 值最大的下标
int query(int l, int r) {
    int j = lg[r - l + 1];
    int a = st[l][j], b = st[r - (1 << j) + 1][j];
    return (S[a] >= S[b]) ? a : b;
}

struct Node {
    long long sum;  // 该区间的最优和
    int i;          // 起始位置
    int j;          // 最优结束位置
    int l, r;       // 当前区间 [l, r]
    bool operator<(const Node& o) const { return sum < o.sum; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> L >> R;
    S[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> S[i];
        S[i] += S[i - 1];
    }

    // 预处理 log
    lg[1] = 0;
    for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;

    build_st();

    // 大根堆：每个起始位置维护一个最优区间
    priority_queue<Node> pq;
    for (int i = 1; i <= n; i++) {
        int l = i + L - 1;
        int r = min(i + R - 1, n);
        if (l > r) continue;
        int j = query(l, r);
        pq.push({S[j] - S[i - 1], i, j, l, r});
    }

    long long ans = 0;
    for (int t = 0; t < k; t++) {
        auto [sum, i, j, l, r] = pq.top();
        pq.pop();
        ans += sum;

        // 分裂：左半 [l, j-1]
        if (l < j) {
            int jj = query(l, j - 1);
            pq.push({S[jj] - S[i - 1], i, jj, l, j - 1});
        }
        // 分裂：右半 [j+1, r]
        if (j < r) {
            int jj = query(j + 1, r);
            pq.push({S[jj] - S[i - 1], i, jj, j + 1, r});
        }
    }

    cout << ans << "\n";
    return 0;
}
