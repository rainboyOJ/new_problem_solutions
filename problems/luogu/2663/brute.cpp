// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;               // 学生人数
int need_cnt;        // 必须选出的人数
int limit_score;     // 选出队伍的总分上限
int a[MAXN];         // 每个学生的分数
int choose_student[MAXN]; // choose_student[i] = 0/1，表示第 i 个学生不选/选
int best_answer;     // 当前找到的最优答案

int calc_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_student[i] == 1) cnt++;
    }
    return cnt;
}

int calc_score() {
    int sum_score = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_student[i] == 1) sum_score += a[i];
    }
    return sum_score;
}

bool check() {
    return calc_count() == need_cnt && calc_score() <= limit_score;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_score();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 个学生的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_student[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    need_cnt = n / 2;

    int total_score = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_score += a[i];
    }

    limit_score = total_score / 2;
    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
