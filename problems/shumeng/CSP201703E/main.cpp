/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:47
 */
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);

long long next_value(long long &x, long long a, long long b, long long q) {
    x = (a * x + b) % q;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long a, b, q, x;
    cin >> n >> m >> a >> b >> q >> x;

    long long vertical_size = 1LL * (m + 1) * n;
    long long horizontal_size = 1LL * m * n;
    int *vertical = new int[vertical_size];
    int *horizontal = new int[horizontal_size];

    // 输入生成顺序是按行，DP 使用时按列，因此转置存储两类管道容量。
    for (int row = 1; row <= n - 1; row++) {
        for (int column = 1; column <= m; column++) {
            vertical[1LL * column * n + row] = (int)next_value(x, a, b, q);
        }
    }
    for (int row = 2; row <= n - 1; row++) {
        for (int column = 1; column <= m - 1; column++) {
            horizontal[1LL * column * n + row] = (int)next_value(x, a, b, q);
        }
    }

    vector<long long> dp(n), next_dp(n), prefix(n);
    for (int height = 1; height <= n - 1; height++) {
        dp[height] = vertical[n + height];
    }

    for (int column = 2; column <= m; column++) {
        prefix[1] = 0;
        for (int height = 2; height <= n - 1; height++) {
            prefix[height] = prefix[height - 1]
                    + horizontal[1LL * (column - 1) * n + height];
        }

        long long best = INF;
        for (int height = 1; height <= n - 1; height++) {
            best = min(best, dp[height] - prefix[height]);
            next_dp[height] = best + prefix[height];
        }
        best = INF;
        for (int height = n - 1; height >= 1; height--) {
            best = min(best, dp[height] + prefix[height]);
            next_dp[height] = min(next_dp[height], best - prefix[height]);
            next_dp[height] += vertical[1LL * column * n + height];
        }
        dp.swap(next_dp);
    }

    long long answer = INF;
    for (int height = 1; height <= n - 1; height++) {
        answer = min(answer, dp[height]);
    }
    cout << answer << '\n';

    delete[] vertical;
    delete[] horizontal;
    return 0;
}
