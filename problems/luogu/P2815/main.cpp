#include <bits/stdc++.h>
using namespace std;

string s;
string part[10];
string short_part[10];

string trim_leading_zero(const string &t) {
    int i = 0;
    while (i < 4 && t[i] == '0') {
        i++;
    }
    if (i == 4) {
        return "0";
    }
    return t.substr(i);
}

string join_parts(int l, int r) {
    if (l > r) {
        return "";
    }

    string res = "";
    for (int i = l; i <= r; i++) {
        if (!res.empty()) {
            res += ':';
        }
        res += short_part[i];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int idx = 1;
    int last = 0;
    for (int i = 0; i <= (int)s.size(); i++) {
        if (i == (int)s.size() || s[i] == ':') {
            part[idx++] = s.substr(last, i - last);
            last = i + 1;
        }
    }

    for (int i = 1; i <= 8; i++) {
        short_part[i] = trim_leading_zero(part[i]);
    }

    int best_l = -1, best_r = -1;
    int best_len = 0;
    int i = 1;
    while (i <= 8) {
        if (part[i] != "0000") {
            i++;
            continue;
        }

        int j = i;
        while (j <= 8 && part[j] == "0000") {
            j++;
        }

        int len = j - i;
        if (len > best_len) {
            best_len = len;
            best_l = i;
            best_r = j - 1;
        }
        i = j;
    }

    // 没有任何一组 0000 时，只做去前导零。
    if (best_len == 0) {
        cout << join_parts(1, 8) << '\n';
        return 0;
    }

    string left = join_parts(1, best_l - 1);
    string right = join_parts(best_r + 1, 8);

    if (left.empty() && right.empty()) {
        cout << "::\n";
    }
    else if (left.empty()) {
        cout << "::" << right << '\n';
    }
    else if (right.empty()) {
        cout << left << "::\n";
    }
    else {
        cout << left << "::" << right << '\n';
    }

    return 0;
}
