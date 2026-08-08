#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MOD = 998244353;

int n, m;
string s;
int cnt[MAXN], pre[MAXN];
int fac[MAXN], comb[MAXN][MAXN];
int cur[MAXN][MAXN], nxt[MAXN][MAXN];

void add_mod(int &x, long long y) {
    x = (x + y) % MOD;
}

long long choose_pending(int value_c, int k, int t) {
    return 1LL * comb[k][t] * comb[cnt[value_c]][t] % MOD * fac[t] % MOD;
}

void init_comb() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = 1LL * fac[i - 1] * i % MOD;
    }

    for (int i = 0; i < MAXN; i++) {
        comb[i][0] = comb[i][i] = 1;
    }
    for (int i = 1; i < MAXN; i++) {
        for (int j = 1; j < i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= MOD) {
                comb[i][j] -= MOD;
            }
        }
    }
}

void clear_next() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            nxt[i][j] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_comb();

    cin >> n >> m;
    cin >> s;

    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        cnt[c]++;
    }

    pre[0] = cnt[0];
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + cnt[i];
    }

    cur[0][0] = 1;

    for (int day = 0; day < n; day++) {
        clear_next();

        for (int failed = 0; failed <= day; failed++) {
            for (int pending = 0; pending <= day; pending++) {
                int val = cur[failed][pending];
                if (val == 0) {
                    continue;
                }

                if (s[day] == '1') {
                    // 选一个 c > failed 的人，他会被录用；具体是谁先延后统计。
                    if (n - pre[failed] - pending > 0) {
                        add_mod(nxt[failed][pending + 1], val);
                    }

                    // 选一个 c <= failed 的人，他会放弃，失败人数增加。
                    int available_small = pre[failed] - (day - pending);
                    if (available_small > 0) {
                        int max_t = min(cnt[failed + 1], pending);
                        for (int t = 0; t <= max_t; t++) {
                            long long ways = choose_pending(failed + 1, pending, t);
                            ways = ways * available_small % MOD;
                            add_mod(nxt[failed + 1][pending - t], 1LL * val * ways % MOD);
                        }
                    }
                } else {
                    // 题目太难，必定失败；失败人数从 failed 变成 failed + 1。
                    int max_t = min(cnt[failed + 1], pending);
                    for (int t = 0; t <= max_t; t++) {
                        long long ways = choose_pending(failed + 1, pending, t);
                        int after_pending = pending - t;

                        // 当天这个人若 c > failed + 1，继续作为待结算人员。
                        if (n - pre[failed + 1] - after_pending > 0) {
                            add_mod(nxt[failed + 1][after_pending + 1],
                                    1LL * val * ways % MOD);
                        }

                        // 当天这个人若 c <= failed + 1，立即结算具体身份。
                        int available_small = pre[failed + 1] - (day - after_pending);
                        if (available_small > 0) {
                            add_mod(nxt[failed + 1][after_pending],
                                    1LL * val * ways % MOD * available_small % MOD);
                        }
                    }
                }
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                cur[i][j] = nxt[i][j];
            }
        }
    }

    int ans = 0;
    for (int failed = 0; failed <= n - m; failed++) {
        int pending = n - pre[failed];
        if (pending >= 0 && pending <= n) {
            add_mod(ans, 1LL * cur[failed][pending] * fac[pending] % MOD);
        }
    }

    cout << ans << '\n';
    return 0;
}
