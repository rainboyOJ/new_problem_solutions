/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:29
 * update_at: 2026-10-04 23:29
 */
#include <cstdio>

typedef long long ll;

const ll MAXN = 50005;

ll L, n, m;              // 河道长 L，中间岩石数 n，最多移走 m 个
ll d[MAXN];              // d[i] = 第 i 个岩石到起点的距离（输入已升序）

// 判定：要求最短跳跃距离 >= x 时，最少需要移走几个岩石
// 从左往右贪心保留"最早可行"的岩石，保留点越靠左后面越宽松，所以是最优的
ll need_remove(ll x) {
    ll limit = L - x;    // 保留点最远只能到 L-x，否则最后一跳不足 x
    ll removed = 0;
    ll last = 0;         // 上一个保留点，起点从 0 开始
    for (ll i = 1; i <= n; ++i) {
        // 越过 limit 的岩石必删：终点不可移走，末跳必须 >= x
        // 与上一个保留点距离不足 x 的也要删
        if (d[i] > limit || d[i] - last < x)
            ++removed;
        else
            last = d[i];
    }
    return removed;
}

int main() {
    scanf("%lld %lld %lld", &L, &n, &m);
    for (ll i = 1; i <= n; ++i)
        scanf("%lld", &d[i]);

    // 对答案二分：need_remove(x) 随 x 单调不减，可行域是前缀 [1, x*]
    // 岩石位置互异整数，x=1 恒可行；x=L 时全删，M=N 时可达
    ll lo = 1, hi = L;
    while (lo < hi) {
        ll mid = (lo + hi + 1) / 2;   // 上取整，lo 只被可行解抬高，不会死循环
        if (need_remove(mid) <= m)
            lo = mid;                 // mid 可行，抬高下界
        else
            hi = mid - 1;
    }

    printf("%lld\n", lo);
    return 0;
}
