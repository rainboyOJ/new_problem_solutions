/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:58
 * update_at: 2026-10-07 16:04
 */
// main.cpp：最大值。对手把当前值 v 变成 rol(v)（n 位循环左移一位），
// 而 rol 与异或可交换，于是每个时刻的最终值都写成 rol(x) ^ C_i；
// 问题化为「选 y 使 min_i (y ^ C_i) 最大」，用 01 字典树自底向上 DP 求解。
// 与 main.py 同一算法，结点数 O((m+1)n)、时间 O((m+1)n)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 3000035; // 结点数上界：1 + (m+1)*n，m ≤ 100000、n ≤ 30

// 01 字典树用「动态化静态」存储：静态大数组 + node_cnt 当分配指针。
// 每个结点同时带着子树 DP 的结果，避免用多个下标平行的数组。
struct Node {
    int son[2]; // 两个二进制儿子；0 表示这条边不存在（结点 0 只当空标记用）
    int dep;    // 深度 = 从根走到它已经确定的位数，根是 0
    int val;    // 只看它子树里剩下的位时，y 能保证的最坏结果值
    int cnt;    // 在它子树里取到 val 的 y 低位方案数
};

Node node[MAXNODE]; // node[u] 就是结点 u，按高位到低位逐层建树
int node_cnt;       // 已开出的结点个数，真实结点编号是 1..node_cnt，根固定为 1

int n, m;      // n 是位数，m 是异或的操作个数
int a[100005]; // 读入的 a_1..a_m，下标从 1 开始和题面对应

// 把一个数按二进制高位到低位插进 01 字典树
void insert_num(int v) {
    int u = 1;
    for (int k = n - 1; k >= 0; k--) {
        int b = (v >> k) & 1;
        if (node[u].son[b] == 0) { // 这条边还没有，就开一个新结点挂上去
            node_cnt++;
            node[node_cnt].son[0] = 0;
            node[node_cnt].son[1] = 0;
            node[node_cnt].dep = node[u].dep + 1;
            node[u].son[b] = node_cnt;
        }
        u = node[u].son[b];
    }
}

// 返回对手第 i 个时刻对应的常数 C_i = rol(pre[i]) ^ suf[i+1]，
// 其中 pre 是前缀异或、suf 是后缀异或。
int moment_const(int prefix, int suffix, int full) {
    int rot = ((prefix << 1) & full) | (prefix >> (n - 1)); // rol(prefix)
    return rot ^ suffix;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }

    int full = (1 << n) - 1; // n 位全 1 掩码，用来把循环左移截到 n 位

    // pre[i] = a_1 ^ .. ^ a_i（pre[0] = 0），suf[i] = a_i ^ .. ^ a_m（suf[m+1] = 0），
    // 于是 suf[i+1] 就是第 i 个时刻之后所有数的异或。
    // 对手在第 i 个时刻出手（i=0 是刚选完 x，i=m 是最后一次异或后）时，
    // 最终值 = rol(x ^ pre[i]) ^ suf[i+1] = rol(x) ^ (rol(pre[i]) ^ suf[i+1])，
    // 所以插入的常数就是 C_i = rol(pre[i]) ^ suf[i+1]。
    vector<int> pre(m + 1, 0), suf(m + 2, 0);
    for (int i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] ^ a[i];
    }
    for (int i = m; i >= 1; i--) {
        suf[i] = suf[i + 1] ^ a[i];
    }

    node_cnt = 1;
    node[1].son[0] = 0;
    node[1].son[1] = 0;
    node[1].dep = 0;
    for (int i = 0; i <= m; i++) {
        insert_num(moment_const(pre[i], suf[i + 1], full));
    }

    // 子结点编号一定大于父结点，所以按编号从大到小扫就是自底向上。
    for (int u = node_cnt; u >= 1; u--) {
        if (node[u].dep == n) { // 叶子：C 的 n 位已全部确定，没有剩余位可选
            node[u].val = 0;
            node[u].cnt = 1;
            continue;
        }
        int c0 = node[u].son[0], c1 = node[u].son[1];
        int bit = 1 << (n - 1 - node[u].dep); // 当前这一位在结果数值里的权重
        if (c0 == 0 || c1 == 0) {
            // 子树只有一个：全部 C 在这一位都相同，y 取反位就能让这一位是 1；
            // 之后所有 C 都还在这个子树里，低位继续在它里面决策。
            int only = c0 ? c0 : c1;
            node[u].val = bit + node[only].val;
            node[u].cnt = node[only].cnt;
        } else if (node[c0].val == node[c1].val) {
            // 两个子树：对手总能把这一位压成 0。y 选哪一侧就由异侧的子树决定低位，
            // 两侧的最坏值相等，且两种 y 的这一位相反、互不重复，方案数相加。
            node[u].val = node[c0].val;
            node[u].cnt = node[c0].cnt + node[c1].cnt;
        } else {
            int best = node[c0].val > node[c1].val ? c0 : c1; // 取更优的那一侧
            node[u].val = node[best].val;
            node[u].cnt = node[best].cnt;
        }
    }

    printf("%d\n%d\n", node[1].val, node[1].cnt); // rol 是双射，y 的个数就是初值 x 的个数
    return 0;
}
