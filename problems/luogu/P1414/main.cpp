/**
 * P1414 又是毕业季II
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXV = 1000005;

int freq[MAXV];       // 每个数的出现次数
int cnt[MAXN];        // cnt[k] = 能被 k 个数同时整除的最大值
int n, max_val;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        ++freq[x];
        if (x > max_val) max_val = x;
    }
    // 对每个可能的约数 d，统计有多少个数是 d 的倍数
    for (int d = 1; d <= max_val; ++d) {
        int total = 0;
        for (int m = d; m <= max_val; m += d)
            total += freq[m];
        // 如果有 total 个数能被 d 整除，则 cnt[total] = max(cnt[total], d)
        if (total) cnt[total] = max(cnt[total], d);
    }
    // 后缀取最大：cnt[k] 至少是 cnt[k+1]
    for (int k = n - 1; k >= 1; --k)
        cnt[k] = max(cnt[k], cnt[k + 1]);
    for (int k = 1; k <= n; ++k)
        printf("%d\n", cnt[k]);
    return 0;
}
