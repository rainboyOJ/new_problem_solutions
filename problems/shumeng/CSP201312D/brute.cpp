/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
// brute.cpp：按位递归枚举四种数字，并缓存重复的后缀状态。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

int n;
long long memo[1002][3][3];

long long dfs(int pos, int first, int second) {
    if (pos > n) {
        return first == 2 && second == 2;
    }

    if (memo[pos][first][second] != -1) {
        return memo[pos][first][second];
    }

    long long ways = 0;
    // 追加 0：还没有出现 1 时才允许。
    if (first < 2) {
        ways += dfs(pos + 1, max(first, 1), second);
    }
    // 追加 1：必须已经出现过 0。
    if (first > 0) {
        ways += dfs(pos + 1, 2, second);
    }

    // 追加 2：还没有出现 3 时才允许。
    if (second < 2) {
        ways += dfs(pos + 1, first, max(second, 1));
    }
    // 追加 3：必须已经出现过 2。
    if (second > 0) {
        ways += dfs(pos + 1, first, 2);
    }

    memo[pos][first][second] = ways % MOD;
    return memo[pos][first][second];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        memset(memo, -1, sizeof(memo));

        // 首位只能是 2，因此从第二位开始枚举。
        cout << dfs(2, 0, 1) << '\n';
    }

    return 0;
}
