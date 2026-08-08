#include <bits/stdc++.h>
using namespace std;

const int MAXNODE = 3200005;

int head[MAXNODE];       // head[u] 表示节点 u 的第一条出边
int to[MAXNODE];         // 边的终点
int nxt[MAXNODE];        // 邻接表下一条边
unsigned char ch[MAXNODE]; // 这条边对应哪个字符编号
int cnt[MAXNODE];        // 经过这个节点的模式串数量

int node_cnt = 0;
int edge_cnt = 0;

int new_node() {
    ++node_cnt;
    return node_cnt;
}

// 把字符映射到 0..61
int trans(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    return c - 'a' + 36;
}

// 在节点 u 的所有出边里寻找字符 code 对应的儿子。
int find_child(int u, int code) {
    for (int i = head[u]; i != 0; i = nxt[i]) {
        if ((int) ch[i] == code) {
            return to[i];
        }
    }
    return 0;
}

int add_child(int u, int code) {
    int v = new_node();
    ++edge_cnt;
    to[edge_cnt] = v;
    ch[edge_cnt] = (unsigned char) code;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    return v;
}

void insert_string(int root, const string &s) {
    int p = root;
    for (int i = 0; i < (int) s.size(); i++) {
        int code = trans(s[i]);
        int v = find_child(p, code);
        if (v == 0) {
            v = add_child(p, code);
        }
        p = v;
        cnt[p]++; // 经过这个节点的字符串数量，也就是这个前缀的出现次数
    }
}

int query_prefix_count(int root, const string &s) {
    int p = root;
    for (int i = 0; i < (int) s.size(); i++) {
        int code = trans(s[i]);
        p = find_child(p, code);
        if (p == 0) {
            return 0;
        }
    }
    return cnt[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, q;
        cin >> n >> q;

        int root = new_node();

        for (int i = 1; i <= n; i++) {
            string s;
            cin >> s;
            insert_string(root, s);
        }

        for (int i = 1; i <= q; i++) {
            string s;
            cin >> s;
            cout << query_prefix_count(root, s) << '\n';
        }
    }

    return 0;
}
