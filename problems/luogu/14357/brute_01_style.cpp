// brute_01_style.cpp：另一种小数据暴力写法，按每个数字决定选或不选。
#include <bits/stdc++.h>
using namespace std;

string digits;
string current_digits;
string best_answer;

bool better(const string &a, const string &b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    return a > b;
}

void dfs_choose(int pos, bool has_non_zero) {
    if (pos == (int)digits.size()) {
        if (current_digits.empty() || !has_non_zero) {
            return;
        }

        string candidate = current_digits;
        sort(candidate.begin(), candidate.end(), greater<char>());
        if (better(candidate, best_answer)) {
            best_answer = candidate;
        }
        return;
    }

    // 这一位选 0：不使用当前数字。
    dfs_choose(pos + 1, has_non_zero);

    // 这一位选 1：使用当前数字。
    current_digits.push_back(digits[pos]);
    dfs_choose(pos + 1, has_non_zero || digits[pos] != '0');
    current_digits.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    for (int i = 0; i < (int)s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            digits.push_back(s[i]);
        }
    }

    dfs_choose(0, false);
    cout << best_answer << '\n';

    return 0;
}
