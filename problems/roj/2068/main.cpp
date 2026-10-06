/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:58
 * update_at: 2026-10-06 10:58
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 传动比 a/b 用整数 a * W[b] 表示（W[b] = L / b，L 是 5..40 的公倍数），
// 这样传动比、相邻差、方差分数全部是精确整数运算，没有浮点误差。
const ll L_LCM = 5342931457063200LL; // lcm(5,6,...,40)
ll W[45]; // W[b] = L_LCM / b，下标 5..40 有效

ll F, R;                 // 前、后齿轮个数
ll f1, f2, r1, r2;       // 前、后齿轮齿数的可选区间
ll front_g[10];          // 当前枚举的前齿轮组合（升序）
ll rear_g[11];           // 当前枚举的后齿轮组合（升序）
ll f_min, f_max;         // 当前前齿轮组合的最小 / 最大齿数
ll nums[55];             // 当前方案的 F*R 个传动比整数，排序后求相邻差

ll ans_front[10];        // 答案：前齿轮组合
ll ans_rear[11];         // 答案：后齿轮组合
bool has_ans = false;    // 是否已找到合法方案
__int128 best_score;     // 当前最优的方差分数（可能超过 ll，用 __int128 精确保存）

// 用当前 front_g / rear_g 组合计算“比较用方差分数”：
//   m*Σ(相邻差)^2 - (首尾差)^2，其中 m = F*R - 1 是相邻差的个数。
// 真实方差 = 分数 / (L^2 * m^2)，L、m 对每个方案相同，所以分数越小方差越小。
// 大小估计：span <= 80*W[5] 约 8.6e16，m <= 49，
//   m*Σd^2 <= 49*49*7.4e33 约 1.8e37，在 __int128 范围内。
__int128 calc_score() {
    ll n = F * R;
    ll idx = 0;
    for (ll j = 0; j < R; j++) {
        for (ll i = 0; i < F; i++) {
            nums[idx] = front_g[i] * W[rear_g[j]];
            idx++;
        }
    }
    sort(nums, nums + n);
    ll m = n - 1; // 相邻差个数
    __int128 sq = 0;              // Σ(相邻差)^2
    for (ll k = 0; k + 1 < n; k++) {
        ll d = nums[k + 1] - nums[k];
        sq += (__int128)d * d;
    }
    __int128 span = nums[n - 1] - nums[0]; // Σd = 最大比 - 最小比（望远镜求和）
    return (__int128)m * sq - span * span;
}

// 分数严格更小才更新：前后齿轮都是升序枚举，天然保证并列时取字典序最小的组合。
void try_update() {
    __int128 score = calc_score();
    if (has_ans && score >= best_score) return;
    has_ans = true;
    best_score = score;
    for (ll i = 0; i < F; i++) ans_front[i] = front_g[i];
    for (ll j = 0; j < R; j++) ans_rear[j] = rear_g[j];
}

// 枚举后齿轮组合：这一层在后齿轮区间里选第 dep 个齿数（保持升序）。
// 剪枝 1：第一个（最小）齿数 b 若连配上最大后齿 r2 都不满足 3 倍约束，更大的 b 只会更差，直接断开。
// 剪枝 2：选最后一个齿数时，必须 >= ceil(3*f_min*rear_g[0]/f_max) 才可能合法，从下界起选，
//         对 R=2 相当于一个非法齿对都不会被访问。
void dfs_rear(ll dep, ll start) {
    if (dep == R) {
        // 完整后齿轮组合已生成：3 倍约束 最大比 >= 3*最小比
        // 即 f_max/rear_min >= 3*f_min/rear_max，交叉相乘成整数比较
        if (f_max * rear_g[R - 1] >= 3 * f_min * rear_g[0]) {
            try_update();
        }
        return;
    }
    for (ll b = start; b <= r2; b++) {
        if (dep == 0 && f_max * r2 < 3 * f_min * b) break; // 最小齿数再增大只会更不合法
        rear_g[dep] = b;
        if (dep == R - 1) {
            ll lo = (3 * f_min * rear_g[0] + f_max - 1) / f_max; // 最后一个齿数的合法下界（向上取整）
            if (b < lo) continue;
        }
        dfs_rear(dep + 1, b + 1);
    }
}

// 枚举前齿轮组合：这一层在前齿轮区间里选第 dep 个齿数（保持升序）。
// 升序枚举即字典序，并列规则由“分数严格更小才更新”自动满足。
void dfs_front(ll dep, ll start) {
    if (dep == F) {
        f_min = front_g[0];
        f_max = front_g[F - 1];
        dfs_rear(0, r1);
        return;
    }
    for (ll a = start; a <= f2; a++) {
        front_g[dep] = a;
        dfs_front(dep + 1, a + 1);
    }
}

int main() {
    // 预处理 W[b] = L / b，把分数 a/b 变成整数 a * W[b]
    for (ll b = 5; b <= 40; b++) {
        W[b] = L_LCM / b;
    }

    cin >> F >> R;
    cin >> f1 >> f2 >> r1 >> r2;

    dfs_front(0, f1);

    // 输出前、后齿轮齿数（升序）
    for (ll i = 0; i < F; i++) {
        cout << ans_front[i] << " \n"[i == F - 1];
    }
    for (ll j = 0; j < R; j++) {
        cout << ans_rear[j] << " \n"[j == R - 1];
    }
    return 0;
}
