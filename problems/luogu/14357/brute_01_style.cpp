// brute_01_style.cpp：01 序列风格暴力，按每个数字决定选或不选。
#include <bits/stdc++.h>
using namespace std;

string digits;
vector<int> choose_digit; // choose_digit[i] = 0/1，表示第 i 个数字不选/选
string best_answer;

bool better(const string &a, const string &b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    return a > b;
}

bool check() {
    for (int i = 0; i < (int)digits.size(); i++) {
        if (choose_digit[i] == 1 && digits[i] != '0') {
            return true;
        }
    }
    return false;
}

string calc_answer() {
    string candidate = "";
    for (int i = 0; i < (int)digits.size(); i++) {
        if (choose_digit[i] == 1) {
            candidate.push_back(digits[i]);
        }
    }
    sort(candidate.begin(), candidate.end(), greater<char>());
    return candidate;
}

void dfs_choose(int pos) {
    if (pos == (int)digits.size()) {
        if (!check()) {
            return;
        }
        string candidate = calc_answer();
        if (better(candidate, best_answer)) {
            best_answer = candidate;
        }
        return;
    }

    // 第 pos 个数字的 01 选择：0 不使用，1 使用。
    for (int i = 0; i <= 1; i++) {
        choose_digit[pos] = i;
        dfs_choose(pos + 1);
    }
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

    choose_digit.assign(digits.size(), 0);
    dfs_choose(0);
    cout << best_answer << '\n';

    return 0;
}
