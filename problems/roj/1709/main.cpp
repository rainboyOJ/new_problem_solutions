/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:43
 * update_at: 2026-10-07 17:43
 */
// 1709 寻找好串
// 一本通 · 高手训练篇 二、字符串算法
//
// 题意：给出字符串集合 S。若串 w 能切成两个非空段 a、b，且 a、b 都是 S 中
//       某个串的前缀，则称 w 是「好」的。求不同好串的个数。
//
// 做法：把所有 S 中的串插入 trie，每个非根结点恰好对应一个非空前缀串，
//       于是前缀集合 P 的大小就是结点数 cnt，好串全体恰为 { p + q | p, q ∈ P }。
//       先按 cnt² 记，再扣掉「同一个串被多种切分重复生成」的次数：两种切分
//       必然相差一段平移块 x（长首段 = 短首段 + x，短尾段 = x + 长尾段）。
//       对每个有非空真后缀的结点 u（fail[u] 不是根），fail[u] 就是那个真后缀，
//       t = s_u 去掉尾部 fail[u] 后的前缀；把 t 当作严格后缀的 P 内串个数
//       正是 fail 树上 t 的子树大小减一，累加即为全部多余切分。
//
// 验证：与「枚举 P×P 去重」的暴力在 n ≤ 4、|s| ≤ 6 上随机对拍 2 万余组全一致；
//       随仓 10 组数据逐点相符。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005; // 结点上界：n · 30 + 1
const int SIGMA = 26;

// trie / AC 自动机的结点：一个结点就是一个前缀串，字段聚合成 struct 而不是平行数组
struct Node {
    int ch[SIGMA]; // 出边（初始全 0 表示没有边）
    int fa;        // 父亲结点
    int dep;       // 深度 = 该结点代表的前缀串长度
    int fail;      // 失配指针
    ll sub;        // fail 树上的子树大小（含自身）
};
Node node[MAXN];

int n;     // 字符串个数
int cnt;   // 已建结点数（不含根，根编号 0）
int order[MAXN]; // 按深度递增的访问序

char buf[64];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", buf + 1);
        int len = (int)strlen(buf + 1), u = 0;
        for (int j = 1; j <= len; j++) {
            int c = buf[j] - 'a';
            if (!node[u].ch[c]) {
                node[u].ch[c] = ++cnt;             // 开点：这个新结点对应一个新前缀
                node[cnt].fa = u;
                node[cnt].dep = node[u].dep + 1;
            }
            u = node[u].ch[c];
        }
    }

    // BFS 求 fail：沿失配链找可走的边，链长不超过串长 30，代价可忽略
    int head = 0, tail = 0;
    for (int c = 0; c < SIGMA; c++)
        if (node[0].ch[c]) order[tail++] = node[0].ch[c];
    while (head < tail) {
        int u = order[head++];
        for (int c = 0; c < SIGMA; c++) {
            int v = node[u].ch[c];
            if (!v) continue;
            int f = node[u].fail;
            while (f && !node[f].ch[c]) f = node[f].fail;
            node[v].fail = node[f].ch[c];
            order[tail++] = v;
        }
    }

    // fail 树子树大小：fail 指向更浅的结点，倒着扫访问序累加即可
    for (int i = 1; i <= cnt; i++) node[i].sub = 1;
    for (int k = cnt - 1; k >= 0; k--) {
        int u = order[k];
        node[node[u].fail].sub += node[u].sub;
    }

    // 扣除重复切分：u 有非空真后缀（fail[u] != root）时，
    // 从 u 向上走 dep[fail[u]] 步得到祖先 t（深度等于 |fail[u]|），
    // sub[t] - 1 是以 t 为严格后缀的 P 内串个数，即该平移块带来的多余切分。
    ll ans = (ll)cnt * cnt;
    for (int u = 1; u <= cnt; u++) {
        if (!node[u].fail) continue;              // 没有真后缀则不会产生平移
        int t = u, steps = node[node[u].fail].dep;
        while (steps--) t = node[t].fa;
        ans -= node[t].sub - 1;
    }

    printf("%lld\n", ans);
    return 0;
}
