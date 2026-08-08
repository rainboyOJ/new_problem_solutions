#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const long long INF = (1LL << 60);

int n, round_time;
int t[MAXN];

long long *dp;
unsigned short *cnt_prefix;
int *sum_prefix;
int *freq_cnt;
int *que;

long long line_value(int idx, int x) {
    return dp[idx] + sum_prefix[idx] - 1LL * cnt_prefix[idx] * x;
}

bool is_bad(int a, int b, int c) {
    long long k1 = -1LL * cnt_prefix[a];
    long long k2 = -1LL * cnt_prefix[b];
    long long k3 = -1LL * cnt_prefix[c];
    long long b1 = dp[a] + sum_prefix[a];
    long long b2 = dp[b] + sum_prefix[b];
    long long b3 = dp[c] + sum_prefix[c];

    return (__int128)(b2 - b1) * (k2 - k3) >= (__int128)(b3 - b2) * (k1 - k2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> round_time;
    for (int i = 1; i <= n; i++) {
        cin >> t[i];
    }

    sort(t + 1, t + n + 1);
    for (int i = 1; i <= n; i++) {
        t[i] += round_time;
    }

    int max_time = t[n] + n * round_time;

    dp = new long long[max_time + 1];
    cnt_prefix = new unsigned short[max_time + 1];
    sum_prefix = new int[max_time + 1];
    freq_cnt = new int[max_time + 1];
    que = new int[max_time + 1];

    for (int i = 0; i <= max_time; i++) {
        dp[i] = INF;
        cnt_prefix[i] = 0;
        sum_prefix[i] = 0;
        freq_cnt[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        freq_cnt[t[i]]++;
    }

    for (int x = 1; x <= max_time; x++) {
        cnt_prefix[x] = cnt_prefix[x - 1] + freq_cnt[x];
        sum_prefix[x] = sum_prefix[x - 1] + freq_cnt[x] * x;
    }

    dp[0] = 0;

    int head = 1, tail = 1;
    que[1] = 0;

    for (int x = 1; x <= max_time; x++) {
        int y = x - round_time;
        if (y >= 0 && dp[y] < INF / 2) {
            // 插入一条来自状态 y 的直线。
            while (head <= tail && cnt_prefix[que[tail]] == cnt_prefix[y]) {
                if (dp[que[tail]] + sum_prefix[que[tail]] <= dp[y] + sum_prefix[y]) {
                    y = -1;
                    break;
                }
                tail--;
            }
            if (y >= 0) {
                while (head < tail && is_bad(que[tail - 1], que[tail], y)) {
                    tail--;
                }
                que[++tail] = y;
            }
        }

        while (head < tail && line_value(que[head], x) >= line_value(que[head + 1], x)) {
            head++;
        }

        dp[x] = 1LL * x * cnt_prefix[x] - sum_prefix[x] + line_value(que[head], x);
    }

    long long ans = INF;
    for (int x = t[n]; x <= max_time; x++) {
        if (cnt_prefix[x] == n && dp[x] < ans) {
            ans = dp[x];
        }
    }

    cout << ans << '\n';

    delete[] dp;
    delete[] cnt_prefix;
    delete[] sum_prefix;
    delete[] freq_cnt;
    delete[] que;
    return 0;
}
