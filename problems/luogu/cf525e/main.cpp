/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02
 * update_at: 2026-08-02
 */

/* CF525E Anya and Cubes */
/* 三进制枚举是 3^25；折半搜索：左半枚举后按贴纸数分桶存 sum->方案数，
 * 右半枚举叶子时查左半所有允许贴纸数的桶，累加 S-right_sum 的出现次数。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25 + 5;

int n, k;          // n 个数，最多 k 张贴纸
long long S;       // 目标和
long long a[MAXN]; // 每个数
long long fact[19] = {1}; // fact[i] = i!，只到 18（19! > 1e16 > S 上限）

// left[st]：左半枚举结果中，用了 st 张贴纸时的 sum -> 方案数
vector<unordered_map<long long, long long>> left_map;

// 枚举左半 [idx, end)，当前和 sum、已用贴纸 st
void dfs_left(int idx, int end, long long sum, int st) {
    if (idx == end) {
        left_map[st][sum]++;
        return;
    }
    dfs_left(idx + 1, end, sum, st);             // 不选
    dfs_left(idx + 1, end, sum + a[idx], st);    // 选原值
    if (a[idx] <= 18 && st < k)                  // 选阶乘（贴一张贴纸）
        dfs_left(idx + 1, end, sum + fact[a[idx]], st + 1);
}

long long ans = 0;

// 枚举右半 [idx, end)
void dfs_right(int idx, int end, long long sum, int st) {
    if (idx == end) {
        // 左半还能用 st2 张：st + st2 <= k
        for (int st2 = 0; st2 + st <= k; st2++) {
            auto it = left_map[st2].find(S - sum);
            if (it != left_map[st2].end())
                ans += it->second;
        }
        return;
    }
    dfs_right(idx + 1, end, sum, st);
    dfs_right(idx + 1, end, sum + a[idx], st);
    if (a[idx] <= 18 && st < k)
        dfs_right(idx + 1, end, sum + fact[a[idx]], st + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 18; i++)
        fact[i] = fact[i - 1] * i;

    cin >> n >> k >> S;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    left_map.resize(k + 1);
    int mid = n / 2;
    dfs_left(0, mid, 0, 0);
    dfs_right(mid, n, 0, 0);

    cout << ans << '\n';
    return 0;
}
