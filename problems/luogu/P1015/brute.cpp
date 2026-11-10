/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:59
 * update_at: 2026-11-10 23:59
 */

// brute.cpp：小数据高精度加法基线模拟
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int to_v(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return c - 'a' + 10;
}

bool check_pal(const vector<int>& v) {
    int s = 0, e = v.size() - 1;
    while (s < e) {
        if (v[s] != v[e]) return false;
        s++;
        e--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int base;
    string s;
    if (!(cin >> base >> s)) return 0;

    vector<int> a;
    for (int i = s.size() - 1; i >= 0; --i) a.push_back(to_v(s[i]));

    for (int step = 1; step <= 30; ++step) {
        vector<int> b = a;
        reverse(b.begin(), b.end());
        vector<int> c;
        int rem = 0;
        for (size_t i = 0; i < a.size(); ++i) {
            int cur = a[i] + b[i] + rem;
            c.push_back(cur % base);
            rem = cur / base;
        }
        if (rem) c.push_back(rem);
        a = c;
        if (check_pal(a)) {
            cout << "STEP=" << step << "\n";
            return 0;
        }
    }
    cout << "Impossible!\n";
    return 0;
}
