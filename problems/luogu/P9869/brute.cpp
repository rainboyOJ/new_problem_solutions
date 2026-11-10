/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:10
 * update_at: 2026-11-10 23:10
 */
// brute.cpp：小数据 3^n 暴力枚举所有初值赋值
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Statement {
    char op;
    int i, j;
};

int n, m;
vector<Statement> stmts;
int min_u;

// 0: F, 1: T, 2: U
int negate_val(int v) {
    if (v == 0) return 1;
    if (v == 1) return 0;
    return 2;
}

bool check(const vector<int>& init_val) {
    vector<int> cur = init_val;
    for (const auto& s : stmts) {
        if (s.op == 'T') cur[s.i] = 1;
        else if (s.op == 'F') cur[s.i] = 0;
        else if (s.op == 'U') cur[s.i] = 2;
        else if (s.op == '+') cur[s.i] = cur[s.j];
        else if (s.op == '-') cur[s.i] = negate_val(cur[s.j]);
    }

    for (int i = 1; i <= n; ++i) {
        if (cur[i] != init_val[i]) return false;
    }
    return true;
}

void dfs(int idx, int u_cnt, vector<int>& init_val) {
    if (u_cnt >= min_u) return; // 剪枝
    if (idx > n) {
        if (check(init_val)) {
            min_u = u_cnt;
        }
        return;
    }

    // 优先尝试 0 (F) 和 1 (T)，最后尝试 2 (U)
    init_val[idx] = 1;
    dfs(idx + 1, u_cnt, init_val);

    init_val[idx] = 0;
    dfs(idx + 1, u_cnt, init_val);

    init_val[idx] = 2;
    dfs(idx + 1, u_cnt + 1, init_val);
}

void solve() {
    cin >> n >> m;
    stmts.resize(m);
    for (int k = 0; k < m; ++k) {
        cin >> stmts[k].op;
        if (stmts[k].op == 'T' || stmts[k].op == 'F' || stmts[k].op == 'U') {
            cin >> stmts[k].i;
        } else {
            cin >> stmts[k].i >> stmts[k].j;
        }
    }

    min_u = n + 1;
    vector<int> init_val(n + 1, 0);
    dfs(1, 0, init_val);

    cout << min_u << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, t;
    if (cin >> c >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
