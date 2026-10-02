/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-06 08:46
 * update_at: 2026-10-01 20:57
 */
// brute.cpp：小数据暴力解，枚举所有 ? 的替换，再用递归判断定义是否合法。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL;

int n, K;
string pattern_s, cur;
vector<int> question_pos; // 所有 '?' 的位置

// memo_valid[l][r]：区间 [l,r] 是否为合法超级括号序列，-1 未计算，0/1 表示结果
// memo_atom[l][r]：区间 [l,r] 是否为单个外层括号块，-1 未计算，0/1 表示结果
int memo_valid[20][20];
int memo_atom[20][20];
ll answer;

// 区间 [l,r] 是否能全部填成星号（长度不超过 K 且每个位置都是 '*'）
bool is_star_string(int l, int r) {
    if (l > r) return false;
    if (r - l + 1 > K) return false;
    for (int i = l; i <= r; i++) {
        if (cur[i] != '*') return false;
    }
    return true;
}

bool is_valid(int l, int r);

// 区间 [l,r] 是否为单个外层括号块
bool is_atom(int l, int r) {
    if (l >= r) return false;
    if (memo_atom[l][r] != -1) return memo_atom[l][r];
    bool ok = false;
    if (cur[l] == '(' && cur[r] == ')') {
        if (l + 1 == r) ok = true;                                 // ()
        if (is_star_string(l + 1, r - 1)) ok = true;              // (S)
        if (l + 1 <= r - 1 && is_valid(l + 1, r - 1)) ok = true;  // (A)
        for (int p = l + 1; p <= r - 2; p++) {
            if (is_star_string(l + 1, p) && is_valid(p + 1, r - 1)) ok = true; // (SA)
            if (is_valid(l + 1, p) && is_star_string(p + 1, r - 1)) ok = true; // (AS)
        }
    }
    memo_atom[l][r] = ok;
    return ok;
}

// 区间 [l,r] 是否为合法超级括号序列
bool is_valid(int l, int r) {
    if (l > r) return false;
    if (memo_valid[l][r] != -1) return memo_valid[l][r];
    bool ok = is_atom(l, r);
    for (int start = l + 1; start <= r && !ok; start++) {
        if (!is_atom(start, r)) continue;
        if (is_valid(l, start - 1)) ok = true;                    // AB
        for (int star_len = 1; star_len <= K && start - star_len - 1 >= l; star_len++) {
            int star_l = start - star_len;
            int left_r = star_l - 1;
            if (is_star_string(star_l, start - 1) && is_valid(l, left_r)) {
                ok = true;                                         // ASB
            }
        }
    }
    memo_valid[l][r] = ok;
    return ok;
}

// 枚举第 idx 个 '?' 的替换（'(' / ')' / '*'）
void dfs_replace(int idx) {
    if (idx == (int)question_pos.size()) {
        memset(memo_valid, -1, sizeof(memo_valid));
        memset(memo_atom, -1, sizeof(memo_atom));
        if (is_valid(1, n)) {
            answer++;
            if (answer >= MOD) answer -= MOD;
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
