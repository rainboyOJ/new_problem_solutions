/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:36
 * update_at: 2026-10-01 22:36
 */
// main.cpp：把每个前缀消除后的栈状态存成 trie 结点，用“同一状态出现次数”统计可消除子串。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2000005;   // n <= 2e6

int n;
string s;

// 每个结点代表一个“消除栈状态”，结点 0 表示空栈。
// parent_node[u]：状态 u 去掉栈顶字符之后的状态；
// node_char[u]：状态 u 的栈顶字符（只有非根结点才有意义）。
int parent_node[MAXN];
char node_char[MAXN];

// 孩子用链式前向星存：一个状态最多有 26 个孩子（追加不同字符各一个）。
int first_edge[MAXN], to_node[MAXN], next_edge[MAXN];
int node_cnt, edge_cnt;

ll seen_count[MAXN];   // seen_count[u]：状态 u 作为前缀消除结果出现过的次数

// 在状态 u 后追加字符 c 得到的状态；已经存在就复用，避免重复建结点。
int get_child(int u, char c) {
    for (int e = first_edge[u]; e != 0; e = next_edge[e]) {
        int v = to_node[e];
        if (node_char[v] == c) {
            return v;
        }
    }

    node_cnt++;
    parent_node[node_cnt] = u;
    node_char[node_cnt] = c;

    edge_cnt++;
    to_node[edge_cnt] = node_cnt;
    next_edge[edge_cnt] = first_edge[u];
    first_edge[u] = edge_cnt;

    return node_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    ll answer = 0;
    int cur = 0;       // 当前前缀消除后的状态，0 表示空栈
    seen_count[0] = 1; // 空前缀是一个合法起点

    for (int i = 0; i < n; i++) {
        char c = s[i];

        if (cur != 0 && node_char[cur] == c) {
            // 栈顶字符和新字符相同，两者一起消去，状态退到父亲。
            cur = parent_node[cur];
        } else {
            // 否则把新字符压栈，得到一个新状态。
            cur = get_child(cur, c);
        }

        // 子串 (j, i] 可完全消除，当且仅当前缀 j 与前缀 i 的消除状态相同。
        answer += seen_count[cur];
        seen_count[cur]++;
    }

    cout << answer << '\n';
    return 0;
}
