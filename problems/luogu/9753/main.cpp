// main.cpp：把每个前缀消除后的栈状态放入 trie，统计相同状态出现次数。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2000005;

int n;
string s;

int parent_node[MAXN];      // trie 中每个状态的父状态
int first_edge[MAXN];       // 状态向后追加一个字符后的转移链表
int to_node[MAXN], next_edge[MAXN];
char node_char[MAXN], edge_char[MAXN];
long long seen_count[MAXN]; // 每个消除后状态已经出现过多少次
int node_cnt, edge_cnt;

int get_child(int u, char c) {
    for (int e = first_edge[u]; e != 0; e = next_edge[e]) {
        if (edge_char[e] == c) {
            return to_node[e];
        }
    }

    node_cnt++;
    parent_node[node_cnt] = u;
    node_char[node_cnt] = c;

    edge_cnt++;
    to_node[edge_cnt] = node_cnt;
    edge_char[edge_cnt] = c;
    next_edge[edge_cnt] = first_edge[u];
    first_edge[u] = edge_cnt;

    return node_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    long long answer = 0;
    int cur = 0;       // 当前前缀消除后的栈状态，0 表示空栈
    seen_count[0] = 1; // 空前缀出现一次

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (cur != 0 && node_char[cur] == c) {
            // 新字符和栈顶相同，二者可以一起消去。
            cur = parent_node[cur];
        } else {
            // 否则把这个字符压入消除栈。
            cur = get_child(cur, c);
        }

        answer += seen_count[cur];
        seen_count[cur]++;
    }

    cout << answer << '\n';
    return 0;
}
