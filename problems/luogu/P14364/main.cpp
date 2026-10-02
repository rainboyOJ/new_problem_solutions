/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:59
 * update_at: 2026-10-01 22:48
 */
// main.cpp：按失败人数做 DP，用 pending 延后结算大耐心人群，
// 失败人数阈值增加时用组合数把具体人员归属结算出来。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 505;
const ll MOD = 998244353LL;

int n, m;
string s;

int cnt[MAXN]; // cnt[x]：耐心上限恰好为 x 的人数
int pre[MAXN]; // pre[x]：耐心上限 <= x 的人数前缀和

ll fac[MAXN];          // fac[t]：t 的阶乘（模 MOD）
ll comb[MAXN][MAXN];   // comb[i][j]：组合数 C(i, j)（模 MOD）
ll cur[MAXN][MAXN];    // cur[failed][pending]：当前天结束后的方案数
ll nxt[MAXN][MAXN];    // 下一天的滚动数组

// 模意义下加法：x = (x + y) % MOD，要求 y < MOD
void add_mod(ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

// 从 pending 个未结算位置里结算出 t 个耐心值恰为 value_c 的人：
// 选位置 C(k, t) * 选人 C(cnt[value_c], t) * 分配 t!
ll choose_pending(int value_c, int k, int t) {
    return comb[k][t] * comb[cnt[value_c]][t] % MOD * fac[t] % MOD;
}

// 预处理阶乘和组合数表
void init_comb() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = fac[i - 1] * i % MOD;
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

// 清零滚动数组 nxt（只清会用到的 0..n 范围）
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
                ll val = cur[failed][pending];
                if (val == 0) {
                    continue;
                }

                if (s[day] == '1') {
                    // 选一个 c > failed 的人，他会被录用；具体是谁延后统计。
                    if (n - pre[failed] - pending > 0) {
                        add_mod(nxt[failed][pending + 1], val);
                    }

                    // 选一个 c <= failed 的人，他会放弃，失败人数增加。
                    int available_small = pre[failed] - (day - pending);
                    if (available_small > 0) {
                        int max_t = min(cnt[failed + 1], pending);
                        for (int t = 0; t <= max_t; t++) {
                            ll ways = choose_pending(failed + 1, pending, t);
                            ways = ways * available_small % MOD;
                            add_mod(nxt[failed + 1][pending - t], val * ways % MOD);
                        }
                    }
                }
                else {
                    // 题目太难，必定失败；失败人数从 failed 变成 failed + 1。
                    int max_t = min(cnt[failed + 1], pending);
                    for (int t = 0; t <= max_t; t++) {
                        ll ways = choose_pending(failed + 1, pending, t);
                        int after_pending = pending - t;

                        // 当天这个人若 c > failed + 1，继续作为待结算人员。
                        if (n - pre[failed + 1] - after_pending > 0) {
                            add_mod(nxt[failed + 1][after_pending + 1], val * ways % MOD);
                        }

                        // 当天这个人若 c <= failed + 1，立即结算具体身份。
                        int available_small = pre[failed + 1] - (day - after_pending);
                        if (available_small > 0) {
                            add_mod(nxt[failed + 1][after_pending],
                                    val * ways % MOD * available_small % MOD);
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

    // 录用至少 m 人 <=> 失败人数 <= n - m；
    // 最终所有 c <= failed 的人已结算完，剩余 pending 个大耐心人可任意排列。
    ll ans = 0;
    for (int failed = 0; failed <= n - m; failed++) {
        int pending = n - pre[failed];
        if (pending >= 0 && pending <= n) {
            add_mod(ans, cur[failed][pending] * fac[pending] % MOD);
        }
    }

    cout << ans << '\n';
    return 0;
}
