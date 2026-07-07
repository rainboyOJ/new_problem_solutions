// brute_01_style.cpp：选择序列风格暴力，分别枚举作业选不选、喜欢题做不做。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;
const int MAXM = 15;

int n, m, k, r;
int like_time[MAXN];
int homework_time[MAXM], homework_score[MAXM];
int choose_homework[MAXM]; // choose_homework[i] = 0/1，表示第 i 项作业不做/做
int choose_like[MAXN];     // choose_like[i] = 0/1，表示第 i 道喜欢题不做/做
int answer;
int homework_used_time;

int calc_homework_time() {
    int total = 0;
    for (int i = 1; i <= m; i++) {
        if (choose_homework[i] == 1) total += homework_time[i];
    }
    return total;
}

int calc_homework_score() {
    int total = 0;
    for (int i = 1; i <= m; i++) {
        if (choose_homework[i] == 1) total += homework_score[i];
    }
    return total;
}

int calc_like_time() {
    int total = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_like[i] == 1) total += like_time[i];
    }
    return total;
}

int calc_like_count() {
    int total = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_like[i] == 1) total++;
    }
    return total;
}

void dfs_like(int dep) {
    if (dep == n + 1) {
        if (homework_used_time + calc_like_time() <= r) {
            int value = calc_like_count();
            if (answer < value) answer = value;
        }
        return;
    }

    for (int i = 0; i <= 1; i++) {
        choose_like[dep] = i;
        dfs_like(dep + 1);
    }
}

void dfs_homework(int dep) {
    if (dep == m + 1) {
        homework_used_time = calc_homework_time();
        if (homework_used_time <= r && calc_homework_score() >= k) {
            dfs_like(1);
        }
        return;
    }

    for (int i = 0; i <= 1; i++) {
        choose_homework[dep] = i;
        dfs_homework(dep + 1);
    }
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
    dfs_homework(1);

    cout << answer << '\n';
    return 0;
}
