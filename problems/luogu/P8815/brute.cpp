#include <bits/stdc++.h>
using namespace std;

struct Result {
    int value;
    long long short_and;
    long long short_or;
};

static string s;
static int pos_idx;

Result parse_or();
void skip_or();

Result parse_factor() {
    if (s[pos_idx] == '0' || s[pos_idx] == '1') {
        int value = s[pos_idx] - '0';
        ++pos_idx;
        return {value, 0, 0};
    }

    ++pos_idx;  // skip '('
    Result res = parse_or();
    ++pos_idx;  // skip ')'
    return res;
}

void skip_factor() {
    if (s[pos_idx] == '0' || s[pos_idx] == '1') {
        ++pos_idx;
        return;
    }

    ++pos_idx;  // skip '('
    skip_or();
    ++pos_idx;  // skip ')'
}

Result parse_and() {
    Result left_res = parse_factor();

    while (pos_idx < (int)s.size() && s[pos_idx] == '&') {
        ++pos_idx;
        if (left_res.value == 0) {
            ++left_res.short_and;
            skip_factor();
        } else {
            Result right_res = parse_factor();
            left_res.value &= right_res.value;
            left_res.short_and += right_res.short_and;
            left_res.short_or += right_res.short_or;
        }
    }
    return left_res;
}

void skip_and() {
    skip_factor();
    while (pos_idx < (int)s.size() && s[pos_idx] == '&') {
        ++pos_idx;
        skip_factor();
    }
}

Result parse_or() {
    Result left_res = parse_and();

    while (pos_idx < (int)s.size() && s[pos_idx] == '|') {
        ++pos_idx;
        if (left_res.value == 1) {
            ++left_res.short_or;
            skip_and();
        } else {
            Result right_res = parse_and();
            left_res.value |= right_res.value;
            left_res.short_and += right_res.short_and;
            left_res.short_or += right_res.short_or;
        }
    }
    return left_res;
}

void skip_or() {
    skip_and();
    while (pos_idx < (int)s.size() && s[pos_idx] == '|') {
        ++pos_idx;
        skip_and();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    pos_idx = 0;
    Result ans = parse_or();
    cout << ans.value << '\n';
    cout << ans.short_and << ' ' << ans.short_or << '\n';
    return 0;
}
