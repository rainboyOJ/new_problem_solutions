// brute.cpp：小数据暴力解，枚举所有 ? 的替换，再用递归判断定义是否合法。
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int n, K;
string pattern_s, cur;
vector<int> question_pos;
int memo_valid[20][20], memo_atom[20][20];
long long answer;

bool is_star_string(int l, int r) {
    if (l > r) return false;
    if (r - l + 1 > K) return false;
    for (int i = l; i <= r; i++) {
        if (cur[i] != '*') return false;
    }
    return true;
}

bool is_valid(int l, int r);

bool is_atom(int l, int r) {
    if (l >= r) return false;
    if (memo_atom[l][r] != -1) return memo_atom[l][r];
    bool ok = false;
    if (cur[l] == '(' && cur[r] == ')') {
        if (l + 1 == r) ok = true;
        if (is_star_string(l + 1, r - 1)) ok = true;
        if (l + 1 <= r - 1 && is_valid(l + 1, r - 1)) ok = true;
        for (int p = l + 1; p <= r - 2; p++) {
            if (is_star_string(l + 1, p) && is_valid(p + 1, r - 1)) ok = true;
            if (is_valid(l + 1, p) && is_star_string(p + 1, r - 1)) ok = true;
        }
    }
    memo_atom[l][r] = ok;
    return ok;
}

bool is_valid(int l, int r) {
    if (l > r) return false;
    if (memo_valid[l][r] != -1) return memo_valid[l][r];
    bool ok = is_atom(l, r);
    for (int start = l + 1; start <= r && !ok; start++) {
        if (!is_atom(start, r)) continue;
        if (is_valid(l, start - 1)) ok = true;
        for (int star_len = 1; star_len <= K && start - star_len - 1 >= l; star_len++) {
            int star_l = start - star_len;
            int left_r = star_l - 1;
            if (is_star_string(star_l, start - 1) && is_valid(l, left_r)) {
                ok = true;
            }
        }
    }
    memo_valid[l][r] = ok;
    return ok;
}

void dfs_replace(int idx) {
    if (idx == (int)question_pos.size()) {
        memset(memo_valid, -1, sizeof(memo_valid));
        memset(memo_atom, -1, sizeof(memo_atom));
        if (is_valid(1, n)) {
            answer++;
        }
        return;
    }

    int pos = question_pos[idx];
    cur[pos] = '(';
    dfs_replace(idx + 1);
    cur[pos] = ')';
    dfs_replace(idx + 1);
    cur[pos] = '*';
    dfs_replace(idx + 1);
    cur[pos] = '?';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> K >> pattern_s;
    cur = " " + pattern_s;
    for (int i = 1; i <= n; i++) {
        if (cur[i] == '?') {
            question_pos.push_back(i);
        }
    }

    dfs_replace(0);
    cout << (answer % MOD) << '\n';
    return 0;
}
