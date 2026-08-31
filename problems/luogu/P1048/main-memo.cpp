/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-31 10:46
 * update_at: 2026-08-31 10:48
 */
// main-memo.cpp：记忆化搜索解法。f[n][time] 表示只考虑前 n 株草药、时间上限为 time 时的最大总价值。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 105;   // 草药数量上限
const int MAXT = 1005;  // 总时间上限

int total_time;         // 总可用时间
int herb_count;         // 草药数量
int need_time[MAXM];    // 每株草药需要的时间
int herb_value[MAXM];   // 每株草药的价值

// memo[n][time] = 前 n 株草药、时间上限 time 时的最大总价值。
// 初值为 -1，表示这个状态还没算过。
int memo[MAXM][MAXT];

// 只考虑前 n 株草药，时间上限为 time，返回能取得的最大总价值。
int dfs(int n, int time) {
    // 没有草药可用，价值只能是 0。
    // 注意：不能同时写 time == 0 提前返回，否则耗时 0 的草药会被漏掉。
    if (n == 0) return 0;

    // 已经算过的状态直接返回，避免重复搜索。
    if (memo[n][time] != -1) return memo[n][time];

    // 选择 1：不采第 n 株草药。
    int choose_no = dfs(n - 1, time);

    // 选择 2：时间够的话，采第 n 株草药。
    int choose_yes = 0;
    if (time >= need_time[n])
        choose_yes = dfs(n - 1, time - need_time[n]) + herb_value[n];

    // 两个选择取较大值，并记忆下来。
    memo[n][time] = max(choose_no, choose_yes);
    return memo[n][time];
}

void read_input() {
    cin >> total_time >> herb_count;
    for (int i = 1; i <= herb_count; i++) {
        cin >> need_time[i] >> herb_value[i];
    }
}

void solve() {
    // 把记忆数组全部标成"还没算过"。
    memset(memo, -1, sizeof(memo));

    cout << dfs(herb_count, total_time) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
