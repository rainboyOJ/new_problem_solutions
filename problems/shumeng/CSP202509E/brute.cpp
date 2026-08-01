/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 11:35
 */
// brute.cpp：递归枚举每天不工作、造题、验题或两人都工作的选择。
#include <bits/stdc++.h>
using namespace std;

int n;
long long budget;
vector<long long> make_cost;
vector<long long> check_cost;
int answer;

void dfs(int day, int balance, long long cost, int count) {
    if (cost > budget) {
        return;
    }
    if (day == n + 1) {
        if (balance == 0) {
            answer = max(answer, count);
        }
        return;
    }
    dfs(day + 1, balance, cost, count);
    dfs(day + 1, balance + 1, cost + make_cost[day], count);
    if (balance > 0) {
        dfs(day + 1, balance - 1, cost + check_cost[day], count + 1);
    }
    dfs(day + 1, balance,
        cost + make_cost[day] + check_cost[day], count + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> budget;
    make_cost.assign(n + 1, 0);
    check_cost.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> make_cost[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> check_cost[i];
    }
    dfs(1, 0, 0, 0);
    cout << answer << '\n';
    return 0;
}
