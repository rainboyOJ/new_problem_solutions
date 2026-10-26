/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 14:34
 * update_at: 2026-10-26 14:34
 */
#include <bits/stdc++.h>
using namespace std;

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-26 13:28
 * update_at: 2026-10-26 14:25
 */

// brute.cpp：小数据暴力解，逐棵树枚举观看次数，仅用于理解和对拍。
const int MAXN = 10005;

int n, limit_time;
int tree_time[MAXN], beauty[MAXN], count_limit[MAXN];
int choose_count[MAXN]; // choose_count[i] 表示完整方案中第 i 棵树观看的次数
int answer;

void check_plan() {
    int total_time = 0;
    int total_beauty = 0;
    for (int i = 1; i <= n; i++) {
        total_time += choose_count[i] * tree_time[i];
        total_beauty += choose_count[i] * beauty[i];
    }
    if (total_time <= limit_time) {
        answer = max(answer, total_beauty);
    }
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        check_plan();
        return;
    }

    int max_count = limit_time / tree_time[dep];
    if (count_limit[dep] > 0) {
        max_count = min(max_count, count_limit[dep]);
    }

    // 这一层枚举第 dep 棵树观看 0 到 max_count 次。
    for (int take = 0; take <= max_count; take++) {
        choose_count[dep] = take;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int start_hour, start_minute, end_hour, end_minute;
    char colon;
    cin >> start_hour >> colon >> start_minute;
    cin >> end_hour >> colon >> end_minute;
    cin >> n;

    limit_time = (end_hour * 60 + end_minute) - (start_hour * 60 + start_minute);
    for (int i = 1; i <= n; i++) {
        cin >> tree_time[i] >> beauty[i] >> count_limit[i];
    }

    dfs_choose(1);
    cout << answer << '\n';
    return 0;
}
