#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    int best = 0;
    string best_str = s; // 当前字典序最小的循环串

    // brute.cpp：直接枚举所有旋转，找字典序最小的那个。
    // 复杂度是 O(n^2)，只适合小数据验证。
    for (int start = 1; start < n; start++) {
        string cur = s.substr(start) + s.substr(0, start);
        if (cur < best_str) {
            best_str = cur;
            best = start;
        }
    }

    cout << best << '\n';
    return 0;
}
