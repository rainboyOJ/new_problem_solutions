/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

struct Player {
    int id;    // 报名号
    int score; // 分数
};

int n, m;
Player p[MAXN];

// 排序规则：分数降序，分数相同则报名号升序
bool cmp(const Player &a, const Player &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].score;
    }

    sort(p, p + n, cmp);

    int line_cnt = m * 3 / 2;          // 计划录取人数的 150%
    int line_score = p[line_cnt - 1].score; // 分数线

    // 统计所有达到分数线的选手
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (p[i].score >= line_score) cnt++;
    }

    cout << line_score << " " << cnt << "\n";
    for (int i = 0; i < cnt; i++) {
        cout << p[i].id << " " << p[i].score << "\n";
    }

    return 0;
}
