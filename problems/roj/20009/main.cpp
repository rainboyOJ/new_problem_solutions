/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 08:59
 * update_at: 2026-10-06 08:59
 */
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 100005;

int n;              // 史莱姆数量
ll cap;             // 吊桥最大载重
ll a[MAXN];         // 每只史莱姆的重量

int main() {
    scanf("%d %lld", &n, &cap);
    for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    std::sort(a + 1, a + n + 1);

    // 最重的必须过桥：能和最轻的挤一趟就同乘，否则独占一趟。
    // 每趟耗时都是 1，趟数 = n - 成功同乘的对数，一趟最多消化两只。
    int light = 1, heavy = n;
    ll trips = 0;
    while (light <= heavy) {
        trips++;
        if (a[light] + a[heavy] <= cap)
            light++;       // 最轻的搭上这趟，向内收一格
        heavy--;           // 最重的总是从这趟离开
    }
    printf("%lld\n", trips);
    return 0;
}
