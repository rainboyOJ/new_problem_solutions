/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* P6824 「EZEC-4」可乐 —— 静态数组版（对应 index.md 样例图的"贡献覆盖"思路） */
/* 与 main.cpp（rbook 模板版）是同一算法的两种实现：
 *   打标记规则完全相同（k 位=1：异或位取 0 的子树 +1、深入异或位取 1 的分支；
 *   k 位=0：只深入异或位取 0 的分支；走到底的叶子 +1）；
 *   区别：这里 DFS 下传时只结算"实际分配出来的叶子"的覆盖度。
 * 节点用 struct 打包：ch[2]（儿子编号）与 tag（懒标记）放在一起。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAX_BIT = 20;             // a, k <= 1e6 < 2^20，留一位余量
const int MAX_NODE = MAXN * 22 + 5; // 每个数最多新增 21 个节点，2.2M 足够

// 01-Trie 节点：ch[2] 儿子编号（0 为空），tag 懒标记
struct Node {
    int ch[2];
    int tag;
} trie[MAX_NODE];

int node_cnt = 1; // 根节点始终为 1，0 号留作"空儿子"哨兵

// 将 a 针对条件 a ^ x <= k 插入并打懒标记
void insert(int a, int k) {
    int u = 1;
    for (int i = MAX_BIT; i >= 0; --i) {
        int bit_a = (a >> i) & 1;
        int bit_k = (k >> i) & 1;

        if (bit_k == 1) {
            // 1. x 使得异或结果当前位为 0：整棵子树严格小于 k，低位任取，打 tag
            // x 位 = a 位 ^ 异或位(0)；^0 是恒等运算（任何数 ^ 0 不变），
            // 写成 ^0 是为了与下面的 ^1 保持公式对称：x_j = a_i[j] ^ (异或位)
            int branch_less = bit_a ^ 0;
            if (!trie[u].ch[branch_less]) {
                trie[u].ch[branch_less] = ++node_cnt;
            }
            trie[trie[u].ch[branch_less]].tag++;

            // 2. x 使得异或结果当前位为 1：保持前缀相等，继续深入
            int branch_eq = bit_a ^ 1;
            if (!trie[u].ch[branch_eq]) {
                trie[u].ch[branch_eq] = ++node_cnt;
            }
            u = trie[u].ch[branch_eq];
        } else {
            // bit_k == 0：异或结果必须为 0（相等），否则会大于 k
            int branch_eq = bit_a ^ 0;
            if (!trie[u].ch[branch_eq]) {
                trie[u].ch[branch_eq] = ++node_cnt;
            }
            u = trie[u].ch[branch_eq];
        }
    }
    // 叶子节点：精确匹配 a ^ x == k 的情况
    trie[u].tag++;
}

int max_cola = 0;

// DFS 把上层的懒标记瀑布式下推到叶子
void dfs(int u, int current_sum) {
    if (!u) return;

    // 累加当前路径上的 tag
    current_sum += trie[u].tag;

    // 走到实际分配出来的叶子，结算该区域的覆盖度
    if (!trie[u].ch[0] && !trie[u].ch[1]) {
        max_cola = max(max_cola, current_sum);
        return;
    }

    // 继续向下传递
    if (trie[u].ch[0]) dfs(trie[u].ch[0], current_sum);
    if (trie[u].ch[1]) dfs(trie[u].ch[1], current_sum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        insert(a, k);
    }

    dfs(1, 0);
    cout << max_cola << '\n';
    return 0;
}
