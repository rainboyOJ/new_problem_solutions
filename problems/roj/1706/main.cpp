/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:30
 * update_at: 2026-10-07 17:30
 */

// 一本通 1706《串包含问题》
// 长度为 2m 的反对称串 S 由前 m 位 T 唯一确定：S = T + ~reverse(T)，
// 于是"数 S"变成"数 T"。把模式 p 和它的右半段替身 q = ~reverse(p) 一起插进
// AC 自动机，逐位构造 T 做 DP，用 2^n 的掩码记已经命中的模式；
// 横跨中点的命中无法边走边判，改成在"较长前缀"的节点上打标记、末尾一次性结算。

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;
const int MAXN = 6;                        // 模式个数上限
const int MAXLEN = 100;                    // 单个模式长度上限
const int MAXNODE = 1 + 2 * MAXN * MAXLEN; // AC 自动机节点数上限：1 + 2 * sum|s_i|

struct Node {
    int ch[2];    // 0/1 字符的转移，建好 fail 后补全成自动机转移
    int fail;     // 失配指针
    int endMask;  // 以该节点结尾的模式掩码（p 与 q 共用同一位）
    int midMask;  // 只有"T 以该节点结尾"才成立的中点命中标记
    int hitMask;  // 沿 fail 链累积的 endMask：T 已把该模式当后缀用上
    int midAll;   // 沿 fail 链累积的 midMask
};
Node node[MAXNODE]; // 动态化静态：节点 u 就是 node[u]
int nodeCnt;        // 已经开出的节点个数，根节点固定为 0

struct Pattern {
    string p;             // 原串
    string q;             // ~reverse(p)：p 出现在右半段 <=> q 出现在 T 里
    int len;              // 模式长度
    int pNode[MAXLEN + 1]; // pNode[k] = p 的前 k 位在 trie 上的节点编号
    int qNode[MAXLEN + 1]; // qNode[k] = q 的前 k 位在 trie 上的节点编号
};
Pattern pat[MAXN];

int dp[MAXNODE][1 << MAXN];  // dp[u][mask]：T 走到节点 u、已命中模式集合为 mask 的方案数
int ndp[MAXNODE][1 << MAXN]; // 下一层的滚动数组

// 新建一个节点（动态开点），返回编号
int new_node() {
    nodeCnt++;
    node[nodeCnt].ch[0] = node[nodeCnt].ch[1] = 0;
    node[nodeCnt].fail = 0;
    node[nodeCnt].endMask = node[nodeCnt].midMask = 0;
    node[nodeCnt].hitMask = node[nodeCnt].midAll = 0;
    return nodeCnt;
}

// 把串 s 插进 trie，同时把每个前缀的节点编号记到 path 里
void insert(const string& s, int bit, int path[]) {
    int u = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        int c = s[i] - '0';
        if (!node[u].ch[c]) node[u].ch[c] = new_node();
        u = node[u].ch[c];
        path[i + 1] = u;
    }
    node[u].endMask |= 1 << bit; // p 与 q 都算"模式 bit 被 T 包含"
}

// BFS 建 fail 指针、补全自动机转移，并沿 fail 链累积两类命中掩码
void build() {
    queue<int> que;
    node[0].hitMask = node[0].endMask;
    node[0].midAll = node[0].midMask;
    for (int c = 0; c < 2; ++c) {
        int v = node[0].ch[c];
        if (v) {
            node[v].fail = 0;
            que.push(v);
        } else {
            node[0].ch[c] = 0; // 根的缺失转移指向自己
        }
    }
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        node[u].hitMask = node[u].endMask | node[node[u].fail].hitMask;
        node[u].midAll = node[u].midMask | node[node[u].fail].midAll;
        for (int c = 0; c < 2; ++c) {
            int v = node[u].ch[c];
            if (v) {
                node[v].fail = node[node[u].fail].ch[c];
                que.push(v);
            } else {
                node[u].ch[c] = node[node[u].fail].ch[c];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    nodeCnt = 0; // 根节点 0 不用开点
    int fullMask = 0;
    for (int j = 0; j < n; ++j) {
        cin >> pat[j].p;
        pat[j].len = pat[j].p.size();
        pat[j].q = pat[j].p;
        reverse(pat[j].q.begin(), pat[j].q.end());
        for (int i = 0; i < pat[j].len; ++i)
            pat[j].q[i] = (pat[j].q[i] == '0') ? '1' : '0';
        fullMask |= 1 << j;
        insert(pat[j].p, j, pat[j].pNode);
        insert(pat[j].q, j, pat[j].qNode);
    }

    // 横跨中点的命中：设左侧匹配 k 位（1 <= k <= L-1），左侧是 T 的后缀 k 位、
    // 必须是 p 的前 k 位；右侧由 T 的后缀 L-k 位决定、必须是 q 的前 L-k 位。
    // 两者同时成立 <=> 较长者以较短者为后缀，且 T 以较长者结尾。
    for (int j = 0; j < n; ++j) {
        const string& p = pat[j].p;
        const string& q = pat[j].q;
        int L = pat[j].len;
        for (int k = 1; k <= L - 1; ++k) {
            if (k > L - k) {
                // 较长者是 A = p 的前 k 位，要求 A 的后 L-k 位等于 B = q 的前 L-k 位
                if (p.compare(k - (L - k), L - k, q, 0, L - k) == 0)
                    node[pat[j].pNode[k]].midMask |= 1 << j;
            } else {
                // 较长者是 B = q 的前 L-k 位，要求 B 的后 k 位等于 A = p 的前 k 位
                if (q.compare((L - k) - k, k, p, 0, k) == 0)
                    node[pat[j].qNode[L - k]].midMask |= 1 << j;
            }
        }
    }

    build();

    int nodes = nodeCnt + 1;  // 节点编号 0..nodeCnt
    int states = 1 << n;      // 已命中模式的集合
    dp[0][0] = 1;
    for (int step = 0; step < m; ++step) {
        // 行宽固定是 1 << MAXN，DP 只用前 states 列，所以逐行清零 / 逐行拷贝
        for (int u = 0; u < nodes; ++u) memset(ndp[u], 0, sizeof(int) * states);
        for (int u = 0; u < nodes; ++u) {
            for (int mask = 0; mask < states; ++mask) {
                int val = dp[u][mask];
                if (!val) continue;
                for (int c = 0; c < 2; ++c) {
                    int v = node[u].ch[c];
                    int nm = mask | node[v].hitMask;
                    int t = ndp[v][nm] + val;
                    ndp[v][nm] = (t >= MOD) ? t - MOD : t;
                }
            }
        }
        for (int u = 0; u < nodes; ++u) memcpy(dp[u], ndp[u], sizeof(int) * states);
    }

    // T 已经完整，横跨中点的命中此时才结算：要求节点 u 代表的后缀带上 mid 标记
    ll ans = 0;
    for (int u = 0; u < nodes; ++u) {
        for (int mask = 0; mask < states; ++mask) {
            if ((mask | node[u].midAll) == fullMask) {
                ans += dp[u][mask];
                if (ans >= MOD) ans -= MOD;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
