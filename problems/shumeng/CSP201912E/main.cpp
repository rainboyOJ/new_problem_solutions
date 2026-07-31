/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:30
 */
#include <bits/stdc++.h>
using namespace std;

const int BASE = 1 << 20;
const int NODE_COUNT = BASE << 1;
const int MAX_STATE = 32;
const long long MOD = 2009731336725594113LL;
const int MOD_SMALL = 2019;

long long unit[5] = {
    314882150829468584LL,
    427197303358170108LL,
    1022292690726729920LL,
    1698479428772363217LL,
    2006101093849356424LL,
};

int n, query_count, state_count;
int segment[NODE_COUNT][MAX_STATE];
unsigned char lazy_tag[NODE_COUNT];
int multiply_state[MAX_STATE][MAX_STATE], unit_state[5];
vector<long long> state_multiplier;

long long multiply_mod(long long left, long long right) {
    return (long long)((__int128)left * right % MOD);
}

int find_state(long long value) {
    for (int i = 0; i < (int)state_multiplier.size(); i++) {
        if (state_multiplier[i] == value) return i;
    }
    return -1;
}

void build_states() {
    state_multiplier.push_back(1);
    for (int position = 0; position < (int)state_multiplier.size(); position++) {
        for (int i = 0; i < 5; i++) {
            long long next = multiply_mod(state_multiplier[position], unit[i]);
            if (find_state(next) == -1) state_multiplier.push_back(next);
        }
    }
    state_count = (int)state_multiplier.size();
    for (int i = 0; i < 5; i++) unit_state[i] = find_state(unit[i]);
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < state_count; j++) {
            multiply_state[i][j] = find_state(multiply_mod(state_multiplier[i], state_multiplier[j]));
        }
    }
}

void apply_state(int node, int state) {
    if (state == 0) return;
    int old_sum[MAX_STATE];
    for (int i = 0; i < state_count; i++) old_sum[i] = segment[node][i];
    for (int i = 0; i < state_count; i++) {
        segment[node][i] = old_sum[multiply_state[state][i]];
    }
    lazy_tag[node] = (unsigned char)multiply_state[lazy_tag[node]][state];
}

void push_down(int node) {
    if (lazy_tag[node] == 0) return;
    apply_state(node << 1, lazy_tag[node]);
    apply_state(node << 1 | 1, lazy_tag[node]);
    lazy_tag[node] = 0;
}

void pull_up(int node) {
    for (int i = 0; i < state_count; i++) {
        segment[node][i] = segment[node << 1][i] + segment[node << 1 | 1][i];
    }
}

void update(int node, int left, int right, int query_left, int query_right, int state) {
    if (query_left <= left && right <= query_right) {
        apply_state(node, state);
        return;
    }
    push_down(node);
    int middle = (left + right) >> 1;
    if (query_left <= middle) update(node << 1, left, middle, query_left, query_right, state);
    if (query_right > middle) update(node << 1 | 1, middle + 1, right, query_left, query_right, state);
    pull_up(node);
}

int query(int node, int left, int right, int query_left, int query_right) {
    if (query_left <= left && right <= query_right) return segment[node][0];
    push_down(node);
    int middle = (left + right) >> 1;
    int answer = 0;
    if (query_left <= middle) answer += query(node << 1, left, middle, query_left, query_right);
    if (query_right > middle) answer += query(node << 1 | 1, middle + 1, right, query_left, query_right);
    return answer;
}

void build_segment_tree() {
    long long remainder[MAX_STATE] = {};
    for (int i = 1; i <= n; i++) {
        int node = BASE + i - 1;
        for (int j = 0; j < state_count; j++) {
            remainder[j] += state_multiplier[j];
            if (remainder[j] >= MOD) remainder[j] -= MOD;
            segment[node][j] = (int)(remainder[j] % MOD_SMALL);
        }
    }
    for (int node = BASE - 1; node >= 1; node--) pull_up(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> query_count;
    build_states();
    build_segment_tree();
    while (query_count--) {
        int left, right;
        cin >> left >> right;
        int answer = query(1, 1, BASE, left, right);
        cout << answer << '\n';
        update(1, 1, BASE, left, right, unit_state[answer % 5]);
    }

    return 0;
}
