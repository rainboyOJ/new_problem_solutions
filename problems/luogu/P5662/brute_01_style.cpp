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
vector<int> choose_buy; // choose_buy[i] = 0/1，表示第 i 件候选纪念品不买/买
int current_money;
int best_gain;

bool check() {
    int cost = 0;
    for (int i = 0; i < (int)choices.size(); i++) {
        if (choose_buy[i] == 1) cost += choices[i].cost;
    }
    return cost <= current_money;
}

int calc_gain() {
    int gain = 0;
    for (int i = 0; i < (int)choices.size(); i++) {
        if (choose_buy[i] == 1) gain += choices[i].gain;
    }
    return gain;
}

void dfs_choice(int dep) {
    if (dep == (int)choices.size()) {
        if (check()) {
            int value = calc_gain();
            if (best_gain < value) best_gain = value;
        }
        return;
    }

    // 第 dep 件候选纪念品的 01 选择：0 不买，1 买。
    for (int i = 0; i <= 1; i++) {
        choose_buy[dep] = i;
        dfs_choice(dep + 1);
    }
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

    choose_buy.assign(choices.size(), 0);
    current_money = money;
    best_gain = 0;
    dfs_choice(0);
    return best_gain;
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
