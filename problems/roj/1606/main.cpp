/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:23
 * update_at: 2026-10-05 12:23
 *
 * 「一本通 5.6 例 1」任务安排 1
 * 顺序不可变的序列切成连续若干批，每批开始前有固定启动时间 S。
 * 一批的耗时会被它之后所有任务共享，直接按“完成时刻”DP 会失去无后效性；
 * 交换求和次序后，批 (j, i] 的贡献 = (S + 该批耗时和) × (j 之后所有 C 之和)，
 * 两项都只依赖前缀和，于是 f[i] 只需枚举切点 j 即可转移：
 * f[i] = min_{j<i} f[j] + (S + preT[i] - preT[j]) * (preC[N] - preC[j])。
 * 时间复杂度 O(N^2)，空间 O(N)。
 */
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXN = 5005;
const ll INF = 1000000000000000000LL; // 取最小值用的哨兵，远大于真实答案上界

ll n, S;
ll preT[MAXN]; // preT[i] = 前 i 个任务的耗时前缀和
ll preC[MAXN]; // preC[i] = 前 i 个任务的费用系数前缀和
ll f[MAXN];    // f[i] = 前 i 个任务分批的最小总费用（按批记账）

int main() {
    scanf("%lld %lld", &n, &S);
    for (ll i = 1; i <= n; i++) {
        ll t, c;
        scanf("%lld %lld", &t, &c);
        preT[i] = preT[i - 1] + t;
        preC[i] = preC[i - 1] + c;
    }

    ll totalC = preC[n]; // 全部任务的费用系数之和，用于取后缀和 preC[N] - preC[j]
    f[0] = 0;
    for (ll i = 1; i <= n; i++) {
        ll best = INF;
        // 枚举最后一批的起点 j+1，即切点 j 把前 j 个任务作为已处理前缀
        for (ll j = 0; j < i; j++) {
            ll cand = f[j] + (S + preT[i] - preT[j]) * (totalC - preC[j]);
            if (cand < best)
                best = cand;
        }
        f[i] = best;
    }

    printf("%lld\n", f[n]);
    return 0;
}
