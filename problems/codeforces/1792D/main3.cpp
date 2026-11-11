#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NODES = 500000 + 50;
int ch[MAX_NODES][11];
int node_cnt = 0;

int new_node() {
    node_cnt++;
    for (int d = 1; d <= 10; ++d) {
        ch[node_cnt][d] = 0;
    }
    return node_cnt;
}

void insert_perm(const vector<int>& q, int m) {
    int u = 0;
    for (int k = 1; k <= m; ++k) {
        int d = q[k];
        if (!ch[u][d]) {
            ch[u][d] = new_node();
        }
        u = ch[u][d];
    }
}

int query_lcp(const vector<int>& p, int m) {
    int u = 0;
    int len = 0;
    for (int k = 1; k <= m; ++k) {
        int d = p[k];
        if (ch[u][d]) {
            len++;
            u = ch[u][d];
        } else {
            break;
        }
    }
    return len;
}

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    // 清空根节点
    node_cnt = 0;
    for (int d = 1; d <= 10; ++d) {
        ch[0][d] = 0;
    }

    vector<vector<int>> a(n, vector<int>(m + 1));
    for (int i = 0; i < n; ++i) {
        vector<int> q(m + 1);
        for (int k = 1; k <= m; ++k) {
            cin >> a[i][k];
            // 计算逆置换：数字 a[i][k] 位于位置 k
            q[a[i][k]] = k;
        }
        insert_perm(q, m);
    }

    for (int i = 0; i < n; ++i) {
        cout << query_lcp(a[i], m) << (i == n - 1 ? "" : " ");
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
