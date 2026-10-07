/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:31
 * update_at: 2026-10-05 12:31
 */
// 斜率优化 DP：猫压成 a = T - s[H] 后排序，P 位饲养员各接一段连续的猫，
// 转移整理成直线族（斜率 -k、截距 f[k]+S[k]），双单调用单调队列维护下凸壳。

#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 山和猫的数量上限
const ll INF = 4e18;     // 不可达 DP 值的哨兵

ll n, m, p;      // 山数、猫数、饲养员数
ll s[MAXN];      // s[h]：1 号山走到 h 号山的时间（距离前缀和）
ll a[MAXN];      // a[i]：第 i 只猫（排序后）能被接走的出发时刻下限
ll pre[MAXN];    // pre[i]：a 的前缀和
ll f[2][MAXN];   // 滚动数组：f[cur][r] = 前 r 只猫用当前位数饲养员的最小等待和

struct Cat {
    ll h;
    ll t;
};
Cat cats[MAXN]; // 每只猫所在山编号与玩到时刻

// 判断队尾直线 (m2,b2) 是否被新线 (m1,b1) 与队尾前一条线 (m3,b3) 夹死（生效区间为空）
// 即新线与队尾线的交点 x12 不晚于队尾线与前一条线的交点 x23，交叉相乘避免除法
bool bad_line(ll m1, ll b1, ll m2, ll b2, ll m3, ll b3) {
    // x12 <= x23，即 (b2-b1)*(m2-m3) <= (b3-b2)*(m1-m2)；
    // b 可达 2e14、斜率差可达 1e5，乘积可超 ll，用 __int128 承接
    __int128 lhs = b2 - b1;
    lhs *= m2 - m3;
    __int128 rhs = b3 - b2;
    rhs *= m1 - m2;
    return lhs <= rhs;
}

// 用上一层 DP 值 prevdp[] 推进一层：
// f[r] = min_k prevdp[k] + (r-k)*a_r - (pre[r]-pre[k])
// 把每个切点 k 看成直线 y = -k*x + (prevdp[k]+pre[k])，查询点 x = a_r
void dp_layer(ll *prevdp, ll *curdp) {
    // dq 存直线 (斜率, 截距)，斜率自队头向队尾递减（k 递增）
    deque<pair<ll, ll> > dq;
    for (ll r = 0; r <= m; r++) {
        if (prevdp[r] < INF) { // 不可达切点不入壳
            ll nm = -r, nb = prevdp[r] + pre[r];
            // 队尾直线的生效区间被新线截空则弹出（交点比较交叉相乘，整数精确）
            while (dq.size() >= 2 && bad_line(nm, nb, dq.back().first,
                   dq.back().second, dq[dq.size() - 2].first, dq[dq.size() - 2].second))
                dq.pop_back();
            dq.push_back(make_pair(nm, nb));
        }
        if (r == 0) {
            curdp[0] = 0; // 0 只猫费用恒为 0，也是下一层 k=0 的直线来源
            continue;
        }
        ll x = a[r]; // 查询点：段尾猫的出发时刻下限，随 r 非降
        // 查询点递增，队头若已不如第二条则永远不再最优，弹出
        while (dq.size() >= 2 && dq.front().first * x + dq.front().second >=
               dq[1].first * x + dq[1].second)
            dq.pop_front();
        curdp[r] = r * x - pre[r] + dq.front().first * x + dq.front().second;
    }
}

void read_input() {
    cin >> n >> m >> p;
    s[1] = 0;
    for (ll i = 2; i <= n; i++) {
        cin >> s[i];
        s[i] += s[i - 1];
    }
    for (ll i = 1; i <= m; i++) {
        cin >> cats[i].h >> cats[i].t;
    }
}

void solve() {
    // 每只猫压成 a = T - s[H]：饲养员不早于 a 出发才接得到，等待 = 出发时刻 - a
    for (ll i = 1; i <= m; i++) {
        a[i] = cats[i].t - s[cats[i].h];
    }
    sort(a + 1, a + m + 1);
    for (ll i = 1; i <= m; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    // 初始：0 位饲养员一只猫也接不到，只有 f[0]=0 可达
    for (ll r = 1; r <= m; r++) {
        f[0][r] = INF;
    }
    f[0][0] = 0;
    ll cur = 0; // 滚动数组当前层下标
    for (ll layer = 1; layer <= p; layer++) {
        dp_layer(f[cur], f[cur ^ 1]);
        cur ^= 1;
    }
    cout << f[cur][m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
