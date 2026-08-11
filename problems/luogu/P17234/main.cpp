/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 22:22
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 200005;

int n;
int a[MAXV];
vector<int> pos[MAXV]; // pos[v] 保存值 v 在数组中的所有位置（下标从 1 开始）

void read_input() {
    cin >> n;
    for (int i = 0; i <= n + 1; i++) pos[i].clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= n) pos[a[i]].push_back(i); // 值 > n 不可能成为 mex=cmin 的答案，忽略
    }
}

// 统计 mex(l,r) = cmin(l,r) = 0 的区间数量。
// 条件等价于：区间内不含任何 0（mex=0），
// 且补区间里至少有一个 0（cmin=0），即区间没覆盖全部 0。
long long count_no_zero() {
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

// 把值 v 的所有位置并入最小覆盖段 [L,R]。
// 随着 x 增大，覆盖段只增不删，因此每个位置只会被加入一次。
void merge_into_cover(int v, int &L, int &R) {
    for (int i = 0; i < (int)pos[v].size(); i++) {
        int p = pos[v][i];
        if (p < L) L = p;
        if (p > R) R = p;
    }
}

// 找 [L,R] 左侧最近的 x 与右侧最近的 x（不含则用哨兵位置 0 / n+1）。
// 若覆盖段 [L,R] 内已经存在 x，则任何合法区间都无法避开它，返回 false。
bool get_nearest_x(int x, int L, int R, int &prev_x, int &next_x) {
    vector<int>::iterator it = lower_bound(pos[x].begin(), pos[x].end(), L);
    prev_x = 0;      // 左侧哨兵，表示位置 0 处虚拟一个 x
    next_x = n + 1;  // 右侧哨兵，表示位置 n+1 处虚拟一个 x
    if (it != pos[x].end()) {
        next_x = *it;
        if (*it <= R) return false;
    }
    if (it != pos[x].begin()) {
        --it;
        prev_x = *it;
    }
    return true;
}

// 对每个 x >= 1：mex(l,r) = cmin(l,r) = x 等价于
// 1) 区间 [l,r] 覆盖所有值 < x 的位置（保证 mex >= x 且补区间不含 < x 的值）；
// 2) 区间 [l,r] 不覆盖任何值 = x 的位置（保证 mex <= x 且补区间含 x，cmin = x）。
long long solve() {
    long long ans = 0;

    if (pos[0].empty()) {
        // 数组里没有 0：任意区间的 mex 恒为 0，
        // 而补区间最小值至少为 1（或 +inf），不可能相等。
        return 0;
    }
    ans += count_no_zero();

    int L = n + 1; // [L,R] 是所有值 < x 的位置的最小覆盖段
    int R = 0;
    for (int x = 1; x <= n; x++) {
        merge_into_cover(x - 1, L, R); // 覆盖段增加值 x-1 的所有位置

        if (pos[x].empty()) break; // 缺少值 x，mex 不可能再等于更大的值

        int prev_x, next_x;
        if (!get_nearest_x(x, L, R, prev_x, next_x)) continue;

        // 左端点 l 可在 (prev_x, L] 中任选，右端点 r 可在 [R, next_x) 中任选，
        // 左右端点选择互不影响，贡献为可选数量的乘积。
        ans += 1LL * (L - prev_x) * (next_x - R);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << solve() << '\n';

    return 0;
}
