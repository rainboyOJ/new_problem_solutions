/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 01:15
 * update_at: 2026-10-05 01:15
 */
// main.cpp：按 0-18、19-35、36-60、61 以上四段统计患病人数百分比。
#include <cstdio>

typedef long long ll;

const int MAXN = 105;
ll age[MAXN]; // age[i] 表示第 i 个病人的年龄
ll cnt[4];    // cnt[b] 表示第 b 段的人数：0=0-18，1=19-35，2=36-60，3=61 以上

int main() {
    ll n; // 病人总数
    if (scanf("%lld", &n) != 1) {
        return 0;
    }
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &age[i]);
    }

    // 四个年龄段由三个右端点 18、35、60 划分：
    // 年龄严格越过几个右端点，就属于第几段
    for (ll i = 1; i <= n; i++) {
        ll bucket = 0; // 当前年龄所属的年龄段编号
        if (age[i] > 18) {
            bucket++;
        }
        if (age[i] > 35) {
            bucket++;
        }
        if (age[i] > 60) {
            bucket++;
        }
        cnt[bucket]++;
    }

    for (ll b = 0; b < 4; b++) {
        double ratio = cnt[b] * 100.0 / n; // 该段人数占总人数的百分比
        printf("%.2f%%\n", ratio);
    }
    return 0;
}
