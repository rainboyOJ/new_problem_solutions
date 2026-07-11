/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:38
 * update_at: 2026-07-11 18:42
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;
const int MAXK = 8;

int n, k;
ll t[MAXN];
ll bessie_time;
bool possible[MAXK];

struct State {
    ll finish_time[MAXK];
    int next_cow;
};

void dfs_state(State state);

void assign_cows_to_farmers(State state, vector<int> farmers, vector<int> cows, ll event_time, int dep, bool used[]) {
    if (dep == (int)cows.size()) {
        dfs_state(state);
        return;
    }

    int cow = cows[dep];
    for (int i = 0; i < (int)farmers.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            int farmer = farmers[i];
            state.finish_time[farmer] = event_time + t[cow];
            assign_cows_to_farmers(state, farmers, cows, event_time, dep + 1, used);
            used[i] = false;
        }
    }
}

void dfs_state(State state) {
    ll min_time = state.finish_time[0];
    for (int i = 1; i < k; i++) {
        if (state.finish_time[i] < min_time) {
            min_time = state.finish_time[i];
        }
    }

    vector<int> farmers;
    for (int i = 0; i < k; i++) {
        if (state.finish_time[i] == min_time) {
            farmers.push_back(i);
        }
    }

    int remain = n - state.next_cow;
    if ((int)farmers.size() > remain) {
        bessie_time = min_time;
        for (int i = 0; i < (int)farmers.size(); i++) {
            possible[farmers[i]] = true;
        }
        return;
    }

    vector<int> cows;
    for (int i = 0; i < (int)farmers.size(); i++) {
        cows.push_back(state.next_cow + i);
    }
    state.next_cow += farmers.size();

    bool used[MAXK];
    for (int i = 0; i < MAXK; i++) {
        used[i] = false;
    }
    assign_cows_to_farmers(state, farmers, cows, min_time, 0, used);
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    for (int i = 0; i < k; i++) {
        possible[i] = false;
    }

    State start;
    for (int i = 0; i < k; i++) {
        start.finish_time[i] = t[i];
    }
    start.next_cow = k;
    bessie_time = -1;

    dfs_state(start);

    cout << bessie_time << '\n';
    for (int i = 0; i < k; i++) {
        cout << (possible[i] ? '1' : '0');
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
