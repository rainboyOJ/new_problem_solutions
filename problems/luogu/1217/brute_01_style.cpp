// brute_01_style.cpp：选择序列风格暴力，按位构造回文数的前半部分。
#include <bits/stdc++.h>
using namespace std;

int a, b;
int digit[10];
vector<int> candidates;

bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= x; d++) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int build_palindrome(int half_len) {
    int res = 0;
    for (int i = 1; i <= half_len; i++) {
        res = res * 10 + digit[i];
    }
    for (int i = half_len - 1; i >= 1; i--) {
        res = res * 10 + digit[i];
    }
    return res;
}

void add_if_ok(int x) {
    if (x < a || x > b) {
        return;
    }
    if (is_prime(x)) {
        candidates.push_back(x);
    }
}

// dfs_build(pos)：正在填写奇数位回文数前半部分的第 pos 位。
void dfs_build(int pos, int half_len) {
    if (pos == half_len + 1) {
        add_if_ok(build_palindrome(half_len));
        return;
    }

    int left = 0;
    if (pos == 1) {
        left = 1; // 最高位不能为 0。
    }

    for (int d = left; d <= 9; d++) {
        digit[pos] = d;
        dfs_build(pos + 1, half_len);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    add_if_ok(11);

    // b <= 100000000，奇数位回文只需要枚举 1、3、5、7 位。
    for (int half_len = 1; half_len <= 4; half_len++) {
        dfs_build(1, half_len);
    }

    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    for (int i = 0; i < (int)candidates.size(); i++) {
        cout << candidates[i] << '\n';
    }

    return 0;
}
