// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int T, n;
string s1, s2, t1, t2;
vector<string> final_a, final_b;

void build_finals_dfs(const string &s, const string &t, int pos, string current, vector<string> &result) {
    if (pos == n) {
        result.push_back(current);
        return;
    }

    if (t[pos] == '0') {
        build_finals_dfs(s, t, pos + 1, current + s[pos], result);
        return;
    }

    int end_pos = pos;
    int count_one = 0;
    while (end_pos < n && t[end_pos] == '1') {
        count_one += s[end_pos] == '1';
        end_pos++;
    }

    int len = end_pos - pos;
    int total = 1 << len;
    for (int mask = 0; mask < total; mask++) {
        int bits = 0;
        for (int i = 0; i < len; i++) {
            if (mask & (1 << i)) {
                bits++;
            }
        }
        if (bits != count_one) {
            continue;
        }

        string next_string = current;
        for (int i = 0; i < len; i++) {
            if (mask & (1 << i)) {
                next_string.push_back('1');
            } else {
                next_string.push_back('0');
            }
        }
        build_finals_dfs(s, t, end_pos, next_string, result);
    }
}

int calc_score(const string &a, const string &b) {
    int score = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            score++;
        }
    }
    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        cin >> s1 >> s2 >> t1 >> t2;

        final_a.clear();
        final_b.clear();

        build_finals_dfs(s1, t1, 0, "", final_a);
        build_finals_dfs(s2, t2, 0, "", final_b);

        int ans = 0;
        for (int i = 0; i < (int)final_a.size(); i++) {
            for (int j = 0; j < (int)final_b.size(); j++) {
                ans = max(ans, calc_score(final_a[i], final_b[j]));
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
