/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 11:13
 * update_at: 2026-10-09 11:41
 */

/* ROJ 3165 「Buy Low Buy Lower」低买 */

/* ⚠ 题面与真实数据不符：题面是「最长严格递减子序列 + 方案数」，真实数据是
 * POJ 2828 Buy Tickets 插队问题。这里按真实数据实现。
 *
 * 插队问题：N 个人依次入队，第 i 个人插到当时队伍的第 P_i 个位置（0-indexed），
 * 求最终队伍里每个人的 V_i。
 *
 * 做法：正向模拟插入的复杂度是 O(N^2)，改用「离线倒序 + 树状数组上二分」。
 * 最后一个插入的人位置不再被后来者影响，他在最终队伍中的位置就是第 P_N+1 个空位；
 * 倒着往前，每人都占据当前剩余空位中的第 P_i+1 个。树状数组维护「每个位置是否为空」
 * 的前缀和，用倍增在 O(log N) 内定位第 k 个空位。总复杂度 O(N log N)。 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;  // N ≤ 200000，位置按下标 1..N 使用

struct Op {
    int pos;  // P_i：插入到当时队伍的第 pos 个位置（0-indexed）
    ll val;   // V_i：这个人的数值
};

int n;              // 当前组的操作条数
Op op[MAXN];        // op[i]：第 i 条插入指令（按下标 0..n-1 读入，倒序处理）
ll ans[MAXN];       // ans[p]：最终队伍第 p 个位置（1-indexed）上的人的数值
int bit[MAXN];      // 树状数组，存「第 p 个位置是否为空」的前缀和；下标 ≤ 200000，用 int

// 单点加减：位置 i 的空位数变化 delta（0 表示已被占用）
void bit_add(int i, int delta) {
    for (; i <= n; i += i & -i) {
        bit[i] += delta;
    }
}

// 倍增求前缀和首次达到 k 的位置，即当前第 k 个空位的下标（1-indexed）
int bit_kth(int k) {
    int pos = 0;
    int sum = 0;
    int step = 1;
    while ((step << 1) <= n) {
        step <<= 1;
    }
    for (; step > 0; step >>= 1) {
        int next_pos = pos + step;
        if (next_pos <= n && sum + bit[next_pos] < k) {
            pos = next_pos;
            sum += bit[next_pos];
        }
    }
    return pos + 1;
}

void solve() {
    for (int i = 0; i < n; i++) {
        cin >> op[i].pos >> op[i].val;
    }

    // 初始时每个位置都空着：bit[i] = i & -i 是「前 i 个位置全为 1」的树状数组初值
    for (int i = 1; i <= n; i++) {
        bit[i] = i & -i;
    }

    // 倒序处理：第 i 个人必定落在当前剩余空位的第 op[i].pos + 1 个
    for (int i = n - 1; i >= 0; i--) {
        int p = bit_kth(op[i].pos + 1);
        ans[p] = op[i].val;
        bit_add(p, -1);  // 这个空位被占掉
    }

    // 输出最终队伍；每个数字后都带一个空格，行末也保留（与数据格式一致）
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        solve();
    }
    return 0;
}
