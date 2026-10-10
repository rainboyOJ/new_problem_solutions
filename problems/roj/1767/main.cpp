/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 00:09
 * update_at: 2026-10-08 00:09
 */
// 一本通 1767《字符合并》：[HAOI2016] 字符合并 同源。
// 区间 DP + 状压：区间 [l, r] 无论怎么合并，最终残留长度恒为 (len-1) % (k-1) + 1，
// 而 k <= 8 说明残留串最多 k-1 = 7 位，可以整个塞进状态里。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 305;               // n <= 300，留安全系数
const int MAXK = 8;
const int MAXS = 1 << (MAXK - 1);   // 残留长度 <= k-1 <= 7，故残留串形态最多 2^7 = 128 种

struct Rule {
    int ch;                         // 合并后得到的新字符
    ll score;                       // 本次合并获得的分数
};

int n, k;
int a[MAXN];                        // a[1..n]：初始 01 串
Rule rule[1 << MAXK];               // rule[i]：i 的 k 位二进制（最高位为最左字符）对应的合并规则
// f[l][r][S]：把 a[l..r] 合并到不能再合并、且残留串恰为 S（长度 (r-l) % (k-1) + 1）时的最大得分
ll f[MAXN][MAXN][MAXS];

const ll NEG = -1000000000000000000LL;  // 不可达状态的哨兵；合法得分一定 >= 0

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int tot = 1 << k;
    for (int i = 0; i < tot; i++) scanf("%d%lld", &rule[i].ch, &rule[i].score);

    int km1 = k - 1;                // 每次合并净减少 k-1 个字符，这就是长度不变量
    int smax = 1 << km1;            // 残留串形态总数

    for (int l = 1; l <= n; l++)
        for (int r = 1; r <= n; r++)
            for (int s = 0; s < smax; s++) f[l][r][s] = NEG;
    for (int i = 1; i <= n; i++) f[i][i][a[i]] = 0;   // 单字符区间残留它自己，得分为 0

    for (int len = 2; len <= n; len++) {
        int rest = (len - 1) % km1;     // 该区间残留长度 = rest + 1
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            if (rest == 0) {
                // 残留 1 个字符：先拼满 k 位，再整体合并一次。
                // 后缀 [mid+1, r] 必须恰好收成 1 个字符，故 mid 以 k-1 为步长倒着取。
                ll best[2] = {NEG, NEG};
                for (int mid = r - 1; mid >= l; mid -= km1) {
                    for (int s = 0; s < smax; s++) {          // 前缀残留 k-1 位
                        ll base = f[l][mid][s];
                        if (base <= NEG / 2) continue;
                        for (int b = 0; b < 2; b++) {
                            ll tail = f[mid + 1][r][b];
                            if (tail <= NEG / 2) continue;
                            int id = (s << 1) | b;            // 拼出的 k 位串
                            ll val = base + tail + rule[id].score;
                            if (val > best[rule[id].ch]) best[rule[id].ch] = val;
                        }
                    }
                }
                f[l][r][0] = best[0];
                f[l][r][1] = best[1];
            } else {
                // 残留 rest + 1 个字符：前缀 [l, mid] 残留 rest 位，末尾再拼后缀的 1 个字符
                for (int mid = r - 1; mid >= l; mid -= km1) {
                    int lim = 1 << rest;
                    for (int s = 0; s < lim; s++) {
                        ll base = f[l][mid][s];
                        if (base <= NEG / 2) continue;
                        for (int b = 0; b < 2; b++) {
                            ll tail = f[mid + 1][r][b];
                            if (tail <= NEG / 2) continue;
                            int id = (s << 1) | b;
                            ll val = base + tail;
                            if (val > f[l][r][id]) f[l][r][id] = val;
                        }
                    }
                }
            }
        }
    }

    // w_i >= 1，合并只会加分，所以整串一定合并到最短，答案取残留串各形态的最大值
    ll ans = NEG;
    for (int s = 0; s < smax; s++) ans = max(ans, f[1][n][s]);
    printf("%lld\n", ans);
    return 0;
}
