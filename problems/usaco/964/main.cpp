/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:40
 * update_at: 2026-07-11 14:41
 */
#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool has_duplicate(int len) {
    set<string> seen;

    for (int i = 0; i + len <= n; i++) {
        string sub = s.substr(i, len);
        if (seen.count(sub)) {
            return true;
        }
        seen.insert(sub);
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    for (int len = 1; len <= n; len++) {
        if (!has_duplicate(len)) {
            cout << len << '\n';
            return 0;
        }
    }

    return 0;
}
