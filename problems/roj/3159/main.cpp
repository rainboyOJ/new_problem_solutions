/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <cstdio>
#include <deque>
using namespace std;

typedef long long ll;
typedef __int128 lll; // 叉积可能超过 long long 范围，用 128 位

const int MAXN = 300005;

ll task_time[MAXN]; // 第 i 个任务的执行时间 T_i
ll task_cost[MAXN]; // 第 i 个任务的费用系数 C_i
ll n, s;

deque<pair<ll, ll> > hull; // 下凸壳上的直线 (斜率 m, 截距 b)，斜率随插入递减

// 128 位乘法：参数直接声明成 128 位，靠隐式转换避免出现强制转换
lll mul(lll a, lll b) { return a * b; }

// 把直线 y = m*x + b 压入凸壳尾部。
// 若队尾直线在新直线与次队尾直线的交点之上（三点不再构成下凸），它永远取不到最小值，弹掉。
void push_line(ll m, ll b) {
    while (hull.size() >= 2) {
        ll m1 = hull[hull.size() - 2].first, b1 = hull[hull.size() - 2].second;
        ll m2 = hull[hull.size() - 1].first, b2 = hull[hull.size() - 1].second;
        if (mul(b2 - b1, m2 - m) < mul(b - b2, m1 - m2)) break; // 队尾仍是凸壳顶点
        hull.pop_back();
    }
    hull.push_back(make_pair(m, b));
}

// 查询所有已插入直线在 x 处的最小值。
// 查询点 x 严格递增，最优直线沿凸壳单调右移，队首弹出即可均摊 O(1)。
ll min_line(ll x) {
    while (hull.size() >= 2
           && hull[0].first * x + hull[0].second >= hull[1].first * x + hull[1].second)
        hull.pop_front();
    return hull[0].first * x + hull[0].second;
}

int main() {
    scanf("%lld%lld", &n, &s); // S 是每批任务开始前的启动时间
    ll total_cost = 0;
    for (ll i = 1; i <= n; i++) {
        scanf("%lld%lld", &task_time[i], &task_cost[i]);
        total_cost += task_cost[i];
    }
    // f[i]：前 i 个任务的最小总费用（已把启动时间折算给「它及之后所有任务」）
    // f[i] = sc[i]*st[i] + S*total_cost + min_j { -sc[j]*(st[i]+S) + f[j] }
    // 每个决策 j 是一条斜率 -sc[j] 递减的直线，查询点 st[i]+S 递增 → 单调队列凸壳
    ll dp = 0, st = 0, sc = 0; // dp = f[0] = 0
    for (ll i = 1; i <= n; i++) {
        push_line(-sc, dp); // 此刻 sc、dp 仍是第 i-1 轮的值
        st += task_time[i];
        sc += task_cost[i];
        dp = sc * st + s * total_cost + min_line(st + s);
    }
    printf("%lld\n", dp);
    return 0;
}
