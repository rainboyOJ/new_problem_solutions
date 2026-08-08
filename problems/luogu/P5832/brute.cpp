// brute.cpp：直接枚举 K，并暴力检查所有长度为 K 的子串是否互不相同。
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool check(int len) {
    for (int i = 0; i + len - 1 < n; i++) {
        for (int j = i + 1; j + len - 1 < n; j++) {
            bool same = true;
            for (int k = 0; k < len; k++) {
                if (s[i + k] != s[j + k]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int len = 1; len <= n; len++) {
        if (check(len)) {
            cout << len << '\n';
            return 0;
        }
    }

    return 0;
}
