/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:30
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int MAXP = 6;
const int STATE_BITS = 24;
const int STATE_COUNT = 1 << STATE_BITS;
const long long INF = (1LL << 60);

struct StateCost {
    int code;
    long long value;
};

int n, m, p;
int is_user[MAXN];
int suffix_user[MAXN + 2];
long long edge_cost[MAXN][MAXP + 1];
long long *best;
long long answer;
vector<StateCost> current_states;
vector<int> next_codes;

// 把窗口内的连通分量重新编号。标签按首次出现的位置编号，保证同一状态只有一种编码。
int pack_state(int label[]) {
    int remap[8] = {};
    int next_label = 0;
    int code = 0;
    int new_has_terminal[8] = {};

    for (int i = 1; i <= p; i++) {
        int old_label = label[i];
        if (old_label == 0) {
            continue;
        }
        if (remap[old_label] == 0) {
            remap[old_label] = ++next_label;
            new_has_terminal[next_label] = (label[7] >> old_label) & 1;
        }
        code |= remap[old_label] << (3 * (i - 1));
    }
    for (int i = 1; i <= next_label; i++) {
        if (new_has_terminal[i]) {
            code |= 1 << (18 + i - 1);
        }
    }
    return code;
}

void update_next(int code, long long value) {
    if (best[code] == INF) {
        best[code] = value;
        next_codes.push_back(code);
    } else if (value < best[code]) {
        best[code] = value;
    }
}

// label[0] 是本轮离开窗口的设备；label[7] 的各 bit 记录原分量是否含用户设备。
void forget_oldest(int label[], long long value, int future_user_count) {
    int leaving_label = label[0];
    bool still_active = false;
    for (int i = 1; i <= p; i++) {
        if (label[i] == leaving_label) {
            still_active = true;
        }
    }

    if (leaving_label != 0 && !still_active && ((label[7] >> leaving_label) & 1)) {
        bool has_other_user_component = false;
        for (int i = 1; i <= p; i++) {
            int component = label[i];
            if (component != 0 && component != leaving_label
                    && ((label[7] >> component) & 1)) {
                has_other_user_component = true;
            }
        }

        // 这个分量再也无法和未来连边。它只能恰好是包含所有用户的最终连通块。
        if (!has_other_user_component && future_user_count == 0) {
            answer = min(answer, value);
        }
        return;
    }

    update_next(pack_state(label), value);
}

void transfer_one_state(const StateCost &state, int position) {
    int base_label[8] = {};
    int max_label = 0;
    for (int i = 0; i < p; i++) {
        base_label[i] = (state.code >> (3 * i)) & 7;
        max_label = max(max_label, base_label[i]);
    }
    for (int i = 1; i <= max_label; i++) {
        if ((state.code >> (18 + i - 1)) & 1) {
            base_label[7] |= 1 << i;
        }
    }

    int future_user_count = position < n ? suffix_user[position + 1] : 0;
    if (position > n) {
        base_label[p] = 0;
        forget_oldest(base_label, state.value, 0);
        return;
    }

    // 非用户设备可以完全不选。
    if (!is_user[position]) {
        base_label[p] = 0;
        forget_oldest(base_label, state.value, future_user_count);
    }

    // 选入当前设备，并枚举它分别连接哪些已有连通分量。
    int new_label = max_label + 1;
    base_label[p] = new_label;
    int min_cost[8];
    for (int i = 0; i < 8; i++) {
        min_cost[i] = INT_MAX;
    }
    for (int distance = 1; distance <= p; distance++) {
        int component = base_label[p - distance];
        if (component != 0 && edge_cost[position][distance] < min_cost[component]) {
            min_cost[component] = (int)edge_cost[position][distance];
        }
    }

    int available[6];
    int available_count = 0;
    for (int component = 1; component <= max_label; component++) {
        if (min_cost[component] != INT_MAX) {
            available[available_count++] = component;
        }
    }

    for (int mask = 0; mask < (1 << available_count); mask++) {
        int label[8];
        for (int i = 0; i < 8; i++) {
            label[i] = base_label[i];
        }
        if (is_user[position]) {
            label[7] |= 1 << new_label;
        }

        long long added_cost = 0;
        for (int k = 0; k < available_count; k++) {
            if ((mask & (1 << k)) == 0) {
                continue;
            }
            int old_label = available[k];
            added_cost += min_cost[old_label];
            if ((label[7] >> old_label) & 1) {
                label[7] |= 1 << new_label;
            }
            for (int i = 0; i < p; i++) {
                if (label[i] == old_label) {
                    label[i] = new_label;
                }
            }
        }
        forget_oldest(label, state.value + added_cost, future_user_count);
    }
}

void solve_one_case() {
    cin >> n >> m >> p;
    string users;
    cin >> users;
    for (int i = 1; i <= n; i++) {
        is_user[i] = users[i - 1] == '1';
    }
    suffix_user[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        suffix_user[i] = suffix_user[i + 1] + is_user[i];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= p; j++) {
            edge_cost[i][j] = INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edge_cost[v][v - u] = w;
    }

    current_states.clear();
    StateCost initial_state = {0, 0};
    current_states.push_back(initial_state);
    answer = INF;
    for (int position = 1; position <= n + p; position++) {
        next_codes.clear();
        for (int i = 0; i < (int)current_states.size(); i++) {
            transfer_one_state(current_states[i], position);
        }

        current_states.clear();
        for (int i = 0; i < (int)next_codes.size(); i++) {
            int code = next_codes[i];
            StateCost next_state = {code, best[code]};
            current_states.push_back(next_state);
            best[code] = INF;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    best = new long long[STATE_COUNT];
    fill(best, best + STATE_COUNT, INF);

    int test_count;
    cin >> test_count;
    while (test_count--) {
        solve_one_case();
    }

    delete[] best;
    return 0;
}
