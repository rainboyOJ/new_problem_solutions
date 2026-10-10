/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:46
 * update_at: 2026-10-07 18:05
 */
// 最小花费：询问区间 [i,j] 的和的奇偶性 = 前缀异或 S_{i-1} xor S_j，
// 要把每个 x_i 定下来，就必须把全部前缀点 S_0..S_n 连成一块（S_0 = 0 已知），
// 于是答案就是 n+1 个点、边 (i-1,j) 权为 c[i,j] 的完全图的最小生成树。
// 稠密图用朴素 Prim，O(n^2)。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 2005;   // n 的上限 2000，点数 V = n+1 <= 2001
const ll INF = 4000000000000000000LL; // 4×10^18，比最大可能答案（2000 * 10^9）大得多

int V;                   // 点数 = n+1，前缀点为 0..n
int w[MAXN * MAXN];      // 平铺的对称邻接矩阵，w[a*V+b] = 边 (a,b) 的权，a<b 时为 c[a+1][b]
ll minDist[MAXN];        // minDist[u] = 未入树的点 u 到当前生成树的最小边权
char used[MAXN];         // used[u] = 点 u 是否已进入生成树

// fread 缓冲的快速读入：最大输入约 22MB，逐个 scanf 会超时
static char buf[1 << 16];
static size_t bufLen = 0, bufPos = 0;

// 取下一位字符，缓冲空了就补一次
static inline int nextChar() {
    if (bufPos == bufLen) {
        bufLen = fread(buf, 1, sizeof(buf), stdin);
        bufPos = 0;
        if (bufLen == 0) return -1;
    }
    return buf[bufPos++];
}

// 读一个非负整数（本题费用 0 <= c <= 10^9，用 int 就够）
int readInt() {
    int c = nextChar();
    while (c != -1 && (c < '0' || c > '9')) c = nextChar();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = nextChar();
    }
    return x;
}

int main() {
    int n = readInt();
    V = n + 1;
    // 题面第 i 行给的是 c[i][j] (i <= j <= n)，它正是前缀点 i-1 与 j 之间的边权
    for (int i = 1; i <= n; ++i) {
        int a = i - 1;
        for (int j = i; j <= n; ++j) {
            int cost = readInt();
            w[a * V + j] = cost; // 上三角
            w[j * V + a] = cost; // 对称的下三角
        }
    }

    for (int u = 0; u < V; ++u) {
        minDist[u] = INF;
        used[u] = 0;
    }
    minDist[0] = 0; // 从点 0 出发

    ll ans = 0;
    for (int step = 0; step < V; ++step) {
        int v = -1; // 未入树点中离树最近的那个
        for (int u = 0; u < V; ++u)
            if (!used[u] && (v == -1 || minDist[u] < minDist[v])) v = u;
        used[v] = 1;
        ans += minDist[v];
        // 用新入树的 v 松弛其余未入树点
        for (int u = 0; u < V; ++u)
            if (!used[u] && w[v * V + u] < minDist[u]) minDist[u] = w[v * V + u];
    }

    printf("%lld\n", ans);
    return 0;
}
