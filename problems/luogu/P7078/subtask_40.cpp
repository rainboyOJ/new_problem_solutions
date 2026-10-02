/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// subtask_40.cpp：20/40 分档（n <= 10）解法。完全按题面规则递归模拟决斗：
// 最强蛇若吃掉最弱蛇后自己仍能存活到最后就吃，否则选择不吃、决斗立刻结束。
// 不依赖任何贪心结论，直接翻译题面规则，适合小数据。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 15;

struct Snake {
    ll value;
    int id;
};

int T, n;
ll a[MAXN]; // a[i]：第 i 条蛇的体力值

// 比较两条蛇的强弱：体力值大者强，相同则编号大者强。
// 参数用 x/y，避开全局体力值数组 a[]。
bool weaker_than(const Snake &x, const Snake &y) {
    if (x.value != y.value) {
        return x.value < y.value;
    }
    return x.id < y.id;
}

// 判断编号为 id 的蛇是否在存活集合中。
bool contains_id(const vector<Snake> &alive, int id) {
    for (int i = 0; i < (int)alive.size(); i++) {
        if (alive[i].id == id) {
            return true;
        }
    }
    return false;
}

// 递归模拟决斗，返回最终存活的蛇。
// 当前最强蛇先尝试吃：吃完后若自己仍能存活到最后就吃，否则选择不吃、决斗结束。
vector<Snake> play_game(vector<Snake> state) {
    sort(state.begin(), state.end(), weaker_than);
    if ((int)state.size() == 1) {
        return state;
    }

    Snake weakest = state.front();
    Snake strongest = state.back();

    // 假设最强蛇吃掉最弱蛇，构造下一状态。
    vector<Snake> next_state;
    for (int i = 1; i + 1 < (int)state.size(); i++) {
        next_state.push_back(state[i]);
    }
    Snake changed;
    changed.value = strongest.value - weakest.value;
    changed.id = strongest.id;
    next_state.push_back(changed);

    // 递归求"吃完之后"的存活集合。
    vector<Snake> alive_after_eat = play_game(next_state);
    if (contains_id(alive_after_eat, strongest.id)) {
        return alive_after_eat; // 吃了能活到最后，就吃
    }
    return state; // 吃了会死，选择不吃，决斗结束
}

// 求解单组测试数据，返回最终存活蛇的数量。
int solve_current_case() {
    vector<Snake> state;
    for (int i = 1; i <= n; i++) {
        Snake x;
        x.value = a[i];
        x.id = i;
        state.push_back(x);
    }
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
            ll y;
            cin >> x >> y;
            a[x] = y;
        }
        cout << solve_current_case() << '\n';
    }

    return 0;
}
