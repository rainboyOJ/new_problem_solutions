/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 括号序列计数：四维 DP，深度不超过 d 的 SS 串数
#include <cstdio>
using namespace std;

typedef long long ll;

const int MOD = 11380; // 题面里的“当前年份”
const int MAXL = 12;   // 每种括号的对数上界
const int MAXD = 32;   // 深度上界

// le[d][i][j][k]：深度不超过 d、含 i 对 {}、j 对 []、k 对 () 的 SS 串数
ll le[MAXD][MAXL][MAXL][MAXL];

int main() {
    int L1, L2, L3, D;
    if (scanf("%d %d %d %d", &L1, &L2, &L3, &D) != 4) {
        return 0;
    }
    int total = L1 + L2 + L3;
    if (D > total) {
        printf("0\n"); // 每层嵌套至少吃掉一对括号
        return 0;
    }

    for (int i = 0; i <= L1; i++) {
        for (int j = 0; j <= L2; j++) {
            for (int k = 0; k <= L3; k++) {
                le[0][i][j][k] = (i == 0 && j == 0 && k == 0) ? 1 : 0;
            }
        }
    }

    for (int d = 1; d <= D; d++) {
        ll (*prev)[MAXL][MAXL] = le[d - 1]; // 深度不超过 d-1 的表
        ll (*cur)[MAXL][MAXL] = le[d];      // 深度不超过 d 的表
        cur[0][0][0] = 1;                   // 空串深度为 0
        for (int i = 0; i <= L1; i++) {
            for (int j = 0; j <= L2; j++) {
                for (int k = 0; k <= L3; k++) {
                    if (i == 0 && j == 0 && k == 0) {
                        continue;
                    }
                    ll t = 0;
                    // 首原子 (A)：内层只能含 ()，故内层用 prev[0][0][a]
                    for (int a2 = 0; a2 < k; a2++) {
                        t += cur[i][j][k - 1 - a2] * prev[0][0][a2];
                    }
                    // 首原子 [A]：内层不含 {}，故内层用 prev[0][a][b]
                    for (int a2 = 0; a2 < j; a2++) {
                        for (int b2 = 0; b2 <= k; b2++) {
                            t += prev[0][a2][b2] * cur[i][j - 1 - a2][k - b2];
                        }
                    }
                    // 首原子 {A}：三种括号都要在内层与剩余串间分配
                    for (int a2 = 0; a2 < i; a2++) {
                        for (int b2 = 0; b2 <= j; b2++) {
                            for (int c2 = 0; c2 <= k; c2++) {
                                t += prev[a2][b2][c2] * cur[i - 1 - a2][j - b2][k - c2];
                            }
                        }
                    }
                    cur[i][j][k] = t % MOD;
                }
            }
        }
    }

    // 深度恰为 D = 深度不超过 D 减去深度不超过 D-1
    ll ans;
    if (D == 0) {
        ans = le[0][L1][L2][L3];
    } else {
        ans = le[D][L1][L2][L3] - le[D - 1][L1][L2][L3];
    }
    ans %= MOD;
    if (ans < 0) {
        ans += MOD;
    }
    printf("%lld\n", ans);
    return 0;
}
