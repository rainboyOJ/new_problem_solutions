/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 505;
ll top1[MAXN]; // top1[i]：i 号武将关联的最大默契值
ll top2[MAXN]; // top2[i]：i 号武将关联的次大默契值

// 用边权 w 刷新武将 v 的最大、次大默契值
void keep_top2(int v, ll w) {
    if (w > top1[v]) {
        top2[v] = top1[v]; // 原最大降级为次大
        top1[v] = w;
    } else if (w > top2[v]) {
        top2[v] = w;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    // 第 i+1 行给出 i 号与 i+1..n 号武将的默契值
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            ll w;
            scanf("%lld", &w);
            keep_top2(i, w); // 边 (i, j) 对两端各自刷新
            keep_top2(j, w);
        }
    }

    // 电脑每手只破坏"最强组合"，小涵能稳拿的只有次大值；
    // 取次大值最大的武将先手，电脑必抢其最强搭档，小涵再抢次强搭档即可必胜。
    ll ans = 0;
    for (int v = 1; v <= n; v++) {
        ans = max(ans, top2[v]);
    }
    printf("1\n%lld\n", ans);
    return 0;
}
