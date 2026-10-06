/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:13
 * update_at: 2026-10-06 11:14
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 12; // 题目要求输出 n = 1..12 的答案

ll f[MAXN + 1]; // f[n] 表示 n 个盘从 A 柱搬到 D 柱的最少步数，f[0] = 0

int main() {
    // 四塔汉诺塔 Frame-Stewart 递推：
    // 先用四塔把 k 个最小盘搬到中转柱（f[k] 步），
    // 再用三塔把剩下 n-k 个大盘搬到 D 柱（2^{n-k} - 1 步），
    // 最后用四塔把 k 个最小盘接到 D 柱（又是 f[k] 步）。
    // k = 0 对应不借第四座塔，即标准三塔搬法。
    for (int n = 1; n <= MAXN; n++) {
        f[n] = (1LL << n) - 1; // 先取三塔上界
        for (int k = 0; k < n; k++) {
            ll cur = 2 * f[k] + (1LL << (n - k)) - 1;
            if (cur < f[n]) f[n] = cur;
        }
    }

    for (int n = 1; n <= MAXN; n++) {
        printf("%lld\n", f[n]);
    }
    return 0;
}
