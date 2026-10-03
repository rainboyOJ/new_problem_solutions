/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:36
 *
 * P9234 [蓝桥杯 2023 省 A] 买瓜
 *
 * 模型：每个瓜有三种去向
 *   不买          -> 重量贡献 0
 *   劈开只买半个  -> 重量贡献 A_i/2，劈瓜数 +1
 *   买整个        -> 重量贡献 A_i，  劈瓜数不变
 * 要求重量和恰好为 m，最小化劈瓜数。
 *
 * 技巧一：把所有重量统一乘 2，半个瓜的重量就是整数 A_i，整瓜是 2*A_i，
 *         目标变成 target = 2*m，全程整数运算，不丢精度。
 * 技巧二：直接枚举是 3^n（n=30 时约 2*10^14，必然超时），采用折半搜索：
 *         把瓜分成两半分别枚举，左半记录"凑出重量 w 最少要劈几刀"，
 *         右半枚举后用 target-右半重量 去左半里查表，合并答案。
 *         复杂度降到约 2*3^(n/2)，n=30 时约 3*10^7。
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 35;

int n;
ll m;
ll a[maxn];   // 每个瓜的重量（原始值）
ll target;    // 目标重量 = 2*m

int half;              // 前半部分的瓜的个数
ll leftWholeMax;       // 左半全部买整瓜的重量和（放大后）
ll rightWholeMax;      // 右半全部买整瓜的重量和（放大后）

ull *leftPack;         // 左半所有可达状态：打包成 (重量 << 5) | 劈瓜数
long long leftCnt;     // 左半状态数
int ans;               // 最优劈瓜数

// 从大到小排序，让大的瓜先决策，剪枝更早生效
bool cmp_greater(ll x, ll y) {
    return x > y;
}

ll gcd_ll(ll x, ll y) {
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

// 枚举左半的每一种去向，收集所有可达重量
// idx: 当前瓜；sum: 已选重量（放大后）；cuts: 已劈瓜数
// restWhole: 剩下的左半瓜全部买整瓜的重量和（上界，用于剪枝）
void enumerateLeft(int idx, ll sum, int cuts, ll restWhole) {
    if (sum > target) return;
    // 左半最多把重量补到 sum+restWhole，若这个上界还够不到
    // 右半可能需要的下界，这条分支就没用
    if (sum + restWhole < target - rightWholeMax) return;
    if (idx == half) {
        leftPack[leftCnt++] = ((ull)sum << 5) | (ull)cuts;
        return;
    }
    ll nxt = restWhole - 2 * a[idx];
    enumerateLeft(idx + 1, sum + 2 * a[idx], cuts, nxt);      // 买整个
    enumerateLeft(idx + 1, sum + a[idx], cuts + 1, nxt);      // 买半个，劈一刀
    enumerateLeft(idx + 1, sum, cuts, nxt);                   // 不买
}

// 枚举右半的每一种去向，用 target-sum 去左半查表合并答案
void enumerateRight(int idx, ll sum, int cuts, ll restWhole) {
    if (sum > target) return;
    // 右半全买整瓜也只有 sum+restWhole，若还够不到左半能提供的下界，剪掉
    if (sum + restWhole < target - leftWholeMax) return;
    if (idx == n) {
        ll need = target - sum;
        if (need < 0 || need > leftWholeMax) return;
        // 左半状态按 (重量<<5)|劈瓜数 升序排列，
        // 相同重量时劈瓜数小的排前面，所以首次命中就是最优
        ull key = ((ull)need << 5);
        ull *lo = lower_bound(leftPack, leftPack + leftCnt, key);
        if (lo != leftPack + leftCnt && ((*lo) >> 5) == (ull)need) {
            int c = (int)((*lo) & 31);
            if (cuts + c < ans) ans = cuts + c;
        }
        return;
    }
    ll nxt = restWhole - 2 * a[idx];
    enumerateRight(idx + 1, sum + 2 * a[idx], cuts, nxt);     // 买整个
    enumerateRight(idx + 1, sum + a[idx], cuts + 1, nxt);     // 买半个，劈一刀
    enumerateRight(idx + 1, sum, cuts, nxt);                  // 不买
}

void read_data() {
    scanf("%d %lld", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
}

signed main () {
    read_data();

    sort(a, a + n, cmp_greater);
    target = 2 * m;

    // 剪枝 1：全部买整瓜也够不到目标，必然无解
    ll total = 0;
    for (int i = 0; i < n; i++) total += 2 * a[i];
    if (target > total) {
        printf("-1\n");
        return 0;
    }

    // 剪枝 2：每个瓜贡献的重量都是 g = gcd(A_1..A_n) 的倍数，
    // 所以 total 必为 g 的倍数。target 不是 g 的倍数时一定凑不出来，
    // 例如 30 个 10^9 的瓜凑不出 10^9 + 1。
    ll g = 0;
    for (int i = 0; i < n; i++) g = gcd_ll(g, a[i]);
    if (g && target % g != 0) {
        printf("-1\n");
        return 0;
    }

    half = n / 2;
    leftWholeMax = 0;
    for (int i = 0; i < half; i++) leftWholeMax += 2 * a[i];
    rightWholeMax = 0;
    for (int i = half; i < n; i++) rightWholeMax += 2 * a[i];

    // 左半最多 3^half 种去向；half = n/2 <= 15，约 1.4*10^7 个状态
    long long cap = 1;
    for (int i = 0; i < half; i++) cap *= 3;
    leftPack = new ull[cap + 5];
    leftCnt = 0;
    enumerateLeft(0, 0, 0, leftWholeMax);

    sort(leftPack, leftPack + leftCnt);
    // 同一重量只保留最小劈瓜数：打包后劈瓜数在低位，升序排序后
    // 相同重量里第一个出现的就是劈瓜数最小的，后面的直接丢掉
    long long w = 0;
    for (long long i = 0; i < leftCnt; i++) {
        if (i > 0 && (leftPack[i] >> 5) == (leftPack[i - 1] >> 5)) continue;
        leftPack[w++] = leftPack[i];
    }
    leftCnt = w;

    ans = n + 1;   // n+1 表示"还没找到可行方案"
    enumerateRight(half, 0, 0, rightWholeMax);

    if (ans > n) printf("-1\n");
    else printf("%d\n", ans);

    return 0;
}
