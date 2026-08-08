/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-23 17:48
 *
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

// 插入单词 s，返回以 s 结尾的最长词链长度
int insert_word(const string &s) {
    int u = 1;
    int chain = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[u][c] == 0) {
            trie[u][c] = get_new_node();
        }
        u = trie[u][c];
        // 沿途遇到的 is_end 标记都是 s 的前缀
        if (is_end[u]) {
            ++chain;
        }
    }
    // 标记 s 自己为单词结尾
    is_end[u] = true;
    ++chain; // 加上自己
    return chain;
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
        ans = max(ans, insert_word(s));
    }

    cout << ans << '\n';
    return 0;
}
