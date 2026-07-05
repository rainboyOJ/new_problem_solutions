// brute_01_style.cpp：01 序列风格暴力，把每天能买的每一件纪念品看成选/不选。
#include <bits/stdc++.h>
using namespace std;

struct Choice {
    int cost;
    int gain;
};

const int MAXT = 105;
const int MAXN = 105;

int T, N, start_money;
int price[MAXT][MAXN];
vector<Choice> choices;
vector<vector<int> > memo;

int dfs_choice(int dep, int money_left) {
    if (dep == (int)choices.size()) {
        return 0;
    }

    int &res = memo[dep][money_left];
    if (res != -1) {
        return res;
    }

    // 第 dep 件候选纪念品不买，对应 01 序列中的 0。
    res = dfs_choice(dep + 1, money_left);

    // 第 dep 件候选纪念品买下，对应 01 序列中的 1。
    if (money_left >= choices[dep].cost) {
        res = max(res, dfs_choice(dep + 1, money_left - choices[dep].cost) + choices[dep].gain);
    }

    return res;
}

int best_gain_one_day(int day, int money) {
    choices.clear();

    for (int item = 1; item <= N; item++) {
        int cost = price[day][item];
        int gain = price[day + 1][item] - price[day][item];
        if (gain <= 0) {
            continue;
        }

        // 同一种纪念品可以买多件，这里把每一件展开成一个 01 选择。
        for (int cnt = 1; cnt * cost <= money; cnt++) {
            choices.push_back({cost, gain});
        }
    }

    memo.assign(choices.size() + 1, vector<int>(money + 1, -1));
    return dfs_choice(0, money);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> N >> start_money;
    for (int day = 1; day <= T; day++) {
        for (int item = 1; item <= N; item++) {
            cin >> price[day][item];
        }
    }

    int money = start_money;
    for (int day = 1; day < T; day++) {
        money += best_gain_one_day(day, money);
    }

    cout << money << '\n';
    return 0;
}
