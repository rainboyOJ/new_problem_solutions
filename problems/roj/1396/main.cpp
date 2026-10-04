/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:40
 * update_at: 2026-10-05 00:40
 */
#include <bits/stdc++.h>
using namespace std;

// 病毒把全文做同一个小写字母置换：密文里字母的“明文序”就是各密文字母按明文从小到大排的顺序。
// 相邻词对只由首个不同字母决定大小关系，于是每条这样的字母对就是图上一条有向边。

const int MAXK = 50005;
const int SIGMA = 26;

typedef long long ll;

ll k;
string words[MAXK]; // 感染后的字典，按密文字典序给出
string target;      // 待还原的密文串

bool edge_exist[SIGMA][SIGMA]; // edge_exist[u][v]：密文字母 u 的明文必须排在 v 的明文之前
bool is_node[SIGMA];           // 只有当过“首个不同字母对”主角的字母才配当图结点
int indeg[SIGMA];              // 每个结点的当前入度
int order[SIGMA];              // 拓扑序：order[i] 是明文序中第 i 小的密文字母
int order_cnt;

priority_queue<int, vector<int>, greater<int> > ready; // 入度为 0 的结点，取最小编号只为让结果稳定

void read_input() {
    cin >> k;
    for (ll i = 1; i <= k; i++) {
        cin >> words[i];
    }
    cin >> target;
}

// 相邻两词首个不同位置给出 u 的字母 → v 的字母这一条约束。
bool add_pair_edge(const string &u, const string &v) {
    ll ulen = u.size();
    ll vlen = v.size();
    ll len = min(ulen, vlen);
    for (ll j = 0; j < len; j++) {
        if (u[j] != v[j]) {
            int a = u[j] - 'a';
            int b = v[j] - 'a';
            edge_exist[a][b] = true;
            is_node[a] = true;
            is_node[b] = true;
            return true;
        }
    }
    return false; // 两词完全相同，或一个是另一个的前缀：不提供任何字母大小关系
}

void build_graph() {
    for (ll i = 1; i + 1 <= k; i++) {
        if (words[i] == words[i + 1]) {
            continue; // 排列严格递增，重复词作废，避免凭空造出一条边
        }
        add_pair_edge(words[i], words[i + 1]);
    }

    bool has_node = false;
    for (int c = 0; c < SIGMA; c++) {
        if (is_node[c]) {
            has_node = true;
        }
    }
    if (!has_node) {
        // 一个相邻词对都挑不出字母：此时只有目标串里的字母能确定，按字母表顺序重编号即可
        ll target_len = target.size();
        for (ll i = 0; i < target_len; i++) {
            is_node[target[i] - 'a'] = true;
        }
    }

    for (int u = 0; u < SIGMA; u++) {
        for (int v = 0; v < SIGMA; v++) {
            if (edge_exist[u][v]) {
                indeg[v]++;
            }
        }
    }
    for (int c = 0; c < SIGMA; c++) {
        if (is_node[c] && indeg[c] == 0) {
            ready.push(c);
        }
    }
}

void solve() {
    build_graph();

    int node_cnt = 0; // 结点最多 26 个，用 int
    for (int c = 0; c < SIGMA; c++) {
        if (is_node[c]) {
            node_cnt++;
        }
    }

    bool unique = true;
    while (!ready.empty()) {
        int candidate_cnt = ready.size();
        if (candidate_cnt > 1) {
            unique = false; // 同一轮出现多个候选：把它们的先后对调仍是合法明文序
        }
        int u = ready.top();
        ready.pop();
        order[order_cnt] = u;
        order_cnt++;
        for (int v = 0; v < SIGMA; v++) {
            if (edge_exist[u][v]) {
                indeg[v]--;
                if (indeg[v] == 0) {
                    ready.push(v);
                }
            }
        }
    }

    if (order_cnt != node_cnt) {
        cout << 0 << "\n"; // 约束成环，字典自相矛盾
        return;
    }
    if (!unique) {
        cout << 0 << "\n"; // 字典给的信息不足，明文序不唯一
        return;
    }

    ll target_len = target.size();
    for (ll i = 0; i < target_len; i++) {
        if (!is_node[target[i] - 'a']) {
            cout << 0 << "\n"; // 目标串出现字典没约束过的字母
            return;
        }
    }

    // 明文序中第 i 小的密文字母，其明文就是 'a' + i，据此重编号翻译目标串
    char trans[SIGMA];
    for (int c = 0; c < SIGMA; c++) {
        trans[c] = 0;
    }
    for (int i = 0; i < order_cnt; i++) {
        trans[order[i]] = char('a' + i);
    }
    for (ll i = 0; i < target_len; i++) {
        cout << trans[target[i] - 'a'];
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
