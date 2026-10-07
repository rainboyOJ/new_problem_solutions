/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:23
 * update_at: 2026-10-05 23:23
 */
// main.cpp：「一本通 1.1 例 2」种树，区间贪心：按右端点排序，缺树时从右往左补种。
// 输出最少种树数以及每棵树的位置。

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 30005; // 地块数上限
const int MAXM = 5005;  // 居民需求数上限

// 一条居民需求：区间 [b, e] 内至少种 t 棵树
struct Demand {
    ll b, e, t;
};

ll n, m;
Demand d[MAXM];
bool planted[MAXN]; // planted[pos] = true 表示位置 pos 已种树

// 贪心比较：按区间右端点 e 从小到大排序
bool cmp_e(const Demand &a, const Demand &b) {
    return a.e < b.e;
}

int main() {
    scanf("%lld %lld", &n, &m);
    for (int i = 1; i <= m; i++)
        scanf("%lld %lld %lld", &d[i].b, &d[i].e, &d[i].t);

    // 右端点小的区间先处理，后面的区间才能复用靠右种的树
    sort(d + 1, d + m + 1, cmp_e);

    ll total = 0; // 总共种下的树数
    for (int i = 1; i <= m; i++) {
        // 先统计当前区间 [b, e] 内已经种了多少棵
        ll has = 0;
        for (ll p = d[i].b; p <= d[i].e; p++)
            if (planted[p])
                has++;

        // 还缺 need 棵，从右端点向左找空位补种，
        // 靠右种最容易被后面的区间复用
        ll need = d[i].t - has;
        for (ll p = d[i].e; p >= d[i].b && need > 0; p--) {
            if (!planted[p]) {
                planted[p] = true;
                total++;
                need--;
            }
        }
    }

    printf("%lld\n", total);
    // 逐棵输出位置，位置之间用空格分隔，行尾不留多余空格
    bool first = true;
    for (ll p = 1; p <= n; p++)
        if (planted[p]) {
            if (first) {
                printf("%lld", p);
                first = false;
            } else
                printf(" %lld", p);
        }
    printf("\n");
    return 0;
}
