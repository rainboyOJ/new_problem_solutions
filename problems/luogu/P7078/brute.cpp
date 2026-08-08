// brute.cpp：小数据完整博弈搜索，判断最强蛇吃后自己是否还能存活。
#include <bits/stdc++.h>
using namespace std;

struct Snake {
    long long value;
    int id;
};

int T, n;
long long a[20];
map<string, vector<Snake> > memo_alive;

bool weaker_than(const Snake &a, const Snake &b) {
    if (a.value != b.value) {
        return a.value < b.value;
    }
    return a.id < b.id;
}

string encode_state(const vector<Snake> &state) {
    string key;
    for (int i = 0; i < (int)state.size(); i++) {
        key += to_string(state[i].id);
        key += ':';
        key += to_string(state[i].value);
        key += ',';
    }
    return key;
}

bool contains_id(const vector<Snake> &alive, int id) {
    for (int i = 0; i < (int)alive.size(); i++) {
        if (alive[i].id == id) {
            return true;
        }
    }
    return false;
}

vector<Snake> play_game(vector<Snake> state) {
    sort(state.begin(), state.end(), weaker_than);
    string key = encode_state(state);
    auto it = memo_alive.find(key);
    if (it != memo_alive.end()) {
        return it->second;
    }

    if ((int)state.size() == 1) {
        memo_alive[key] = state;
        return state;
    }

    Snake weakest = state.front();
    Snake strongest = state.back();

    vector<Snake> next_state;
    for (int i = 1; i + 1 < (int)state.size(); i++) {
        next_state.push_back(state[i]);
    }
    Snake changed;
    changed.value = strongest.value - weakest.value;
    changed.id = strongest.id;
    next_state.push_back(changed);

    vector<Snake> alive_after_eat = play_game(next_state);
    if (contains_id(alive_after_eat, strongest.id)) {
        memo_alive[key] = alive_after_eat;
    } else {
        memo_alive[key] = state;
    }
    return memo_alive[key];
}

int solve_current_case() {
    vector<Snake> state;
    for (int i = 1; i <= n; i++) {
        Snake x;
        x.value = a[i];
        x.id = i;
        state.push_back(x);
    }
    memo_alive.clear();
    vector<Snake> alive = play_game(state);
    return (int)alive.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << solve_current_case() << '\n';

    for (int tc = 2; tc <= T; tc++) {
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++) {
            int x;
            long long y;
            cin >> x >> y;
            a[x] = y;
        }
        cout << solve_current_case() << '\n';
    }

    return 0;
}
