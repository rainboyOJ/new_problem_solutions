#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const long long INF = (1LL << 62);

int n, L;
int d[MAXN];
int t[MAXN];
long long pre_w[MAXN];
long long pre_dw[MAXN];
long long dp_prev[MAXN], dp_cur[MAXN];
int que[MAXN];

// 把区间 [l..r] 的家庭都安排到 d[r] 这个会场，总代价是多少。
long long seg_cost(int l, int r) {
    if (l > r) {
        return 0;
    }
    long long sum_w = pre_w[r] - pre_w[l - 1];
    long long sum_dw = pre_dw[r] - pre_dw[l - 1];
    return 1LL * d[r] * sum_w - sum_dw;
}

// 把区间 [l..n] 的家庭都安排到终点 L，总代价是多少。
long long last_cost(int l) {
    if (l > n) {
        return 0;
    }
    long long sum_w = pre_w[n] - pre_w[l - 1];
    long long sum_dw = pre_dw[n] - pre_dw[l - 1];
    return 1LL * L * sum_w - sum_dw;
}

long long line_value(int j, int x) {
    return dp_prev[j] + pre_dw[j] - 1LL * x * pre_w[j];
}

bool is_bad(int a, int b, int c) {
    long long m1 = -pre_w[a];
    long long m2 = -pre_w[b];
    long long m3 = -pre_w[c];
    long long b1 = dp_prev[a] + pre_dw[a];
    long long b2 = dp_prev[b] + pre_dw[b];
    long long b3 = dp_prev[c] + pre_dw[c];

    return (__int128)(b2 - b1) * (m2 - m3) >= (__int128)(b3 - b2) * (m1 - m2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> d[i] >> t[i];
        pre_w[i] = pre_w[i - 1] + t[i];
        pre_dw[i] = pre_dw[i - 1] + 1LL * d[i] * t[i];
    }

    for (int i = 0; i <= n; i++) {
        dp_prev[i] = INF;
    }
    dp_prev[0] = 0;

    long long ans = last_cost(1);

    // 最多再额外放 3 个中间会场。
    for (int k = 1; k <= 3; k++) {
        for (int i = 0; i <= n; i++) {
            dp_cur[i] = INF;
        }

        int head = 1, tail = 0;
        if (dp_prev[0] < INF / 2) {
            que[++tail] = 0;
        }

        for (int i = 1; i <= n; i++) {
            // 当前层转移到 i 时，只能从 j < i 转过来，
            // 因此先查询，再把 j=i 加入队列供后面使用。
            while (head < tail && line_value(que[head], d[i]) >= line_value(que[head + 1], d[i])) {
                head++;
            }

            if (head <= tail) {
                dp_cur[i] = 1LL * d[i] * pre_w[i] - pre_dw[i] + line_value(que[head], d[i]);
            }

            if (dp_prev[i] < INF / 2) {
                while (head <= tail && pre_w[que[tail]] == pre_w[i]) {
                    if (dp_prev[que[tail]] + pre_dw[que[tail]] <= dp_prev[i] + pre_dw[i]) {
                        goto skip_insert;
                    }
                    tail--;
                }
                while (head < tail && is_bad(que[tail - 1], que[tail], i)) {
                    tail--;
                }
                que[++tail] = i;
            }
skip_insert:
            ;
        }

        for (int i = 1; i <= n; i++) {
            if (dp_cur[i] < INF / 2) {
                ans = min(ans, dp_cur[i] + last_cost(i + 1));
            }
        }

        for (int i = 0; i <= n; i++) {
            dp_prev[i] = dp_cur[i];
        }
    }

    cout << ans << '\n';
    return 0;
}
