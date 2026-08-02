/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* P2922 [USACO08DEC] Secret Message G */
/* 把消息插入 Trie，暗号匹配 = 暗号是消息的前缀 或 消息是暗号的前缀。 */
/* 答案 = 暗号路径上所有节点的 end 之和 + 最终节点的 pass - 最终节点的 end（暗号自身被重复计数）。 */

#include <bits/stdc++.h>
using namespace std;

// 字典树 Trie 模板（来自 rbook 文章 trie）：
// 节点维护 pass(经过次数) 和 end(单词结尾次数)
// 本题字符集为 {0, 1}，所以 ALPHA=2，OFFSET='0'
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
};

int m, n;          // m 条消息，n 条暗号
Trie<2, '0'> trie; // 01 字典树，存放所有消息

// 查询暗号 s 能匹配多少条消息：
// 匹配条件 = 一个是另一个的前缀（前缀长度取较小者）。
int query(const string &s) {
    int u = 0;
    int ans = 0; // 路径上节点 end 的累加：这些消息是暗号 s 的前缀（含 s 本身）
    for (char cc : s) {
        int c = cc - '0';
        u = trie.tree[u].ch[c];
        if (u == 0) return ans; // 暗号走不到底：之后的节点不存在，
                                // 已累加的 end 就是全部匹配（消息是暗号的前缀）
        ans += trie.tree[u].end;
    }
    // 暗号完整存在于 Trie 中：
    // 还要加上"经过最终节点的消息数"（暗号是消息的前缀），
    // 但等于暗号本身的消息在 pass 和 end 中各计了一次，需要减去 end。
    return ans + trie.tree[u].pass - trie.tree[u].end;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 1; i <= m; ++i) {
        int b;
        cin >> b;
        string s;
        for (int j = 1; j <= b; ++j) {
            int bit;
            cin >> bit;
            s.push_back('0' + bit);
        }
        trie.insert(s);
    }

    for (int i = 1; i <= n; ++i) {
        int c;
        cin >> c;
        string s;
        for (int j = 1; j <= c; ++j) {
            int bit;
            cin >> bit;
            s.push_back('0' + bit);
        }
        cout << query(s) << '\n';
    }

    return 0;
}
