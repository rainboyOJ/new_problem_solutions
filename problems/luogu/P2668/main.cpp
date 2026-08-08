#include <bits/stdc++.h>
using namespace std;

const int RANK_CNT = 16;

int T, n;
int cnt[RANK_CNT];
int answer;
map<long long, int> memo;

// 把 3..A,2,小王,大王 映射到 1..15，方便顺子判断。
int rank_id(int a) {
    if (a == 0) {
        return 14;
    }
    if (a == 1) {
        return 12;
    }
    if (a == 2) {
        return 13;
    }
    return a - 2;
}

long long encode_state() {
    long long code = 0;
    for (int i = 1; i <= 15; i++) {
        code = code * 5 + cnt[i];
    }
    return code;
}

// 不再考虑顺子时，剩余牌型的最优解。
int solve_rest() {
    long long state = encode_state();
    map<long long, int>::iterator it = memo.find(state);
    if (it != memo.end()) {
        return it->second;
    }

    int single_cnt = 0;
    int pair_cnt = 0;
    int best = 0;

    for (int i = 1; i <= 15; i++) {
        if (cnt[i] == 1) {
            single_cnt++;
        } else if (cnt[i] == 2) {
            pair_cnt++;
        } else if (cnt[i] == 3) {
            best++;
        } else if (cnt[i] == 4) {
            best++;
        }
    }

    // 三张/炸弹尽量带牌，可以把剩下的单牌或对子吸收进去。
    for (int i = 1; i <= 15; i++) {
        if (cnt[i] == 3) {
            if (pair_cnt > 0) {
                pair_cnt--;
            } else if (single_cnt > 0) {
                single_cnt--;
            }
        } else if (cnt[i] == 4) {
            if (pair_cnt >= 2) {
                pair_cnt -= 2;
            } else if (pair_cnt >= 1 && single_cnt >= 1) {
                pair_cnt--;
                single_cnt--;
            } else if (single_cnt >= 2) {
                single_cnt -= 2;
            }
        }
    }

    best += pair_cnt + single_cnt;

    // 再尝试更精细地枚举三张/炸弹的出法，修正上面的贪心估值。
    for (int i = 1; i <= 15; i++) {
        if (cnt[i] >= 3) {
            cnt[i] -= 3;
            best = min(best, solve_rest() + 1);

            for (int j = 1; j <= 15; j++) {
                if (cnt[j] >= 1) {
                    cnt[j]--;
                    best = min(best, solve_rest() + 1);
                    cnt[j]++;
                }
            }

            for (int j = 1; j <= 15; j++) {
                if (cnt[j] >= 2) {
                    cnt[j] -= 2;
                    best = min(best, solve_rest() + 1);
                    cnt[j] += 2;
                }
            }

            cnt[i] += 3;
        }

        if (cnt[i] == 4) {
            cnt[i] -= 4;
            best = min(best, solve_rest() + 1);

            for (int a = 1; a <= 15; a++) {
                if (cnt[a] == 0) {
                    continue;
                }
                cnt[a]--;
                for (int b = a; b <= 15; b++) {
                    if (cnt[b] == 0) {
                        continue;
                    }
                    cnt[b]--;
                    best = min(best, solve_rest() + 1);
                    cnt[b]++;
                }
                cnt[a]++;
            }

            for (int a = 1; a <= 15; a++) {
                if (cnt[a] < 2) {
                    continue;
                }
                cnt[a] -= 2;
                for (int b = a; b <= 15; b++) {
                    if (cnt[b] < 2) {
                        continue;
                    }
                    cnt[b] -= 2;
                    best = min(best, solve_rest() + 1);
                    cnt[b] += 2;
                }
                cnt[a] += 2;
            }

            cnt[i] += 4;
        }
    }

    if (cnt[14] >= 1 && cnt[15] >= 1) {
        cnt[14]--;
        cnt[15]--;
        best = min(best, solve_rest() + 1);
        cnt[14]++;
        cnt[15]++;
    }

    memo[state] = best;
    return best;
}

// depth 表示已经打出了多少手顺子类牌型。
void dfs_straight(int depth) {
    if (depth >= answer) {
        return;
    }

    answer = min(answer, depth + solve_rest());

    // 单顺子：长度至少 5，只能用到 A，不能含 2 和大小王。
    for (int l = 1; l <= 12; l++) {
        if (cnt[l] == 0) {
            continue;
        }
        for (int r = l; r <= 12 && cnt[r] >= 1; r++) {
            if (r - l + 1 < 5) {
                continue;
            }
            for (int i = l; i <= r; i++) {
                cnt[i]--;
            }
            dfs_straight(depth + 1);
            for (int i = l; i <= r; i++) {
                cnt[i]++;
            }
        }
    }

    // 双顺子：长度至少 3。
    for (int l = 1; l <= 12; l++) {
        if (cnt[l] < 2) {
            continue;
        }
        for (int r = l; r <= 12 && cnt[r] >= 2; r++) {
            if (r - l + 1 < 3) {
                continue;
            }
            for (int i = l; i <= r; i++) {
                cnt[i] -= 2;
            }
            dfs_straight(depth + 1);
            for (int i = l; i <= r; i++) {
                cnt[i] += 2;
            }
        }
    }

    // 三顺子：长度至少 2。
    for (int l = 1; l <= 12; l++) {
        if (cnt[l] < 3) {
            continue;
        }
        for (int r = l; r <= 12 && cnt[r] >= 3; r++) {
            if (r - l + 1 < 2) {
                continue;
            }
            for (int i = l; i <= r; i++) {
                cnt[i] -= 3;
            }
            dfs_straight(depth + 1);
            for (int i = l; i <= r; i++) {
                cnt[i] += 3;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> n;
    while (T--) {
        memset(cnt, 0, sizeof(cnt));

        for (int i = 1; i <= n; i++) {
            int a, b;
            cin >> a >> b;
            cnt[rank_id(a)]++;
        }

        memo.clear();
        answer = n;
        dfs_straight(0);
        cout << answer << '\n';
    }

    return 0;
}
