/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:23
 * update_at: 2026-10-05 11:23
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 105;   // 行数上限
const int MAXM = 10;    // 列数上限，状态压缩按 M<=10
const int MAXS = 70;    // 单行合法状态数（M<=10 时最多 60 种）

int n, m;                       // 网格行数、列数
int hillMask[MAXN];             // hillMask[i]：第 i 行山地的列掩码（H 为 1）
ll numState;                    // 单行合法状态总数
ll states[MAXS];                // states[i]：第 i 个单行合法状态（行内间距 > 2）
ll stateCnt[MAXS];              // stateCnt[i]：该状态的置位数，即该行炮兵数
ll dp[MAXS][MAXS];              // dp[s1][s2]：上一行状态 s1、当前行状态 s2 时的最大炮兵数
ll tmp[MAXS][MAXS];             // tmp：滚动转移用的临时数组
ll candidateCnt;                // 当前行的候选状态数（不压山地的合法状态）
ll candidates[MAXS];            // candidateCnt 个候选状态的下标

// 判断单行状态是否合法：任意两个炮兵列间距必须大于 2
bool rowValid(ll mask) {
    if (mask & (mask << 1)) return false;   // 相邻两位不能同时有炮兵
    if (mask & (mask << 2)) return false;   // 间隔一位也不能同时有炮兵
    return true;
}

// 统计掩码中 1 的个数
ll countBits(ll x) {
    ll c = 0;
    while (x > 0) {
        c += x & 1;
        x >>= 1;
    }
    return c;
}

void solve() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        char row[MAXM + 5];
        scanf("%s", row);
        hillMask[i] = 0;
        // 从左到右读入地形，最高位对应第 0 列
        for (int j = 0; j < m; j++) {
            if (row[j] == 'H') hillMask[i] |= 1 << (m - 1 - j);
        }
    }

    // 预处理所有单行合法状态
    numState = 0;
    for (ll mask = 0; mask < (1LL << m); mask++) {
        if (rowValid(mask)) {
            states[numState] = mask;
            stateCnt[numState] = countBits(mask);
            numState++;
        }
    }

    // 初始 DP：前两行都不部署（状态 0），价值 0
    memset(dp, -1, sizeof(dp));
    dp[0][0] = 0;

    // 逐行转移：枚举上一行状态 s1、当前行状态 s2
    for (int i = 0; i < n; i++) {
        // 收集当前行的候选状态：合法且不压山地
        candidateCnt = 0;
        for (ll k = 0; k < numState; k++) {
            if ((states[k] & hillMask[i]) == 0) {
                candidates[candidateCnt++] = k;
            }
        }

        memset(tmp, -1, sizeof(tmp));
        for (ll k1 = 0; k1 < numState; k1++) {          // 上一行状态
            for (ll k2 = 0; k2 < numState; k2++) {      // 当前行候选状态
                if (dp[k1][k2] < 0) continue;           // 不可达
                for (ll t = 0; t < candidateCnt; t++) { // 下一行状态
                    ll k3 = candidates[t];
                    ll s2 = states[k2];
                    ll s3 = states[k3];
                    // 纵向攻击距离 2：与当前行、上一行都不能同列冲突
                    if (s3 & s2) continue;
                    if (s3 & states[k1]) continue;
                    ll newVal = dp[k1][k2] + stateCnt[k3];
                    if (newVal > tmp[k2][k3]) tmp[k2][k3] = newVal;
                }
            }
        }
        // 滚动到下一行
        memcpy(dp, tmp, sizeof(dp));
    }

    // 答案为所有状态对中的最大值
    ll ans = 0;
    for (ll k1 = 0; k1 < numState; k1++) {
        for (ll k2 = 0; k2 < numState; k2++) {
            if (dp[k1][k2] > ans) ans = dp[k1][k2];
        }
    }
    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
