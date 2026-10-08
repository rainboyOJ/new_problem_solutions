/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 10:05
 * update_at: 2026-10-08 10:25
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

// 3058《双栈排序》：冲突图 + 二分染色 + 贪心模拟（a < b < c < d）。
//
// ⚠ 输入是多组数据：第一行 T，随后 T 组，每组一行 n、一行 n 个数的排列。
//   题库题面的「输入格式」一节只写了「第一行是一个整数 n」，漏了 T —— 以数据为准。

static string solve_one(int n, const vector<int>& p) {
    // 后缀最小值
    vector<int> min_val(n + 2, 1e9);
    for (int i = n; i >= 1; i--) min_val[i] = min(min_val[i + 1], p[i]);

    // 冲突图：i < j、P_i < P_j、且 j 之后还有比 P_i 小的
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (p[i] < p[j] && min_val[j + 1] < p[i]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    // 二分图染色：每个连通块里下标最小的点染 1（S1），使 'a' 尽量靠前
    vector<int> color(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (color[i]) continue;
        color[i] = 1;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (color[v]) {
                    if (color[v] == color[u]) return "0";   // 非二分图
                } else {
                    color[v] = 3 - color[u];
                    q.push(v);
                }
            }
        }
    }

    // 贪心模拟：按 a < b < c < d 尝试；压栈需保持栈内自底向上递减
    stack<int> s1, s2;
    int expected = 1, ptr = 1;
    vector<char> ops;
    while (expected <= n) {
        if (ptr <= n && color[ptr] == 1 && (s1.empty() || s1.top() > p[ptr])) {
            s1.push(p[ptr]); ops.push_back('a'); ptr++;
        } else if (!s1.empty() && s1.top() == expected) {
            s1.pop(); ops.push_back('b'); expected++;
        } else if (ptr <= n && color[ptr] == 2 && (s2.empty() || s2.top() > p[ptr])) {
            s2.push(p[ptr]); ops.push_back('c'); ptr++;
        } else if (!s2.empty() && s2.top() == expected) {
            s2.pop(); ops.push_back('d'); expected++;
        } else {
            return "0";   // 理论上不可达
        }
    }

    string out;
    for (size_t i = 0; i < ops.size(); i++) {
        if (i) out += ' ';
        out += ops[i];
    }
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;
    for (int tc = 0; tc < T; tc++) {
        int n;
        if (!(cin >> n)) break;
        vector<int> p(n + 1);
        for (int i = 1; i <= n; i++) cin >> p[i];
        cout << solve_one(n, p) << "\n";
    }
    return 0;
}
