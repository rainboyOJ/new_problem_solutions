// brute_01_style.cpp：另一种小数据暴力写法，从左到右选择区间。
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
vector<int> prefix_xor; // prefix_xor[i] = a[1] ^ ... ^ a[i]
vector<int> memo;       // memo[pos] 表示从 pos 开始最多还能选几个区间

int dfs_solve(int pos) {
    if (pos > n) {
        return 0;
    }
    if (memo[pos] != -1) {
        return memo[pos];
    }

    // 选择 0：当前位置不作为新区间的开头。
    int best = dfs_solve(pos + 1);

    // 选择 1：枚举一个从 pos 开始、异或和为 k 的区间。
    for (int r = pos; r <= n; r++) {
        int value = prefix_xor[r] ^ prefix_xor[pos - 1];
        if (value == k) {
            best = max(best, 1 + dfs_solve(r + 1));
        }
    }

    memo[pos] = best;
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.assign(n + 1, 0);
    prefix_xor.assign(n + 1, 0);
    memo.assign(n + 2, -1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        prefix_xor[i] = prefix_xor[i - 1] ^ a[i];
    }

    cout << dfs_solve(1) << '\n';
    return 0;
}
