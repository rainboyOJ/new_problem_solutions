/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:58
 * update_at: 2026-11-13 09:58
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 40;
long long a[maxn];
long long m;
int n;

vector<long long> set_a; // 前半部分所有可能子集和模 m 的余数
vector<long long> set_b; // 后半部分所有可能子集和模 m 的余数

// DFS 枚举前半部分所有子集的余数
void dfs_a(int idx, int end_idx, long long cur_sum) {
    if (idx == end_idx) {
        set_a.push_back(cur_sum);
        return;
    }
    // 决策 1：不选当前数字
    dfs_a(idx + 1, end_idx, cur_sum);
    // 决策 2：选择当前数字
    dfs_a(idx + 1, end_idx, (cur_sum + a[idx]) % m);
}

// DFS 枚举后半部分所有子集的余数
void dfs_b(int idx, int end_idx, long long cur_sum) {
    if (idx == end_idx) {
        set_b.push_back(cur_sum);
        return;
    }
    // 决策 1：不选当前数字
    dfs_b(idx + 1, end_idx, cur_sum);
    // 决策 2：选择当前数字
    dfs_b(idx + 1, end_idx, (cur_sum + a[idx]) % m);
}

int main() {
    // 提升标准流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m;
    }

    // 1. 折半切分：前半段 n1 个数，后半段 n2 个数
    int mid = n / 2;
    dfs_a(0, mid, 0);
    dfs_b(mid, n, 0);

    // 2. 将后半部分排序并去重，构建单调有序数组供二分查找
    sort(set_b.begin(), set_b.end());
    set_b.erase(unique(set_b.begin(), set_b.end()), set_b.end());

    // 3. 遍历前半部分每个余数 u，在后半部分二分寻找最优配对 v
    long long ans = 0;
    for (long long u : set_a) {
        // 情况 1：u + v < m，即 v < m - u
        // 在 set_b 中二分寻找严格小于 m - u 的最大元素
        auto it = lower_bound(set_b.begin(), set_b.end(), m - u);
        if (it != set_b.begin()) {
            ans = max(ans, u + *prev(it));
        }

        // 情况 2：u + v >= m，此时 (u + v) % m = u + v - m
        // 因为 u 和 m 固定，v 越大越优，直接取 set_b 中的最大值
        ans = max(ans, (u + set_b.back()) % m);
    }

    cout << ans << "\n";
    return 0;
}
