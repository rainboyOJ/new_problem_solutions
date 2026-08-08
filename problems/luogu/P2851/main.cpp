#include <bits/stdc++.h>
using namespace std;

const int MAXV = 120;
const int INF = 1e9;

int n, target_sum;
int value_input[105], count_input[105];
int cnt[MAXV + 5];
bool has_value[MAXV + 5];

int limit_sum, max_value;
vector<int> pay_dp, old_dp, change_dp;
vector<int> que;

int score_of(const vector<int> &dp, int pos, int k) {
    if (dp[pos] >= INF) {
        return INF;
    }
    return dp[pos] - k;
}

void build_pay_dp() {
    pay_dp.assign(limit_sum + 1, INF);
    old_dp.assign(limit_sum + 1, INF);
    pay_dp[0] = 0;

    for (int v = 1; v <= MAXV; v++) {
        if (cnt[v] == 0) {
            continue;
        }

        old_dp = pay_dp;
        for (int r = 0; r < v; r++) {
            int head = 1, tail = 0;

            for (int k = 0; k * v + r <= limit_sum; k++) {
                int pos = k * v + r;

                while (head <= tail && que[head] < k - cnt[v]) {
                    head++;
                }

                int cur_score = score_of(old_dp, pos, k);
                while (head <= tail) {
                    int last_k = que[tail];
                    int last_pos = last_k * v + r;
                    int last_score = score_of(old_dp, last_pos, last_k);
                    if (last_score <= cur_score) {
                        break;
                    }
                    tail--;
                }

                que[++tail] = k;

                int best_k = que[head];
                int best_pos = best_k * v + r;
                if (old_dp[best_pos] >= INF) {
                    pay_dp[pos] = INF;
                }
                else {
                    pay_dp[pos] = old_dp[best_pos] + (k - best_k);
                }
            }
        }
    }
}

void build_change_dp() {
    int max_extra = limit_sum - target_sum;
    change_dp.assign(max_extra + 1, INF);
    change_dp[0] = 0;

    for (int v = 1; v <= MAXV; v++) {
        if (!has_value[v]) {
            continue;
        }

        for (int s = v; s <= max_extra; s++) {
            if (change_dp[s - v] + 1 < change_dp[s]) {
                change_dp[s] = change_dp[s - v] + 1;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target_sum;
    for (int i = 1; i <= n; i++) {
        cin >> value_input[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> count_input[i];
    }

    for (int i = 1; i <= MAXV; i++) {
        cnt[i] = 0;
        has_value[i] = false;
    }

    max_value = 0;
    for (int i = 1; i <= n; i++) {
        int v = value_input[i];
        cnt[v] += count_input[i];
        has_value[v] = true;
        if (v > max_value) {
            max_value = v;
        }
    }

    // 经典上界：最优方案里，多付的钱不需要超过 max_value^2。
    limit_sum = target_sum + max_value * max_value;
    que.assign(limit_sum + 5, 0);

    build_pay_dp();
    build_change_dp();

    int answer = INF;
    for (int pay = target_sum; pay <= limit_sum; pay++) {
        int extra = pay - target_sum;
        if (pay_dp[pay] >= INF || change_dp[extra] >= INF) {
            continue;
        }
        answer = min(answer, pay_dp[pay] + change_dp[extra]);
    }

    if (answer >= INF) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}
