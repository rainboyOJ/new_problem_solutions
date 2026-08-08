#include <bits/stdc++.h>
using namespace std;

const int RANK_CNT = 16;

int T, n;
int cnt[RANK_CNT];
int answer;

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

bool empty_hand() {
    for (int i = 1; i <= 15; i++) {
        if (cnt[i] != 0) {
            return false;
        }
    }
    return true;
}

void dfs(int step) {
    if (step >= answer) {
        return;
    }
    if (empty_hand()) {
        answer = step;
        return;
    }

    for (int i = 1; i <= 15; i++) {
        if (cnt[i] == 0) {
            continue;
        }

        cnt[i]--;
        dfs(step + 1);
        cnt[i]++;

        if (cnt[i] >= 2) {
            cnt[i] -= 2;
            dfs(step + 1);
            cnt[i] += 2;
        }

        if (cnt[i] >= 3) {
            cnt[i] -= 3;
            dfs(step + 1);

            for (int j = 1; j <= 15; j++) {
                if (cnt[j] >= 1) {
                    cnt[j]--;
                    dfs(step + 1);
                    cnt[j]++;
                }
            }

            for (int j = 1; j <= 15; j++) {
                if (cnt[j] >= 2) {
                    cnt[j] -= 2;
                    dfs(step + 1);
                    cnt[j] += 2;
                }
            }

            cnt[i] += 3;
        }

        if (cnt[i] >= 4) {
            cnt[i] -= 4;
            dfs(step + 1);

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
                    dfs(step + 1);
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
                    dfs(step + 1);
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
        dfs(step + 1);
        cnt[14]++;
        cnt[15]++;
    }

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
            dfs(step + 1);
            for (int i = l; i <= r; i++) {
                cnt[i]++;
            }
        }
    }

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
            dfs(step + 1);
            for (int i = l; i <= r; i++) {
                cnt[i] += 2;
            }
        }
    }

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
            dfs(step + 1);
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
        answer = n;
        dfs(0);
        cout << answer << '\n';
    }

    return 0;
}
