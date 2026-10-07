/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:02
 * update_at: 2026-10-05 23:03
 */
#include <iostream>
using namespace std;

const int MAXN = 200005;

typedef long long ll;

ll n;
ll sw[MAXN];   // sw[i] = 前 i 棵树的总重量
ll swd[MAXN];  // swd[i] = 前 i 棵树的 Σ w_k·pos_k
ll f[MAXN];    // f[i] = 较低的厂建在树 i 时，树 1..i 的最小运费（较高的厂在其上游）

// 下凸壳，维护若干条直线 y = m·x + b，按斜率递减的顺序存放
ll hull_m[MAXN]; // 候选直线的斜率 m_j = -sw[j]
ll hull_b[MAXN]; // 候选直线的截距 b_j = sw[j]·pos_j
int head_pos;    // 队头指针：查询点单调不减，只前进
int tail_pos;    // 队尾指针：新直线从队尾进入

// 把直线 y = s·x + b 加入下凸壳（斜率 s 比壳内所有直线都小）
void hull_add(ll s, ll b) {
    // 若「尾前直线 l1 与尾直线 l2」的交点不低于「尾直线 l2 与新直线 l3」的交点，
    // 则 l2 被完全压住，弹出。交点比较用交叉相乘，避免除法与浮点。
    while (tail_pos - head_pos >= 2) {
        ll m1 = hull_m[tail_pos - 2], c1 = hull_b[tail_pos - 2];
        ll m2 = hull_m[tail_pos - 1], c2 = hull_b[tail_pos - 1];
        // x(l1,l2) = (c2-c1)/(m1-m2)，x(l2,l3) = (b-c2)/(m2-s)，两条分母都为正
        if ((c2 - c1) * (m2 - s) >= (b - c2) * (m1 - m2)) {
            tail_pos--;
        } else {
            break;
        }
    }
    hull_m[tail_pos] = s;
    hull_b[tail_pos] = b;
    tail_pos++;
}

// 查询凸壳在横坐标 x 处的最小值
ll hull_query(ll x) {
    while (tail_pos - head_pos >= 2 &&
           hull_m[head_pos] * x + hull_b[head_pos] >=
               hull_m[head_pos + 1] * x + hull_b[head_pos + 1]) {
        head_pos++;
    }
    return hull_m[head_pos] * x + hull_b[head_pos];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    ll pos = 0; // 当前树到山顶的距离 pos_i，山顶处 pos_1 = 0
    for (ll i = 1; i <= n; i++) {
        ll w, d;
        cin >> w >> d;
        sw[i] = sw[i - 1] + w;
        swd[i] = swd[i - 1] + w * pos;

        // f[i] = sw[i]·pos_i - swd[i] + min_{j<i} ( sw[j]·pos_j - sw[j]·pos_i )
        // 后一项是候选直线族在 x = pos_i 处的最小值，用下凸壳 O(1) 取得
        if (i > 1) {
            f[i] = sw[i] * pos - swd[i] + hull_query(pos);
        }

        hull_add(-sw[i], sw[i] * pos); // 树 i 成为「较高的厂」的候选
        pos += d;                      // 推进到下一棵树，读完 d_n 后即山脚
    }

    // 循环结束时 pos = pos_{n+1}（山脚）。尾段：树 i+1..n 全部运到山脚的费用
    ll ans = -1;
    for (ll i = 2; i <= n; i++) {
        ll tail_cost = (sw[n] - sw[i]) * pos - (swd[n] - swd[i]);
        ll total = f[i] + tail_cost;
        if (ans < 0 || total < ans) {
            ans = total;
        }
    }

    cout << ans << "\n";
    return 0;
}
