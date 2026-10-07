/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:59
 * update_at: 2026-10-07 22:40
 *
 * 一本通 1750《取数字》
 *
 * 模型：先手第一步取走 a[p] 后，已取走的数在环上构成一段连续弧，剩下的数
 * 也构成一段连续弧。把剩下的弧按顺时针拉直成序列 C（长度 n-1），此时
 * 「旁边有空位」的候选恰好是 C 的两个端点，而题面规定「有多个时选较大的」，
 * 所以第 2..n 步完全确定：每步取走 C 两端中较大的那个。
 *
 * 记这个确定序列为 x0, x1, ...（x0 是后手取走的），令
 *     D = x0 - x1 + x2 - x3 + ...        （交错和）
 * 剩余数之和为 S - a[p]，其中后手得分 = (S - a[p] + D) / 2，于是
 *     先手总分 = (S + a[p] - D) / 2。
 *
 * 朴素模拟每个起点要 O(n)，总 O(n^2)（N = 3e5 时约 9e10 次，必然超时）。
 * 加速的关键：双指针「取两端较大者」时，同侧会连取一整段连续元素——
 * 从当前端点出发，一直取到「第一个比对面端点小的元素」为止。因此整局只需
 * O(段数) 次查询：「右侧/左侧第一个小于 t 的位置」。用区间最小值线段树做该
 * 查询，每段 O(log n)。段数实测很小（随机数据约 13 段/起点，总段数约 1.3e7
 * 的 1/3），总复杂度 O(总段数 * log n)，N = 3e5 时约 0.3s。
 *
 * 每段贡献可用交错前缀和 O(1) 求出：令 P[i] = sum_{j<i} (-1)^j * A2[j]，则
 * 左侧段 A2[u..w-1] 的交错和（以 + 开头）为 (-1)^u * (P[w] - P[u])，
 * 右侧段 A2[v], A2[v-1], ..., A2[w+1] 的为 (-1)^v * (P[v+1] - P[w+1])。
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300000 + 5;

int n;                 // 环上数字个数
int a[MAXN];           // 原环
int A2[2 * MAXN];      // 环复制两遍，起点 p 对应的弧即 A2[p+1 .. p+n-1]
ll pref[2 * MAXN + 2]; // pref[i] = sum_{j<i} (-1)^j * A2[j]
ll sum_all;            // S = Σ a[i]

int segN;            // 线段树的叶子数（2 的幂）
int mn[1 << 21];     // 线段树：区间最小值

// 快速读入
inline int readInt() {
    int x = 0;
    int c = getchar();
    while (c < '0' || c > '9') {
        if (c == EOF) return 0;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

// 最小的下标 i ∈ [ql, qr] 使 A2[i] < t；不存在返回 -1
int firstLess(int node, int nl, int nr, int ql, int qr, int t) {
    if (qr < nl || nr < ql || mn[node] >= t) return -1;
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    int res = firstLess(node << 1, nl, mid, ql, qr, t);
    if (res != -1) return res;
    return firstLess(node << 1 | 1, mid + 1, nr, ql, qr, t);
}

// 最大的下标 i ∈ [ql, qr] 使 A2[i] < t；不存在返回 -1
int lastLess(int node, int nl, int nr, int ql, int qr, int t) {
    if (qr < nl || nr < ql || mn[node] >= t) return -1;
    if (nl == nr) return nl;
    int mid = (nl + nr) >> 1;
    int res = lastLess(node << 1 | 1, mid + 1, nr, ql, qr, t);
    if (res != -1) return res;
    return lastLess(node << 1, nl, mid, ql, qr, t);
}

int main() {
    n = readInt();
    for (int i = 0; i < n; ++i) {
        a[i] = readInt();
        sum_all += a[i];
    }
    if (n == 1) { // 只有一个数，先手直接拿走
        printf("%lld\n", sum_all);
        return 0;
    }

    int M = 2 * n;
    for (int i = 0; i < M; ++i) A2[i] = a[i % n];
    for (int i = 0; i < M; ++i)
        pref[i + 1] = pref[i] + ((i & 1) ? -1LL : 1LL) * A2[i];

    segN = 1;
    while (segN < M) segN <<= 1;
    for (int i = 0; i < segN; ++i) mn[segN + i] = (i < M) ? A2[i] : INT_MAX;
    for (int i = segN - 1; i >= 1; --i) mn[i] = min(mn[2 * i], mn[2 * i + 1]);

    for (int p = 0; p < n; ++p) {
        // 起点 p：剩余弧是 A2[p+1 .. p+n-1]，两个指针在两端
        int u = p + 1, v = p + n - 1;
        ll D = 0;
        int step = 1; // 当前这一手是「弧内第几个被取走」的（从 1 开始）
        while (u < v) {
            if (A2[u] > A2[v]) {
                // 左指针连取：一直取到第一个小于 A2[v] 的位置 w
                int w = firstLess(1, 0, segN - 1, u + 1, v, A2[v]);
                if (w < 0) w = v; // 该段内没有更小的，则两指针在 v 相遇
                int len = w - u;
                if (len > 0) {
                    ll val = pref[w] - pref[u];
                    if (u & 1) val = -val;
                    D += ((step & 1) ? 1 : -1) * val;
                    step += len;
                }
                u = w;
            } else {
                // 右指针连取：一直取到第一个小于 A2[u] 的位置 w
                int w = lastLess(1, 0, segN - 1, u, v - 1, A2[u]);
                if (w < 0) w = u;
                int len = v - w;
                if (len > 0) {
                    ll val = pref[v + 1] - pref[w + 1];
                    if (v & 1) val = -val;
                    D += ((step & 1) ? 1 : -1) * val;
                    step += len;
                }
                v = w;
            }
        }
        D += ((step & 1) ? 1 : -1) * (ll)A2[u]; // 最后一个元素
        printf("%lld\n", (sum_all + (ll)a[p] - D) / 2);
    }
    return 0;
}
