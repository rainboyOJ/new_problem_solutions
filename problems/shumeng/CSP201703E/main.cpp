/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);

// 递推生成下一个伪随机数 X_{i+1} = (A*X_i + B) mod Q
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

    // 容量按行生成、DP 按列使用，因此转置存储。
    // vertical[column*n + row]：第 column 列、row 与 row+1 行之间的竖管容量。
    // horizontal[column*n + row]：第 column 与 column+1 列之间、第 row 行的横管容量。
    long long vertical_size = 1LL * (m + 1) * n;
    long long horizontal_size = 1LL * m * n;
    int *vertical = new int[vertical_size];
    int *horizontal = new int[horizontal_size];

    // 竖管：第 1..n-1 行、每列 m 条，对应数列的前 (n-1)m 项
    for (int row = 1; row <= n - 1; row++) {
        for (int column = 1; column <= m; column++) {
            vertical[1LL * column * n + row] = (int)next_value(x, a, b, q);
        }
    }
    // 横管：第 2..n-1 行、每行 m-1 条，对应数列的接下来 (n-2)(m-1) 项
    for (int row = 2; row <= n - 1; row++) {
        for (int column = 1; column <= m - 1; column++) {
            horizontal[1LL * column * n + row] = (int)next_value(x, a, b, q);
        }
    }

    // dp[h]：当前列在第 h 行与 h+1 行之间切断时的最小割代价。
    // 第一列没有横向代价，初值就是本列竖管容量。
    vector<long long> dp(n), next_dp(n), prefix(n);
    for (int height = 1; height <= n - 1; height++) {
        dp[height] = vertical[n + height];
    }

    for (int column = 2; column <= m; column++) {
        // prefix[h]：第 column-1 与 column 列之间，从第 2 行累加到第 h 行的横管容量
        prefix[1] = 0;
        for (int height = 2; height <= n - 1; height++) {
            prefix[height] = prefix[height - 1]
                    + horizontal[1LL * (column - 1) * n + height];
        }

        // dp[col][b] = V[col][b] + min_a{ dp[col-1][a] + |P[a] - P[b]| }。
        // 绝对值按 a<=b / a>=b 分成两半，各用一次前缀/后缀最小值完成转移。
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

    // 最后一列取所有高度的最小值
    long long answer = INF;
    for (int height = 1; height <= n - 1; height++) {
        answer = min(answer, dp[height]);
    }
    cout << answer << '\n';

    delete[] vertical;
    delete[] horizontal;
    return 0;
}