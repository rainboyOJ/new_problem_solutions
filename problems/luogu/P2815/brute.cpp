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

string build_answer(int l, int r) {
    string left = "";
    for (int i = 1; i < l; i++) {
        if (!left.empty()) {
            left += ':';
        }
        left += short_part[i];
    }

    string right = "";
    for (int i = r + 1; i <= 8; i++) {
        if (!right.empty()) {
            right += ':';
        }
        right += short_part[i];
    }

    if (l > r) {
        if (left.empty()) {
            return right;
        }
        if (right.empty()) {
            return left;
        }
        return left + ":" + right;
    }

    if (left.empty() && right.empty()) {
        return "::";
    }
    if (left.empty()) {
        return "::" + right;
    }
    if (right.empty()) {
        return left + "::";
    }
    return left + "::" + right;
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

    string best = build_answer(2, 1); // 表示不使用 ::

    int best_len = 0;
    int best_l = -1, best_r = -1;
    for (int l = 1; l <= 8; l++) {
        for (int r = l; r <= 8; r++) {
            bool ok = true;
            for (int i = l; i <= r; i++) {
                if (part[i] != "0000") {
                    ok = false;
                    break;
                }
            }
            if (!ok) {
                continue;
            }

            int len = r - l + 1;
            if (len > best_len) {
                best_len = len;
                best_l = l;
                best_r = r;
            }
        }
    }

    if (best_len > 0) {
        best = build_answer(best_l, best_r);
    }

    cout << best << '\n';
    return 0;
}
