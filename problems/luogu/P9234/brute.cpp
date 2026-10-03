/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-03 11:20
 *
 * P9234 [蓝桥杯 2023 省 A] 买瓜 —— 暴力对拍解
 *
 * 每个瓜枚举三种去向（不买 / 买半个 / 买整个），3^n 穷举所有方案，
 * 取能凑出恰好 m 的方案中最少的劈瓜数。n<=12 时约 5*10^5 种，足够对拍。
 *
 * 同样把重量统一乘 2，半个瓜的重量就是整数，避免浮点误差。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 35;

int n;
ll m;
ll a[maxn];   // 已乘 2 的重量
ll target;
int best;

// dep: 第几个瓜；sum: 当前重量和（乘 2 后）；cuts: 已劈瓜数
void dfs(int dep, ll sum, int cuts) {
    if (cuts >= best) return;      // 已经不比当前最优更好
    if (dep == n) {
        if (sum == target) best = cuts;
        return;
    }
    if (sum > target) return;      // 重量都是正的，超了就回不去
    dfs(dep + 1, sum, cuts);                        // 不买
    dfs(dep + 1, sum + a[dep], cuts + 1);           // 买半个，劈一刀
    dfs(dep + 1, sum + 2 * a[dep], cuts);           // 买整个
}

int main() {
    scanf("%d %lld", &n, &m);
    target = 2 * m;
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    // a[i] 保持原重量：放大后的模型里，半个瓜贡献 a[i]，整个瓜贡献 2*a[i]。
    best = n + 1;
    dfs(0, 0, 0);
    if (best > n) printf("-1\n");
    else printf("%d\n", best);
    return 0;
}
