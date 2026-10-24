/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:09
 * update_at: 2026-10-24 00:50
 */
// brute.cpp：小数据暴力解，用来理解题意并和 main.cpp 对拍。
// 做法：枚举第一步删掉的边 b，把剩下的 n 个顶点、n-1 条边展开成一条链，
// 然后枚举这条链上所有合并顺序（每步任选一对相邻顶点合并），取叶子处的最大值。
// 复杂度 O(n!)，只适合 n <= 8 的小数据。
// 实现上每层递归都按值传一个「当前链」的副本，不做回溯恢复，避免下标写错。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 64;

int n;
int v[maxn];    // v[i]：第 i 个顶点（输入第 i 组里的那个数），1..n
char op[maxn];  // op[i]：第 i 条边（输入第 i 组里的那个运算符），1..n

ll best_score;          // 目前找到的最高分
vector<int> best_edges; // 能达到最高分的所有第一步删除边（递增、去重）

// 链：pr_v[p] 是链上第 p 个顶点的权值，pr_op[p] 是链上第 p 与 p+1 个顶点之间的运算符
// 用 vector 按值传递，递归里各层互不影响
ll dfs(vector<int> pr_v, vector<char> pr_op) {
    if (pr_v.size() == 1) return pr_v[0];
    ll best = LLONG_MIN;
    for (int p = 0; p + 1 < (int)pr_v.size(); p++) {
        vector<int> nv(pr_v);
        vector<char> no(pr_op);
        ll val = (no[p] == 'x') ? (ll)nv[p] * nv[p + 1] : (ll)nv[p] + nv[p + 1];
        nv[p] = (int)val;
        nv.erase(nv.begin() + p + 1);
        no.erase(no.begin() + p);
        best = max(best, dfs(nv, no));
    }
    return best;
}

// 删除第 break_id 条边，把环展开成链，然后枚举该链的全部合并顺序，返回最高分
ll solve_break(int break_id) {
    // 链上第 p 个顶点 = 输入第 (break_id+p-1) mod n + 1 号顶点，
    // 链上第 p 条边   = 输入第 (break_id+p-1) mod n + 1 号边（依次 op[break_id+1], ...）
    // 与 main.cpp 的 build_chain 完全一致
    vector<int> pr_v;
    vector<char> pr_op;
    for (int p = 0; p < n; p++) {
        int id = (break_id - 1 + p) % n + 1;
        pr_v.push_back(v[id]);
        if (p < n - 1) {
            int eid = (break_id + p) % n + 1;   // 链上第 1 条边是 op[break_id+1]
            pr_op.push_back(op[eid]);
        }
    }
    return dfs(pr_v, pr_op);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> op[i] >> v[i];

    best_score = LLONG_MIN;
    for (int b = 1; b <= n; b++) {
        ll cur = solve_break(b);
        if (cur > best_score) {
            best_score = cur;
            best_edges.clear();
            best_edges.push_back(b);
        } else if (cur == best_score) {
            best_edges.push_back(b);
        }
    }

    cout << best_score << "\n";
    for (int i = 0; i < (int)best_edges.size(); i++) {
        if (i) cout << " ";
        cout << best_edges[i];
    }
    cout << "\n";
    return 0;
}
