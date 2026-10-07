/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 03:23
 * update_at: 2026-10-08 03:23
 */
// ROJ 1792 小P的牧场：斜率优化 DP（单调队列维护下凸壳），O(n)。
//
// 模型：选出递增的位置序列 0 = p0 < p1 < ... < pm = n（pm = n 才能控制最东边），
//   总花费 = sum_t ( a[p_t] + sum_{k=p_{t-1}+1}^{p_t-1} (p_t - k) * b_k )。
// DP：f[i] 表示第 i 个牧场必建控制站、且前 i 个牧场都被控制时的最小花费，
//   f[i] = a_i + min_{0 <= j < i} { f[j] + sum_{k=j+1}^{i-1} (i - k) * b_k }
//        = a_i + i * S1[i] - S2[i] + min_{0 <= j < i} { Y[j] - i * X[j] },
//   其中 S1[i] = sum_{k<=i} b_k，S2[i] = sum_{k<=i} k * b_k，
//   X[j] = S1[j]（严格递增），Y[j] = f[j] + S2[j]。
// 查询斜率 i 严格递增 + 横坐标 X 严格递增 => 决策点在单调队列维护的下凸壳上单调右移。
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

ll n;           // 牧场数目
ll a[MAXN];     // a[i]：在第 i 个牧场建控制站的花费
ll S1[MAXN];    // S1[i] = sum_{k<=i} b_k
ll S2[MAXN];    // S2[i] = sum_{k<=i} k * b_k
ll f[MAXN];     // f[i]：第 i 个牧场必建控制站、前 i 个牧场均被控制的最小总花费
ll que[MAXN];   // 单调队列（存决策点下标），维护决策点的下凸壳
ll head, tail;  // 队列区间 [head, tail)

// 快速读入：题面数字均为非负整数，n 最大 10^6，读入量约 10 MB
ll readInt() {
    int c = getchar();
    while (c < '0' || c > '9') c = getchar();
    ll x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = getchar(); }
    return x;
}

// 决策点 j 的坐标：横坐标 X[j] = S1[j]，纵坐标 Y[j] = f[j] + S2[j]
ll X(ll j) { return S1[j]; }
ll Y(ll j) { return f[j] + S2[j]; }

// 下凸壳维护：若 slope(j,k) >= slope(k,m)，则 k 落在 jm 上方或线上，永远不优，可弹掉。
// 叉积最大约 10^16 * 10^10 = 10^26，远超 long long（约 9.2 * 10^18），中间量必须声明为 __int128。
bool bad(ll j, ll k, ll m) {
    __int128 dy1 = Y(k) - Y(j), dx1 = X(k) - X(j);
    __int128 dy2 = Y(m) - Y(k), dx2 = X(m) - X(k);
    return dy1 * dx2 >= dy2 * dx1;
}

// 队头决策：斜率 i 下若 k 已经不比 j 差，则 j 之后再也不会更优
bool front_worse(ll j, ll k, ll i) {
    return Y(k) - Y(j) <= i * (X(k) - X(j));
}

int main() {
    n = readInt();
    for (ll i = 1; i <= n; ++i) a[i] = readInt();
    for (ll i = 1; i <= n; ++i) {
        ll b = readInt();
        S1[i] = S1[i - 1] + b;
        S2[i] = S2[i - 1] + b * i;
    }

    head = 0;
    tail = 0;
    que[tail++] = 0;  // 虚拟起点 j = 0：西边没有控制站，f[0] = S1[0] = S2[0] = 0

    for (ll i = 1; i <= n; ++i) {
        while (head + 1 < tail && front_worse(que[head], que[head + 1], i)) ++head;
        ll j = que[head];  // 队头即当前 i 的最优决策点
        f[i] = a[i] + i * S1[i] - S2[i] + Y(j) - i * X(j);
        while (head + 1 < tail && bad(que[tail - 2], que[tail - 1], i)) --tail;
        que[tail++] = i;
    }

    // 最东边的牧场必须建站才可能被控制，故答案就是 f[n]，不需要对 f 取最小值
    printf("%lld\n", f[n]);
    return 0;
}
