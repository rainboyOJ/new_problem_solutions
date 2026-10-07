/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 16:01
 * update_at: 2026-10-07 16:01
 */

// 一本通 1702《异或运算》正式解
//
// 题意：X[1..n]、Y[1..m]，矩阵 A[i][j] = X[i] xor Y[j]。
// 每次询问矩形 i∈[u,d]、j∈[l,r] 中第 k 大的 A[i][j]。
//
// 关键观察：
//   1. 第 k 大从高位往低位定答案，只需要"候选集合里当前位为 1 的元素有多少个"。
//   2. 对固定的位 b 和固定的 X[i]，A[i][j] 的第 b 位为 1 等价于 Y[j] 的第 b 位
//      等于 (X[i]>>b)&1 的取反；所以统计 Y 的区间 [l,r] 上"某一位等于某值"的个数，
//      就把二维问题拆成了一维的区间按位计数。
//   3. 可持久化 01-Trie 的前缀版本 roots[j] 恰好提供"区间 [l,r] 上某一位为某值"的计数：
//      cnt(roots[r] 的第 want 棵子树) - cnt(roots[l-1] 的第 want 棵子树)。
//   4. n 只有 1000，每次询问可以把 d-u+1 个 X[i] 对应的 Trie 指针整排一起往下走，
//      逐位累计 cnt1 决定答案这一位是 1 还是 0。
//
// 复杂度：建树 O(31m)，单次询问 O(31(d-u+1))，总 O(31(m + pn))，n≤1000、m≤300000、p≤500 可行。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXB = 31;             // X_i, Y_j < 2^31，二进制位编号 0..30
const int MAXM = 300005;         // Y 的长度上界
const int MAXN = 1005;           // X 的长度上界
const int MAXNODE = (MAXM + 5) * 32; // 可持久化 Trie 节点数：每个元素一条链，链长 32

struct Node {
    int ch[2]; // 两个儿子（对应二进制位 0/1）的编号，0 表示空
    int cnt;   // 该子树里元素的个数
};

Node node[MAXNODE]; // 动态化静态：所有 Trie 节点放在一个静态数组里，用 node_cnt 开点
int node_cnt;       // 已经开出的节点个数，节点 0 是全局空节点

ll X[MAXN];         // 数列 X，下标从 1 开始
int roots[MAXM];    // roots[j] = 只插入 Y[1..j] 的 Trie 的根编号

// 复制节点 from 开出一个新点，返回新点编号（可持久化的"版本复制"）
int new_node(int from) {
    node_cnt++;
    node[node_cnt] = node[from];
    return node_cnt;
}

// 在版本 prev 的基础上插入 val，返回新版本的根编号
int insert(int prev, ll val) {
    int root = new_node(prev);
    int cur = root;
    node[cur].cnt++;
    for (int b = MAXB - 1; b >= 0; b--) {
        int bit = (val >> b) & 1; // 当前位的取值
        int nxt = new_node(node[prev].ch[bit]); // 复制要下钻的那棵子树
        node[cur].ch[bit] = nxt;
        cur = nxt;
        prev = node[prev].ch[bit];
        node[cur].cnt++; // 新版本里这条链上的计数都加一
    }
    return root;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &X[i]);
    }

    node_cnt = 0;
    for (int j = 1; j <= m; j++) {
        ll v;
        scanf("%lld", &v);
        roots[j] = insert(roots[j - 1], v);
    }

    int p;
    scanf("%d", &p);
    while (p--) {
        int u, d, l, r, k;
        scanf("%d %d %d %d %d", &u, &d, &l, &r, &k);

        // 每行 X[i] 各自带一对 Trie 指针：cur[i] 是版本 r 的当前节点，
        // prv[i] 是版本 l-1 的当前节点，二者相减就是 Y[l..r] 上这段的计数。
        int cur[MAXN], prv[MAXN];
        for (int i = u; i <= d; i++) {
            cur[i] = roots[r];
            prv[i] = roots[l - 1];
        }

        ll ans = 0;
        for (int b = MAXB - 1; b >= 0; b--) {
            int cnt1 = 0; // 候选集合里 A 的第 b 位为 1 的元素个数
            for (int i = u; i <= d; i++) {
                int xb = (X[i] >> b) & 1;
                int want = xb ^ 1; // 想让 A 的第 b 位为 1，Y 的第 b 位必须是 xb 取反
                cnt1 += node[node[cur[i]].ch[want]].cnt - node[node[prv[i]].ch[want]].cnt;
            }

            int bit; // 答案当前位的取值
            if (k <= cnt1) {
                // 第 k 大落在"当前位为 1"的那一半里，答案这一位取 1，指针走 want 分支
                bit = 1;
                for (int i = u; i <= d; i++) {
                    int want = ((X[i] >> b) & 1) ^ 1;
                    cur[i] = node[cur[i]].ch[want];
                    prv[i] = node[prv[i]].ch[want];
                }
            } else {
                // 当前位为 1 的元素全被跳过，把 k 减去它们，指针走另一位
                k -= cnt1;
                bit = 0;
                for (int i = u; i <= d; i++) {
                    int want = (X[i] >> b) & 1;
                    cur[i] = node[cur[i]].ch[want];
                    prv[i] = node[prv[i]].ch[want];
                }
            }
            ans |= (ll)bit << b;
        }

        printf("%lld\n", ans);
    }

    return 0;
}
