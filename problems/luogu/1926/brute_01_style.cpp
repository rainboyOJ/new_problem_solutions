// brute_01_style.cpp：选择序列风格暴力，分别枚举作业选不选、喜欢题做不做。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXM = 15;

int n, m, k, r;
int like_time[MAXN];
int homework_time[MAXM], homework_score[MAXM];
int answer;

void dfs_like(int pos, int used_time, int count_done) {
    if (used_time > r) {
        return;
    }
    if (pos == n + 1) {
        answer = max(answer, count_done);
        return;
    }

    // 选择 0：不做第 pos 道喜欢题。
    dfs_like(pos + 1, used_time, count_done);

    // 选择 1：做第 pos 道喜欢题。
    dfs_like(pos + 1, used_time + like_time[pos], count_done + 1);
}

void dfs_homework(int pos, int used_time, int score) {
    if (used_time > r) {
        return;
    }
    if (pos == m + 1) {
        if (score >= k) {
            dfs_like(1, used_time, 0);
        }
        return;
    }

    // 选择 0：不做第 pos 项作业。
    dfs_homework(pos + 1, used_time, score);

    // 选择 1：做第 pos 项作业。
    dfs_homework(pos + 1, used_time + homework_time[pos], score + homework_score[pos]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> r;
    for (int i = 1; i <= n; i++) {
        cin >> like_time[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> homework_time[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> homework_score[i];
    }

    answer = 0;
    dfs_homework(1, 0, 0);

    cout << answer << '\n';
    return 0;
}
