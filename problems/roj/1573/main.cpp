/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:17
 * update_at: 2026-10-05 09:17
 */

// 区间 DP：dp[l][r] 表示把区间 [l..r] 全部分离再合体的最大总价值，
// 转移枚举本区间的第一个分离点 k：dp[l][r] = max_k { dp[l][k] + dp[k+1][r] + (a_l + a_r) * a_k }。
// 输出要求字典序最小：枚举 k 从左到右、严格大于才替换，平手自然取最左切点；
// 再从根区间按分离阶段（层序）遍历切点表，即得"阶段从前到后、同阶段从左到右"的输出。

#include <cstdio>

typedef long long ll;

const int MAXN = 305;

int n;
ll a[MAXN];        // a[i]：第 i 个区域金钥匙的价值（1 基）
ll dp[MAXN][MAXN]; // dp[l][r]：区间 [l..r] 分离-合体的最大总价值
int cut[MAXN][MAXN]; // cut[l][r]：取到最大值的最左分离点（1 基）

// 区间 DP 递推：按区间长度从小到大，保证转移用到的子区间已算好
void plan_separations() {
    for (ll len = 2; len <= n; ++len) {
        for (ll l = 1; l + len - 1 <= n; ++l) {
            ll r = l + len - 1;
            ll ends = a[l] + a[r]; // 合体收益里的"区间左右端点价值之和"
            ll best = -1;
            ll best_k = l;
            // 从左往右枚举切点，严格大于才替换：平手保留最左，保证字典序最小
            for (ll k = l; k < r; ++k) {
                ll total = dp[l][k] + dp[k + 1][r] + ends * a[k];
                if (total > best) {
                    best = total;
                    best_k = k;
                }
            }
            dp[l][r] = best;
            cut[l][r] = best_k;
        }
    }
}

// 输出序列重建：把分离树按层（分离阶段）BFS，同一层内区间从左到右
// 由于父子入队有序（父先入队、左孩子先于右孩子），出队顺序恰好满足题目要求
void walk_levels() {
    int head = 0;
    int tail = 0;
    static int ql[MAXN * MAXN]; // 队列存区间左端点
    static int qr[MAXN * MAXN]; // 队列存区间右端点
    if (n < 2) return; // 单个区域无法分离
    ql[tail] = 1; qr[tail] = n; ++tail;
    bool first = true;
    while (head < tail) {
        ll l = ql[head];
        ll r = qr[head];
        ++head;
        ll k = cut[l][r];
        if (!first) printf(" ");
        printf("%lld", k);
        first = false;
        // 左右子区间长度 >= 2 时才需要继续分离，入队
        if (l < k) { ql[tail] = l; qr[tail] = k; ++tail; }
        if (k + 1 < r) { ql[tail] = k + 1; qr[tail] = r; ++tail; }
    }
    printf("\n");
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    plan_separations();
    printf("%lld\n", dp[1][n]);
    walk_levels();
    return 0;
}
