/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 字符串折叠：区间 DP + 按决策还原最短折叠串
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int MAXN = 512;

char s[MAXN];
int f[MAXN][MAXN];   // f[i][j]：s[i..j] 展开前的最少字符数
int cut[MAXN][MAXN]; // cut[i][j]：拼接时的断点（左半段的右端点）
int rep[MAXN][MAXN]; // rep[i][j]：整体折叠的循环节长度 p，0 表示不折叠

// 按 DP 记录的决策还原 s[i..j] 的最优折叠串：折叠优先，其次按断点拆两半
string unfold(int i, int j) {
    if (i == j) {
        return string(1, s[i]);
    }
    int p = rep[i][j];
    if (p) {
        int times = (j - i + 1) / p;
        char buf[16];
        sprintf(buf, "%d", times);
        return string(buf) + "(" + unfold(i, i + p - 1) + ")";
    }
    int k = cut[i][j];
    return unfold(i, k) + unfold(k + 1, j);
}

int main() {
    if (scanf("%500s", s) != 1) {
        return 0;
    }
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        f[i][i] = 1;
    }
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            // 拼接：枚举断点取最优（并列时取最小的断点）
            int best = f[i][i] + f[i + 1][j], best_k = i;
            for (int k = i + 1; k < j; k++) {
                int v = f[i][k] + f[k + 1][j];
                if (v < best) {
                    best = v;
                    best_k = k;
                }
            }
            f[i][j] = best;
            cut[i][j] = best_k;
            // 折叠：循环节长度 p 必须整除区间长度，且各块完全相同
            for (int p = 1; p <= length / 2; p++) {
                if (length % p) {
                    continue;
                }
                if (memcmp(s + i, s + i + p, j + 1 - p - i) != 0) {
                    continue;
                }
                int digits = 0, t = length / p;
                while (t) {
                    digits++;
                    t /= 10;
                }
                int total = f[i][i + p - 1] + digits + 2; // 重复次数 + 一对括号
                if (total < f[i][j]) {                    // 严格更短才改写决策
                    f[i][j] = total;
                    rep[i][j] = p;
                }
            }
        }
    }
    string ans = unfold(0, n - 1);
    printf("%s\n", ans.c_str());
    return 0;
}
