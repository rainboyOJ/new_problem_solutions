/**
 * 魔族密码 - Trie 解法
 *
 * 每插入一个单词，沿 Trie 往下走时统计路径上遇到了几个
 * 已标记为单词结尾的节点（即当前单词的前缀）。
 * 链长 = 路径上遇到的前缀数 + 1（自己）。
 * 在所有链长中取最大值。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 150000 + 5;
int trie[MAXN][26];
bool is_end[MAXN]; // 标记节点是否为某个单词的结尾
int node_cnt = 1;  // 根节点编号为 1

int get_new_node() {
    ++node_cnt;
    return node_cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ans = 0;

    for (int i = 1; i <= n; ++i) {
        string s;
        cin >> s;

        int u = 1;         // 从根节点开始走
        int chain = 0;     // 当前路径上遇到的前缀数

        for (char ch : s) {
            int c = ch - 'a';
            if (trie[u][c] == 0) {
                trie[u][c] = get_new_node();
            }
            u = trie[u][c];
            // 如果这个节点是某个已插入单词的结尾，说明该单词是 s 的前缀
            if (is_end[u]) {
                ++chain;
            }
        }

        // 当前单词自己也要算进链长
        is_end[u] = true;
        ++chain;

        ans = max(ans, chain);
    }

    cout << ans << '\n';
    return 0;
}
