/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:25
 * update_at: 2026-10-06 15:25
 */

#include <cstdio>
using namespace std;

typedef long long ll;

const int MOD = 10007;
const int MAXM = 100005;

// 桶结构：按 (颜色, 奇偶) 分组，每组维护 [个数k, 下标和, 数字和, 下标x数字积和]
// 奇偶用 0/1 表示，颜色范围 [1, m]
struct Bucket {
    int cnt;    // k
    ll sum_i;   // Σi
    ll sum_a;   // Σa_i
    ll sum_ia;  // Σi*a_i
    Bucket(): cnt(0), sum_i(0), sum_a(0), sum_ia(0) {}
};

// 颜色最多 1e5，奇偶 2 种，开二维数组
Bucket bucket[MAXM][2];

int n, m;
ll num[MAXM]; // number_i，下标从 1 开始
int col[MAXM]; // color_i，下标从 1 开始

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &num[i]);
    for (int i = 1; i <= n; i++) scanf("%d", &col[i]);

    // 按 (颜色, 下标奇偶) 分桶，统计 4 个量
    for (int i = 1; i <= n; i++) {
        int c = col[i];
        int p = i & 1; // 0 表示偶数下标，1 表示奇数下标
        bucket[c][p].cnt++;
        bucket[c][p].sum_i += i;
        bucket[c][p].sum_a += num[i];
        bucket[c][p].sum_ia += (ll)i * num[i];
    }

    // 桶内无序对 {i,j} 的贡献 (i+j)(a_i+a_j) 求和展开：
    // 每个 i*a_i 在 k-1 个对里各出现一次，交叉项合计 sum_i * sum_a - sum_ia，
    // 合起来即 (k-2)*sum_ia + sum_i*sum_a。
    ll ans = 0;
    for (int c = 1; c <= m; c++) {
        for (int p = 0; p <= 1; p++) {
            Bucket &b = bucket[c][p];
            if (b.cnt < 2) continue; // k<2 时贡献为 0
            ll contrib = (ll)(b.cnt - 2) * b.sum_ia + b.sum_i * b.sum_a;
            ans += contrib;
        }
    }

    ans %= MOD;
    if (ans < 0) ans += MOD;
    printf("%lld\n", ans);
    return 0;
}
