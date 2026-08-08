#include <bits/stdc++.h>
using namespace std;

struct Girl {
    int money;
    int rp;
    int time;
};

int n, money, rp;
vector<Girl> girls;
vector<int> choose_girl; // choose_girl[i] = 0/1，表示第 i 个 MM 不选/选
int best_cnt = 0;
int best_time = 0;

void calc_state(int &cur_money, int &cur_rp, int &cur_cnt, int &cur_time) {
    cur_money = 0;
    cur_rp = 0;
    cur_cnt = 0;
    cur_time = 0;
    for (int i = 0; i < n; i++) {
        if (choose_girl[i] == 1) {
            cur_money += girls[i].money;
            cur_rp += girls[i].rp;
            cur_cnt++;
            cur_time += girls[i].time;
        }
    }
}

bool check() {
    int cur_money, cur_rp, cur_cnt, cur_time;
    calc_state(cur_money, cur_rp, cur_cnt, cur_time);
    return cur_money <= money && cur_rp <= rp;
}

void update_answer() {
    int cur_money, cur_rp, cur_cnt, cur_time;
    calc_state(cur_money, cur_rp, cur_cnt, cur_time);
    if (cur_money <= money && cur_rp <= rp) {
        if (cur_cnt > best_cnt || (cur_cnt == best_cnt && cur_time < best_time)) {
            best_cnt = cur_cnt;
            best_time = cur_time;
        }
    }
}

// dfs_choose 只负责枚举完整 01 序列。
void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            update_answer();
        }
        return;
    }

    // 第 dep 个 MM 的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_girl[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    girls.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> girls[i].money >> girls[i].rp >> girls[i].time;
    }
    cin >> money >> rp;

    choose_girl.assign(n, 0);
    dfs_choose(0);
    cout << best_time << '\n';

    return 0;
}
