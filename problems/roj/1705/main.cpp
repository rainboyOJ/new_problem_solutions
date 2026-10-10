/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 16:05
 * update_at: 2026-10-07 16:05
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 100000;   // 答案取模的模数
const int ALPHA = 4;     // 字符集大小，A/C/T/G 依次映射成 0/1/2/3
const int MAXNODE = 128; // m<=10 且 |s|<=10，Trie 节点数上界 1+10*10=101，留少量裕量

// Trie 节点：nxt 先当儿子边用，建完 fail 指针后被补成完整的 DFA 转移表
struct Node {
    int nxt[ALPHA]; // 从本状态走字符 c 的去处，根固定为 0 号节点
    int fail;       // 失配指针
    char danger;    // 本状态的后缀（含自身）是否出现过禁止子串
};
Node trie[MAXNODE]; // 状态 u 就是 trie[u]，编号从 0（根）开始
int node_cnt;       // 已创建的节点个数，也等于最大编号

ll m; // 禁止子串个数
ll n; // 序列长度

// 矩阵：sz x sz，元素已模 MOD
struct Mat {
    int sz;
    ll a[MAXNODE][MAXNODE];
};

// 新建一个 Trie 节点（动态化静态：静态大数组 + node_cnt 当分配指针）
int new_node() {
    node_cnt++;
    for (int c = 0; c < ALPHA; c++) trie[node_cnt].nxt[c] = 0;
    trie[node_cnt].fail = 0;
    trie[node_cnt].danger = 0;
    return node_cnt;
}

// 字符映射：A/C/T/G -> 0/1/2/3，题面保证输入只含这四种字符
int c2i(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'T') return 2;
    return 3;
}

// 插入全部禁止子串，再用 BFS 建 fail 指针，顺便把 Trie 补成完整 DFA
void build_dfa() {
    node_cnt = 0; // 根节点
    for (int c = 0; c < ALPHA; c++) trie[0].nxt[c] = 0;
    trie[0].fail = 0;
    trie[0].danger = 0;

    for (int i = 0; i < m; i++) {
        char buf[32];
        scanf("%31s", buf);
        int cur = 0;
        for (int j = 0; buf[j]; j++) {
            int v = c2i(buf[j]);
            if (trie[cur].nxt[v] == 0) trie[cur].nxt[v] = new_node();
            cur = trie[cur].nxt[v];
        }
        trie[cur].danger = 1; // 该状态本身就是一个禁止子串
    }

    // 根的儿子的 fail 都指向根
    queue<int> q;
    for (int c = 0; c < ALPHA; c++) {
        int v = trie[0].nxt[c];
        if (v) {
            trie[v].fail = 0;
            q.push(v);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (trie[trie[u].fail].danger) trie[u].danger = 1; // 后缀里带禁止串也算危险
        for (int c = 0; c < ALPHA; c++) {
            int v = trie[u].nxt[c];
            if (v) {
                // fail[u] 已经处理过，它的 nxt[c] 已是 DFA 转移
                trie[v].fail = trie[trie[u].fail].nxt[c];
                q.push(v);
            } else {
                trie[u].nxt[c] = trie[trie[u].fail].nxt[c]; // 补边，形成完整 DFA
            }
        }
    }
}

// 方阵乘法，x 的行乘 y 的列，元素模 MOD
Mat mat_mul(const Mat &x, const Mat &y) {
    Mat r;
    r.sz = x.sz;
    for (int i = 0; i < x.sz; i++)
        for (int j = 0; j < x.sz; j++) r.a[i][j] = 0;
    for (int i = 0; i < x.sz; i++)
        for (int k = 0; k < x.sz; k++) {
            if (x.a[i][k] == 0) continue;
            for (int j = 0; j < x.sz; j++)
                r.a[i][j] = (r.a[i][j] + x.a[i][k] * y.a[k][j]) % MOD;
        }
    return r;
}

int main() {
    if (scanf("%lld %lld", &m, &n) != 2) return 0;
    build_dfa();

    int total = node_cnt + 1; // 状态编号范围 0..node_cnt
    int id[MAXNODE];          // 原状态 -> 压缩后的「安全状态」编号
    int K = 0;                // 安全状态个数
    for (int u = 0; u < total; u++) {
        id[u] = -1;
        if (!trie[u].danger) id[u] = K++;
    }
    if (id[0] < 0) { // 根都危险（空串是禁止子串）时无解
        printf("0\n");
        return 0;
    }

    // 转移矩阵：只在安全状态之间连边，同一个 (u,v) 有多条字符边就累加
    Mat base;
    base.sz = K;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) base.a[i][j] = 0;
    for (int u = 0; u < total; u++) {
        if (trie[u].danger) continue;
        for (int c = 0; c < ALPHA; c++) {
            int v = trie[u].nxt[c];
            if (!trie[v].danger) base.a[id[u]][id[v]]++;
        }
    }

    // 矩阵快速幂求 base^n：base^n[根][v] 表示从根走 n 步停在 v 的合法串数
    Mat res;
    res.sz = K;
    for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++) res.a[i][j] = 0;
    for (int i = 0; i < K; i++) res.a[i][i] = 1;
    ll e = n;
    while (e > 0) {
        if (e & 1) res = mat_mul(res, base);
        e >>= 1;
        if (e > 0) base = mat_mul(base, base);
    }

    // 答案 = 从根出发走 n 步落在任意安全状态的总方案数
    ll ans = 0;
    for (int j = 0; j < K; j++) ans = (ans + res.a[id[0]][j]) % MOD;
    printf("%lld\n", ans);
    return 0;
}
