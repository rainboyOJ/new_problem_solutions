/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:36
 * update_at: 2026-11-09 22:15
 */
// main.cpp：双指针解法（以左端点为主视角，维护闭区间 [l, r]）。
// 证明与思路：
// 外层枚举左端点 l，指针 r 表示当前窗口内最后一个合法元素（初始为 0 表示窗口为空）。
// 只要下一个位置 r + 1 能够加入窗口且窗口内 0 的个数 <= k，就让 r 扩展一步。
// 当 r 无法再前进时，闭区间 [l, r] 即为以 l 为起点的极大合法窗口，长度为 r - l + 1。
// 当 l 步进到 l + 1 时，新的待查区间 [l+1, r] 包含于原合法区间 [l, r]，内部 0 的个数只减不增，必然合法！
// 因此以 l+1 为起点的最远右端点必有 R(l+1) >= R(l)，r 绝不需要回退。
// 两个指针均单调右移，复杂度 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 300005;

ll n;              // 元素个数
ll k;              // 最多可以改的 0 的个数
int a[maxn];       // 原数组，元素只有 0/1，用 int 足够
int b[maxn];       // 答案数组（原数组修改后的结果）

void read_input() {
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
}

void solve() {
    ll r = 0;         // 右指针：当前已经纳入闭区间 [l, r] 的最右端下标；初始为 0 表示窗口为空
    ll zero_cnt = 0;  // 当前闭区间 [l, r] 内 0 的个数
    ll best_len = 0;  // 记录最大合法长度
    ll best_left = 1; // 记录最优区间的左端点

    // 外层枚举左端点 l
    for (ll l = 1; l <= n; l++) {
        // 尝试试探下一个位置 r + 1：只要还在数组内且加入后 0 的个数不超过 k，就扩展 r
        while (r + 1 <= n && zero_cnt + (a[r + 1] == 0 ? 1 : 0) <= k) {
            r++;
            if (a[r] == 0) {
                zero_cnt++;
            }
        }

        // 此时闭区间 [l, r] 是以 l 为起点的极大合法区间
        if (r >= l && r - l + 1 > best_len) {
            best_len = r - l + 1;
            best_left = l;
        }

        // l 即将步进到 l + 1：若当前区间非空且包含了 a[l]，将其移出窗口
        if (r >= l) {
            if (a[l] == 0) {
                zero_cnt--;
            }
        } else {
            r = l; // 极端情况（如 k=0 且 a[l]=0，单个位置都不合法），r 随 l 推移保证下次从 l+1 试探
        }
    }

    // 将最优窗口内的 0 全部修改为 1
    for (ll i = best_left; i <= best_left + best_len - 1; i++) {
        b[i] = 1;
    }

    cout << best_len << "\n";
    for (ll i = 1; i <= n; i++) {
        cout << b[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
