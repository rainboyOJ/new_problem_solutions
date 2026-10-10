/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 能量项链：环形区间 DP，同时保留最大值与最小值（乘法遇负数时最小可能翻成最大）。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll NEG = -1000000000000LL;
const ll MAXN = 105;

ll n;
ll nums[MAXN * 3];
char ops[MAXN * 3]; // ops[(k+1) % n]：顶点 k 与 k+1 之间边上的运算符
ll dp_max[MAXN * 3][MAXN * 3];
ll dp_min[MAXN * 3][MAXN * 3];

int main() {
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    std::vector<char> op(n);
    std::vector<ll> val(n);
    char buf[8];
    for (ll i = 0; i < n; i++) {
        scanf("%s", buf);
        op[i] = buf[0];
        scanf("%lld", &val[i]);
        ops[i] = op[i];
        nums[i] = val[i];
    }

    ll limit = 3 * n + 2;
    for (ll i = 0; i < limit; i++) {
        for (ll j = 0; j < limit; j++) {
            dp_max[i][j] = NEG;
            dp_min[i][j] = -NEG;
        }
    }

    // 顶点 i..j（下标已对 n 取模）合并后的最大 / 最小值
    for (ll length = 1; length <= n; length++) {
        for (ll i = 0; i + length - 1 <= 3 * n; i++) {
            ll j = i + length - 1;
            if (length == 1) {
                dp_max[i][i] = dp_min[i][i] = nums[i % n];
                continue;
            }
            ll best = NEG, worst = -NEG;
            for (ll k = i; k < j; k++) { // 最后一次合并的是顶点 k 与 k+1 之间的边
                char o = ops[(k + 1) % n];
                ll hi = NEG, lo = -NEG;
                ll lv[2], rv[2];
                lv[0] = dp_max[i][k]; lv[1] = dp_min[i][k];
                rv[0] = dp_max[k + 1][j]; rv[1] = dp_min[k + 1][j];
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        ll r = (o == 'x') ? lv[a] * rv[b] : lv[a] + rv[b];
                        if (r > hi) hi = r;
                        if (r < lo) lo = r;
                    }
                }
                if (hi > best) best = hi;
                if (lo > worst) worst = lo; // worst 记录的是 lo 的较大者，用于最终取最小
            }
            dp_max[i][j] = best;
            dp_min[i][j] = (length == 1) ? best : 0;
            // 重新求真正的最小值：上面 worst 的语义容易混，这里直接再扫一遍
            ll realmin = 0;
            bool has = false;
            for (ll k = i; k < j; k++) {
                char o = ops[(k + 1) % n];
                ll lv[2], rv[2];
                lv[0] = dp_max[i][k]; lv[1] = dp_min[i][k];
                rv[0] = dp_max[k + 1][j]; rv[1] = dp_min[k + 1][j];
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        ll r = (o == 'x') ? lv[a] * rv[b] : lv[a] + rv[b];
                        if (!has || r < realmin) {
                            realmin = r;
                            has = true;
                        }
                    }
                }
            }
            dp_min[i][j] = realmin;
        }
    }

    std::vector<ll> scores(2 * n, 0);
    for (ll i = 0; i < 2 * n; i++) {
        scores[i] = dp_max[i][i + n - 1];
    }
    ll best_score = scores[0];
    for (ll i = 1; i < 2 * n; i++) {
        if (scores[i] > best_score) best_score = scores[i];
    }

    printf("%lld\n", best_score);
    bool first = true;
    for (ll i = 0; i < n; i++) {
        if (scores[i] == best_score) {
            if (!first) printf(" ");
            printf("%lld", i + 1);
            first = false;
        }
    }
    printf("\n");
    return 0;
}
