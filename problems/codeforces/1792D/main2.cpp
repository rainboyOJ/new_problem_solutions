#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> q(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < m; ++k) {
            cin >> a[i][k];
            // 0-based 下标与数值
            a[i][k]--;
            // a[i][k] 这个数字在第 k 个位置
            q[i][a[i][k]] = k;
        }
    }

    // 复制一份逆置换集合并按字典序从小到大排序
    vector<vector<int>> sorted_q = q;
    sort(sorted_q.begin(), sorted_q.end());

    // 逐个二分查找 a[i] 的前驱与后继
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(sorted_q.begin(), sorted_q.end(), a[i]);
        int max_lcp = 0;

        // 检查后继（包含完全相等的情形）
        if (it != sorted_q.end()) {
            max_lcp = max(max_lcp, get_lcp(a[i], *it, m));
        }
        // 检查前驱
        if (it != sorted_q.begin()) {
            max_lcp = max(max_lcp, get_lcp(a[i], *prev(it), m));
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
