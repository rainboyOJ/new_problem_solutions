/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 09:22
 * update_at: 2026-11-12 09:35
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 50000 + 50;
vector<int> a[maxn];        // 原排列序列
vector<int> q[maxn];        // 逆置换序列
vector<int> sorted_q[maxn]; // 排序后的逆置换序列

// 计算两个排列的最长公共前缀 (LCP)
int get_lcp(const vector<int>& u, const vector<int>& v, int m) {
    int len = 0;
    while (len < m && u[len] == v[len]) {
        len++;
    }
    return len;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    for (int i = 0; i < n; ++i) {
        a[i].resize(m);
        q[i].resize(m);
        for (int k = 0; k < m; ++k) {
            cin >> a[i][k];
            // 0-based 下标与数值
            a[i][k]--;
            // a[i][k] 这个数字在第 k 个位置
            q[i][a[i][k]] = k;
        }
        sorted_q[i] = q[i];
    }

    // 按字典序对所有逆置换从小到大排序
    sort(sorted_q, sorted_q + n);

    // 核心性质：在字典序有序序列中，与目标序列拥有最长公共前缀 (LCP) 的元素必然紧挨在二分插入点两侧
    // 逐个二分查找 a[i] 的前驱与后继
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(sorted_q, sorted_q + n, a[i]);
        int idx = it - sorted_q;
        int max_lcp = 0;

        // 检查后继（包含完全相等的情形）
        if (idx < n) {
            max_lcp = max(max_lcp, get_lcp(a[i], sorted_q[idx], m));
        }
        // 检查前驱
        if (idx > 0) {
            max_lcp = max(max_lcp, get_lcp(a[i], sorted_q[idx - 1], m));
        }

        cout << max_lcp << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
