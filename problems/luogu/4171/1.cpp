/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-20 16:34:10
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205; // n <= 100, 节点数最多 200
const int MAXM = 2005; // m <= 1000

int n, m;
vector<int> adj[MAXN];

// Tarjan 变量
int dfn[MAXN], low[MAXN], scc[MAXN];
int timer, scc_cnt;
bool in_stack[MAXN];
stack<int> st;

// 初始化函数：处理多组数据时清空
void clear_data() {
    for (int i = 0; i < MAXN; ++i) {
        adj[i].clear();
    }
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(scc, 0, sizeof(scc));
    memset(in_stack, 0, sizeof(in_stack));
    while (!st.empty()) st.pop();
    timer = 0;
    scc_cnt = 0;
}

// 辅助函数：解析输入的字符串，返回节点编号
// 1..n 代表满式(Manchu)，n+1..2n 代表汉式(Han)
int parse_node(string s) {
    char type = s[0]; // 'm' or 'h'
    int idx = stoi(s.substr(1)); // 解析后面的数字
    
    if (type == 'm') {
        return idx; // 满式对应 1..n
    } else {
        return idx + n; // 汉式对应 n+1..2n
    }
}

// 取反函数
// 满式(i) -> 汉式(i+n)
// 汉式(i+n) -> 满式(i)
int _not(int u) {
    if (u > n) return u - n;
    return u + n;
}

void add_edge(int u, int v) {
    adj[u].push_back(v);
}

void tarjan(int u) {
    dfn[u] = low[u] = ++timer;
    st.push(u);
    in_stack[u] = true;

    for (int v : adj[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        scc_cnt++;
        while (true) {
            int v = st.top();
            st.pop();
            in_stack[v] = false;
            scc[v] = scc_cnt;
            if (u == v) break;
        }
    }
}

void solve() {
    cin >> n >> m;
    clear_data(); // 记得清空！

    for (int i = 0; i < m; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        
        int u = parse_node(s1);
        int v = parse_node(s2);

        // 逻辑：u OR v
        // 连边：!u -> v  AND  !v -> u
        add_edge(_not(u), v);
        add_edge(_not(v), u);
    }

    // 跑 Tarjan
    for (int i = 1; i <= 2 * n; ++i) {
        if (!dfn[i]) tarjan(i);
    }

    // 检查是否有解
    for (int i = 1; i <= n; ++i) {
        // 如果 满式i 和 汉式i 在同一个强连通分量，说明矛盾
        if (scc[i] == scc[i + n]) {
            cout << "BAD" << endl;
            return;
        }
    }

    cout << "GOOD" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int k;
    cin >> k;
    while (k--) {
        solve();
    }
    
    return 0;
}
