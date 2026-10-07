/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 06:41
 * update_at: 2026-10-08 06:41
 */

// 1819《字符串游戏》：把「轮流在末尾加字符、只能保持是某个串的前缀」看成在 Trie 上走一条根到叶的路径，
// 于是单轮就是一个「走到叶子的人赢（走不动的人输）」的无环博弈。
// 多轮的关键是：某一轮的输家成为下一轮的先手，所以「能不能故意输」和「能不能赢」一样重要。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int SIGMA = 26;       // 字符集只有小写字母
const int MAXNODE = 100005; // 每组数据「所有串长度之和」≤ 1e5，Trie 节点数 ≤ 总和 + 1

struct Node {
    int ch[SIGMA]; // 子节点编号，-1 表示这条转移不存在
    bool can_win;  // 轮到 u 处行棋的人，能否强行赢下本轮
    bool can_lose; // 轮到 u 处行棋的人，能否强行输掉本轮（即主动把先手权让给对方）
};

Node trie_node[MAXNODE]; // 动态化静态：trie_node[u] 就是编号 u 的节点，0 号是根（空串）
int node_cnt;            // 已开出的节点数（根算第 0 个）

int order[MAXNODE];     // 先序遍历序列（父一定排在子之前），逆序就是自底向上的处理顺序
int stack_buf[MAXNODE]; // 手写栈，避免 1e5 深链时递归爆栈

// 清空 Trie，只留下代表空串的根节点
void trie_init() {
    node_cnt = 0;
    trie_node[0].can_win = false;
    trie_node[0].can_lose = false;
    for (int c = 0; c < SIGMA; c++) trie_node[0].ch[c] = -1;
}

// 新开一个 Trie 节点（动态开点），返回它的编号
int new_node() {
    node_cnt++;
    trie_node[node_cnt].can_win = false;
    trie_node[node_cnt].can_lose = false;
    for (int c = 0; c < SIGMA; c++) trie_node[node_cnt].ch[c] = -1;
    return node_cnt;
}

// 把一个字符串插入 Trie
void trie_insert(const string &s) {
    int cur = 0;
    for (char c : s) {
        int x = c - 'a';
        if (trie_node[cur].ch[x] == -1) trie_node[cur].ch[x] = new_node();
        cur = trie_node[cur].ch[x];
    }
}

// 自底向上算出每个节点的 can_win / can_lose，结果留在全局的 trie_node 里
void dfs_dp() {
    // 迭代式先序遍历：先把父压进序列，再压子，保证父一定先于子出现
    int top = 0, cnt = 0;
    stack_buf[top++] = 0;
    while (top > 0) {
        int u = stack_buf[--top];
        order[cnt++] = u;
        for (int c = 0; c < SIGMA; c++)
            if (trie_node[u].ch[c] != -1) stack_buf[top++] = trie_node[u].ch[c];
    }

    // 逆序处理：任意节点的所有子节点都排在它前面，天然是自底向上
    for (int i = cnt - 1; i >= 0; i--) {
        int u = order[i];
        bool is_leaf = true;
        for (int c = 0; c < SIGMA; c++) {
            int v = trie_node[u].ch[c];
            if (v == -1) continue;
            is_leaf = false;
            // 走到一个「对手无法强赢」的点，本轮就由自己赢
            if (!trie_node[v].can_win) trie_node[u].can_win = true;
            // 走到一个「对手无法强输」的点，对手只能赢，于是本轮由自己输
            if (!trie_node[v].can_lose) trie_node[u].can_lose = true;
        }
        // 叶子：轮到的人无路可走，本轮已经输了 —— 所以「想赢」做不到，「想输」天生成立
        if (is_leaf) trie_node[u].can_lose = true;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    while (cin >> n >> k) { // 多组数据，读到 EOF
        trie_init();

        string s;
        for (ll i = 0; i < n; i++) {
            cin >> s;
            trie_insert(s);
        }

        dfs_dp();
        bool can_win = trie_node[0].can_win;
        bool can_lose = trie_node[0].can_lose;

        if (!can_win) {
            // 先手一轮也赢不了：每轮的输者都还是先手，Teacher 连赢 k 轮
            cout << "Teacher wins!\n";
        } else if (can_lose) {
            // 先手可自选胜负：前 k-1 轮故意输（下一轮仍自己先手），第 k 轮再赢
            cout << "HY wins!\n";
        } else {
            // 先手只能赢不能输：胜负严格交替，看最后一轮 k 的奇偶
            cout << (k % 2 == 1 ? "HY wins!\n" : "Teacher wins!\n");
        }
    }
    return 0;
}
