/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-10-09 19:59
 */
// main-stl.cpp：P3916 图的遍历（STL 写法）。
// 核心是反向建图：原图的 u -> v，在反图里存成 v -> u。
// 然后按编号从大到小枚举“候选最大编号”，在反图上染色，
// 第一次被染到的点，它的答案就是当前这个编号。
// 代码分层：读入 / 染色 / 输出各一个函数，main 只按顺序调用；
// 反图和答案这些核心数据放全局，函数之间共享。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m;                 // 点数、边数
vector<vector<int>> rg;  // rg[v]：反图中 v 能一步走到的所有点（即原图中能走到 v 的点）
vector<int> ans;         // ans[u]：从 u 出发能到达的最大编号，0 表示还没染色

// 读入 n、m 和 m 条边，顺便就把反图建好
void read_input() {
    cin >> n >> m;

    rg.assign(n + 1, vector<int>());
    ans.assign(n + 1, 0);
    for (ll i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        rg[v].push_back(u); // 反向建边：v 连回 u
    }
}

// 从 start 出发，在反图上把能走到的点都染成 marker
// 用显式栈代替递归，避免 n = 1e5 的长链把递归栈压爆
void color(int start, int marker) {
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (ans[u] != 0) {
            continue; // 这个点被更大的编号先染过了，答案已经确定
        }
        ans[u] = marker;

        ll deg = rg[u].size();
        for (ll i = 0; i < deg; i++) {
            int v = rg[u][i];
            if (ans[v] == 0) {
                st.push(v);
            }
        }
    }
}

// 编号从大到小枚举，先被染到的答案最大
void solve() {
    for (ll marker = n; marker >= 1; marker--) {
        if (ans[marker] == 0) { // 还没确定答案，才需要从它开始染色
            color((int)marker, (int)marker);
        }
    }
}

// 按编号 1..n 输出每个点的答案
void output() {
    for (ll i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();
    output();

    return 0;
}
