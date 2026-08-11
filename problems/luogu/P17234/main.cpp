/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 20:32
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;

int n;
int a[MAXV];
vector<int> pos[MAXV]; // pos[v] 保存值 v 在数组中的所有位置（下标从 1 开始）

// 统计 mex(l,r) = cmin(l,r) = 0 的区间数量。
// 条件等价于：区间内不含任何 0（mex=0），
// 且补区间里至少有一个 0（cmin=0），即区间没覆盖全部 0。
long long count_zero_mex() {
    long long ans = 0;
    int last = 0; // 上一个 0 的位置，初始相当于位置 0 处有一个虚拟 0
    for (int i = 0; i < (int)pos[0].size(); i++) {
        int len = pos[0][i] - last - 1; // 两个相邻 0 之间不含 0 的连续段长度
        ans += 1LL * len * (len + 1) / 2; // 该段内任取一个子区间都不含 0
        last = pos[0][i];
    }
    int len = n - last; // 最后一个 0 之后的连续段
    ans += 1LL * len * (len + 1) / 2;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i <= n + 1; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= n) pos[a[i]].push_back(i); // 值 > n 不可能成为 mex=cmin 的答案，忽略
    }

    long long ans = 0;
    if (pos[0].empty()) {
        // 数组里没有 0：任意区间的 mex 恒为 0，
        // 而补区间最小值至少为 1（或 +inf），不可能相等。
        cout << 0 << '\n';
        return 0;
    }

    ans += count_zero_mex();

    // 处理 x >= 1 的情况：mex(l,r) = cmin(l,r) = x 等价于
    // 1) 区间 [l,r] 覆盖所有值 < x 的位置（保证 mex >= x 且补区间不含 < x 的值）；
    // 2) 区间 [l,r] 不覆盖任何值 = x 的位置（保证 mex <= x 且补区间含 x，cmin = x）。
    int left_bound = n + 1;  // [left_bound, right_bound] 是所有值 < x 的位置的最小覆盖段
    int right_bound = 0;
    for (int x = 1; x <= n; x++) {
        // 先把值 x-1 的所有位置并入覆盖段
        for (int i = 0; i < (int)pos[x - 1].size(); i++) {
            int p = pos[x - 1][i];
            if (p < left_bound) left_bound = p;
            if (p > right_bound) right_bound = p;
        }

        if (pos[x].empty()) break; // 缺少值 x，mex 不可能再等于更大的值

        // 若覆盖段内已经存在 x，任何覆盖所有 < x 位置的区间必然也覆盖这个 x，
        // 条件 2 无法满足，当前 x 没有贡献。
        vector<int>::iterator it = lower_bound(pos[x].begin(), pos[x].end(), left_bound);
        if (it != pos[x].end() && *it <= right_bound) continue;

        // prev_x：覆盖段左侧最近的 x；next_x：覆盖段右侧最近的 x。
        // 左端点 l 可在 (prev_x, left_bound] 中任选，右端点 r 可在 [right_bound, next_x) 中任选。
        int prev_x = 0;      // 左侧哨兵，表示位置 0 处虚拟一个 x
        int next_x = n + 1;  // 右侧哨兵，表示位置 n+1 处虚拟一个 x
        if (it != pos[x].end()) next_x = *it;
        if (it != pos[x].begin()) {
            --it;
            prev_x = *it;
        }

        // 左右端点选择互不影响，贡献为可选数量的乘积。
        ans += 1LL * (left_bound - prev_x) * (next_x - right_bound);
    }

    cout << ans << '\n';
    return 0;
}
