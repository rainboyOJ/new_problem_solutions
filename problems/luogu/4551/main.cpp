/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* P4551 最长异或路径 */
/* 核心：路径异或 = 两个根前缀异或的异或（根→lca 公共段异或两次抵消）；
 * 最大异或对用 01-Trie 逐位贪心：高位支配低位，每层优先走相反位。
 * 01-Trie 直接复用 rbook 文章《Trie 字典树》的模板（ALPHA=2, OFFSET='0'），
 * 把每个数转成 31 位 0/1 字符串插入；最大异或查询写在模板外部。 */

#include <bits/stdc++.h>
using namespace std;

// 字典树 Trie 模板：插入字符串、判断是否存在、统计前缀出现次数
// 模板参数：ALPHA 字符集大小，OFFSET 字符起点（如 'a'）
// 节点维护 pass(经过次数) 和 end(单词结尾次数)
// 用法：Trie<26,'a'> tr; tr.insert("abc"); tr.contains("abc"); tr.count_prefix("ab");
template <int ALPHA = 26, char OFFSET = 'a'>
struct Trie {
    struct Node {
        array<int, ALPHA> ch{}; // ch[c] 子节点编号，0 为空（根也是 0）
        int pass = 0;           // 经过该节点的字符串个数
        int end = 0;            // 以该节点结尾的完整字符串个数
    };

    vector<Node> tree;          // tree[0] 为根

    Trie() { tree.push_back(Node()); }

    // 插入 s
    void insert(const string &s) {
        int u = 0;
        tree[u].pass++;
        for (char cc : s) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) {       // 无子节点则新建
                tree[u].ch[c] = (int)tree.size();
                tree.push_back(Node());
            }
            u = tree[u].ch[c];
            tree[u].pass++;
        }
        tree[u].end++;
    }

    // 判断 s 是否完整插入过
    bool contains(const string &s) const {
        int u = 0;
        for (char cc : s) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) return false;
            u = tree[u].ch[c];
        }
        return tree[u].end > 0;  // 必须作为完整单词结尾
    }

    // 统计以 prefix 为前缀的字符串个数
    int count_prefix(const string &prefix) const {
        int u = 0;
        for (char cc : prefix) {
            int c = cc - OFFSET;
            if (tree[u].ch[c] == 0) return 0;
            u = tree[u].ch[c];
        }
        return tree[u].pass;
    }
};

const int MAXN = 100000 + 5;

int n;                                  // 节点数
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;
unsigned int weight_edge[MAXN * 2];     // 边权 < 2^31
unsigned int xor_root[MAXN];            // xor_root[u] = 根到 u 的边权异或

Trie<2, '0'> trie;                      // 01-Trie：字符集只有 {0,1}

// 把 x 转成 31 位 0/1 字符串（第 30 位到第 0 位），供模板 insert 使用
string to_binary(unsigned int x) {
    string s;
    for (int bit = 30; bit >= 0; bit--)
        s.push_back(((x >> bit) & 1U) ? '1' : '0');
    return s;
}

// 查询与 x 异或最大的值，返回最大异或值（模板不含此功能，写在外部）
// 贪心：每层优先走相反位（x 这位是 0 就找 1），走不到才走同一位
unsigned int max_xor(unsigned int x) {
    int u = 0;
    unsigned int answer = 0;
    for (int bit = 30; bit >= 0; bit--) {
        int c = (x >> bit) & 1U;
        int want = c ^ 1;
        if (trie.tree[u].ch[want]) {         // 相反位存在：这一位异或得 1
            answer |= 1U << bit;
            u = trie.tree[u].ch[want];
        } else {                             // 不存在：退而求其次走同一位
            u = trie.tree[u].ch[c];
        }
    }
    return answer;
}

void add_edge(int u, int v, unsigned int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    weight_edge[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        unsigned int w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
}

// BFS 求每个节点的根前缀异或 xor_root[u]
void calc_xor_values() {
    queue<int> que;
    vector<int> parent(n + 1, 0);
    que.push(1);
    parent[1] = -1;
    xor_root[1] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            xor_root[v] = xor_root[u] ^ weight_edge[i];
            que.push(v);
        }
    }
}

void solve() {
    calc_xor_values();

    // 先插入根的前缀 0：这样"单点路径"（u 到根的路径 = pre[u]^0）也被计入，
    // 同时 0 的全零路径保证 max_xor 的兜底分支永远走得到。
    unsigned int answer = 0;
    trie.insert(to_binary(xor_root[1]));
    for (int i = 2; i <= n; i++) {
        answer = max(answer, max_xor(xor_root[i]));
        trie.insert(to_binary(xor_root[i]));
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
