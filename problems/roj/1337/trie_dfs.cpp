/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-11 22:18
 * update_at: 2026-10-11 22:18
 */
/*
 * trie_dfs.cpp：【例3-2】单词查找树 的解法二 —— 先建字典树，再树上 DFS 统计
 *
 * 把单词列表逐个插进字典树：公共前缀只保留一份，走到头才开新结点，
 * 这样建出来的树正好满足「结点数最少」的条件。
 * 建完后从根出发 DFS 遍历整棵树，访问到的结点数（含根）就是答案。
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 40005; // 结点总数不会超过文件总长度 32K，留出余量
const int SIGMA = 26;   // 只有大写英文字母

struct TrieNode {
    int next[SIGMA]; // next[c] = 沿字符 ('A' + c) 往下的儿子编号，0 表示没有
};
TrieNode node[MAXN]; // 动态化静态：静态大数组当结点池，按编号引用
int node_cnt;        // 已经开出的结点数，根结点固定编号 1

// 动态开一个新结点，返回它的编号
int new_node() {
    node_cnt++;
    memset(node[node_cnt].next, 0, sizeof(node[node_cnt].next));
    return node_cnt;
}

// 插入一个单词：已经存在的前缀直接复用，走到头才开新结点
void insert(const string &word) {
    int u = 1;
    for (size_t i = 0; i < word.size(); i++) {
        int c = word[i] - 'A';
        if (node[u].next[c] == 0) {
            node[u].next[c] = new_node();
        }
        u = node[u].next[c];
    }
}

// 以 u 为根的子树共有多少个结点（含 u 自己）——树上 DFS 遍历
int dfs(int u) {
    int cnt = 1; // 先把自己数上
    for (int c = 0; c < SIGMA; c++) {
        int v = node[u].next[c];
        if (v != 0) {
            cnt += dfs(v); // 有儿子就往下走，每条存在的边恰好走一次
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    node_cnt = 0;
    new_node(); // 结点 1 = 根，根不含字母

    string word;
    while (cin >> word) {
        insert(word);
    }

    // DFS 返回值就是整棵树的结点数
    cout << dfs(1) << '\n';
    return 0;
}
