#include <bits/stdc++.h>
using namespace std;

static int T, N;
static vector<vector<int>> price;
static vector<vector<int>> memo_day;
static vector<vector<vector<int>>> memo_pick;

static int pick_profit(int day, int idx, int money) {
    if (idx == N) {
        return 0;
    }

    int &res = memo_pick[day][idx][money];
    if (res != -1) {
        return res;
    }

    // 不选当前纪念品，直接看后面的种类。
    res = pick_profit(day, idx + 1, money);

    int cost = price[day][idx];
    int gain = price[day + 1][idx] - price[day][idx];
    // 枚举当前纪念品买 1 件、2 件、... 的情况。
    for (int cnt = 1; cnt * cost <= money; ++cnt) {
        res = max(res, pick_profit(day, idx + 1, money - cnt * cost) + cnt * gain);
    }

    return res;
}

static int solve(int day, int money) {
    if (day == T - 1) {
        return money;
    }

    int &res = memo_day[day][money];
    if (res != -1) {
        return res;
    }

    // 当前这一天能赚到的最大额外金币。
    int gain = pick_profit(day, 0, money);
    res = solve(day + 1, money + gain);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> T >> N >> M;

    price.assign(T, vector<int>(N));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> price[i][j];
        }
    }

    memo_day.assign(T, vector<int>(10005, -1));
    memo_pick.assign(T, vector<vector<int>>(N + 1, vector<int>(10005, -1)));

    cout << solve(0, M) << '\n';
    return 0;
}
