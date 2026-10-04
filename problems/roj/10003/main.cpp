/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:50
 * update_at: 2026-10-04 21:50
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

ll n;
int a[MAXN]; // 输入数组，a_i <= 100，用 int 控制内存
ll diff[MAXN + 3]; // diff 按窗口长度做差分，前缀和后 diff[L] 就是第 L 窗口值

// 单调栈元素：value 是极值，index 是它出现的下标。
struct StackNode {
    ll value;
    ll index;
};

StackNode max_stack[MAXN]; // 从右往左看的 max 记录值，值严格递减
StackNode min_stack[MAXN]; // 从右往左看的 min 记录值，值严格递增

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
}

// 固定右端点 i，让左端点从 i 往 1 左移，两栈按下标从大到小归并出极值不变的段，
// 每段对应一段连续的窗口长度，用差分 O(1) 入账。
void solve() {
    ll max_top = 0; // max_stack 中元素个数，栈顶下标是 max_top
    ll min_top = 0;

    for (ll i = 1; i <= n; i++) {
        ll x = a[i];

        while (max_top > 0 && max_stack[max_top].value <= x) {
            max_top--;
        }
        while (min_top > 0 && min_stack[min_top].value >= x) {
            min_top--;
        }
        max_top++;
        max_stack[max_top].value = x;
        max_stack[max_top].index = i;
        min_top++;
        min_stack[min_top].value = x;
        min_stack[min_top].index = i;

        ll cur_max = x; // 只含左端点 i 时的极值
        ll cur_min = x;
        ll left = i; // 当前已入账的最左左端点
        ll p_max = max_top - 1; // 栈顶的下一层即下一个极值变化点
        ll p_min = min_top - 1;

        while (p_max >= 1 || p_min >= 1) {
            // 两栈都有变化点时先走下标更大的那个，因为更靠近 i 的变化先发生。
            // 同一下标同时是 max/min 变化点时会退化成空区间，加减抵消，无需特判。
            bool take_max = (p_max >= 1) && (p_min < 1 || max_stack[p_max].index >= min_stack[p_min].index);
            ll value;
            ll nxt;
            if (take_max) {
                value = max_stack[p_max].value;
                nxt = max_stack[p_max].index;
                p_max--;
            } else {
                value = min_stack[p_min].value;
                nxt = min_stack[p_min].index;
                p_min--;
            }

            ll prod = cur_max * cur_min;
            diff[i - left + 1] += prod; // 左端点 left 对应窗口长度 i-left+1
            diff[i - nxt + 1] -= prod;  // 左端点越过 nxt 后这对极值失效
            left = nxt;
            if (take_max) {
                cur_max = value;
            } else {
                cur_min = value;
            }
        }

        // 剩下的左端点 [1, left] 极值都不再变化，长度上界是 i。
        ll prod = cur_max * cur_min;
        diff[i - left + 1] += prod;
        diff[i + 1] -= prod;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    ll total = 0;
    for (ll length = 1; length <= n; length++) {
        total += diff[length];
        if (length > 1) {
            cout << ' ';
        }
        cout << total;
    }
    cout << '\n';

    return 0;
}
