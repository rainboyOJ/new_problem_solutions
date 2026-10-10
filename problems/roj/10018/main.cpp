/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 07:12
 * update_at: 2026-10-10 08:56
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int MAX_STATE = 120000; // 轮廓状态上限：n=9,k=1 时实测 115975 个，留少量余量
const int MAX_M = 20;         // m <= 16，多留几格
const int MAX_COMB = 540;     // 组合数上标最大 2^n-2 = 510

struct State {
    string text; // text[i] 表示第 i 轮对手的 LIS 轮廓，0 表示还没有选择
    ll mask;     // 已经选择过哪些轮次（第 j 位为 1 表示第 j 轮已填），
                 // 同时它作为整数等于「已占用的选手总数」sum(2^j)
};

int n, m, need_lis, mod_value;
int beat[MAX_M]; // 被买通选手的实力（升序，值域 [2, 2^n]）
vector<string> all_text;      // DFS 生成的所有可达轮廓
map<string, int> visited_text;
State state_info[MAX_STATE];
map<string, int> state_id;
int state_count;
ll comb[MAX_COMB][MAX_COMB];
ll fact[MAX_COMB];
ll dp[MAX_M][MAX_STATE];

void add_mod(ll &x, ll y) {
    x += y;
    x %= mod_value;
}

// DFS 生成“按买通选手从小到大填入轮次”时可能出现的 LIS 轮廓。
void dfs_state(string text, int filled_count) {
    if (visited_text[text] != 0) {
        return;
    }
    visited_text[text] = 1;
    all_text.push_back(text);

    if (filled_count == n) {
        return;
    }

    for (int pos = 0; pos < n; pos++) {
        if (text[pos] == '0') {
            string next_text = text;
            char best = '0';
            for (int j = 0; j < pos; j++) {
                best = max(best, text[j]);
            }
            next_text[pos] = best + 1;
            dfs_state(next_text, filled_count + 1);
        }
    }
}

// 当前轮廓若把剩余空位尽量补好，仍能达到 need_lis，才保留下来做 DP 状态。
bool can_still_reach(string text) {
    char best = '0';
    for (int i = 0; i < n; i++) {
        if (text[i] == '0') {
            text[i] = best + 1;
            best++;
        } else {
            best = max(best, text[i]);
        }
    }

    char max_len = '0';
    for (int i = 0; i < n; i++) {
        max_len = max(max_len, text[i]);
    }
    return max_len >= '0' + need_lis;
}

void build_states() {
    state_count = 0;
    ll total_text = all_text.size();
    for (ll i = 0; i < total_text; i++) {
        string text = all_text[i];
        if (!can_still_reach(text)) {
            continue;
        }

        state_count++;
        state_info[state_count].text = text;
        state_info[state_count].mask = 0;
        for (int j = 0; j < n; j++) {
            if (text[j] != '0') {
                state_info[state_count].mask |= 1LL << j;
            }
        }
        state_id[text] = state_count;
    }
}

void init_comb() {
    fact[0] = 1;
    for (int i = 1; i <= 530; i++) {
        fact[i] = fact[i - 1] * i % mod_value;
    }

    comb[0][0] = 1;
    for (int i = 1; i <= 530; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0 || i == 1) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod_value;
            }
        }
    }
}

// 在 pos 轮填入一个更大的买通选手，它的 LIS 长度由左侧最大轮廓值 + 1 决定。
void fill_position(string &text, int pos) {
    char best = '0';
    for (int i = 0; i < pos; i++) {
        best = max(best, text[i]);
    }
    text[pos] = best + 1;
}

void solve_dp() {
    string start_text(n, '0');
    dp[0][state_id[start_text]] = 1;

    for (int i = 0; i < m; i++) {
        for (int id = 1; id <= state_count; id++) {
            if (dp[i][id] == 0) {
                continue;
            }

            add_mod(dp[i + 1][id], dp[i][id]); // 不使用第 i 个买通选手

            string text = state_info[id].text;
            ll used_mask = state_info[id].mask;
            for (int pos = 0; pos < n; pos++) {
                ll subtree_size = 1LL << pos;
                // 第 pos 轮需要一个自己的子树里最大的选手，且子树还要 2^pos-1 个更小的选手
                bool enough_smaller = beat[i] >= used_mask + subtree_size + 1;
                if (text[pos] == '0' && enough_smaller) {
                    string next_text = text;
                    fill_position(next_text, pos);

                    int next_id = state_id[next_text];
                    if (next_id == 0) {
                        continue;
                    }

                    ll choose_row = beat[i] - used_mask - 2; // 可供填子树的选手数
                    ll choose_col = subtree_size - 1;
                    ll ways = dp[i][id] * comb[choose_row][choose_col] % mod_value;
                    ways = ways * fact[subtree_size] % mod_value;
                    add_mod(dp[i + 1][next_id], ways);
                }
            }
        }
    }

    ll answer = 0;
    ll full_mask = (1LL << n) - 1;
    for (int id = 1; id <= state_count; id++) {
        if (state_info[id].mask == full_mask) {
            add_mod(answer, dp[m][id]);
        }
    }

    for (int i = 1; i <= n; i++) {
        add_mod(answer, answer); // 主角可以放在 2^n 个叶子位置
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    if (!(cin >> n >> m >> need_lis >> mod_value)) {
        return 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> beat[i];
    }
    sort(beat, beat + m);

    string start_text(n, '0');
    dfs_state(start_text, 0);
    build_states();
    init_comb();
    solve_dp();
    return 0;
}
