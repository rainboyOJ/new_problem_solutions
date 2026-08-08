// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, q;
string left_part[MAXN], right_part[MAXN];

bool can_replace_at(const string &a, const string &b, int id, int start) {
    int len = (int)left_part[id].size();
    if (start + len > (int)a.size()) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (a[start + i] != left_part[id][i]) {
            return false;
        }
    }

    for (int i = 0; i < (int)a.size(); i++) {
        char after_char = a[i];
        if (start <= i && i < start + len) {
            after_char = right_part[id][i - start];
        }
        if (after_char != b[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> left_part[i] >> right_part[i];
    }

    while (q--) {
        string a, b;
        cin >> a >> b;

        long long ans = 0;
        if (a.size() == b.size()) {
            for (int id = 1; id <= n; id++) {
                for (int start = 0; start + (int)left_part[id].size() <= (int)a.size(); start++) {
                    if (can_replace_at(a, b, id, start)) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
