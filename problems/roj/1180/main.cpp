/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:34
 * update_at: 2026-10-05 04:34
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 5005; // n <= 5000，多开几个下标防止越界

// 一名选手的排序所需信息
struct Player {
    ll id;    // 报名号
    ll score; // 笔试成绩
};

ll n, m;
Player p[MAXN]; // p[i] 表示第 i 名选手

// 排序规则：成绩从高到低，成绩相同报名号小的在前
bool cmp_player(const Player &a, const Player &b) {
    if (a.score != b.score) return a.score > b.score;
    return a.id < b.id;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        cin >> p[i].id >> p[i].score;
    }

    sort(p + 1, p + n + 1, cmp_player);

    // 分数线 = 排名 floor(m*150/100) 的选手成绩
    // 个别真实数据里 r 可能超过 n，此时按分数线 0 处理，所有人入面
    ll r = m * 150 / 100;
    ll line = 0;
    if (r <= n) line = p[r].score;

    // 实际人数按分数统计：与分数线同分的选手即使排名在 r 之后也要入面
    ll cnt = 0;
    for (ll i = 1; i <= n; i++) {
        if (p[i].score >= line) cnt++;
    }

    // 排好序后入面者恰好构成前缀，直接输出前 cnt 名
    cout << line << " " << cnt << "\n";
    for (ll i = 1; i <= cnt; i++) {
        cout << p[i].id << " " << p[i].score << "\n";
    }

    return 0;
}
