// brute.cpp：小数据暴力解，逐个模式串检查它是否在文本串中出现。
#include <bits/stdc++.h>
using namespace std;

int n;
string pattern_list[105];
string text;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pattern_list[i];
    }
    cin >> text;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        bool found = false;
        int len = (int)pattern_list[i].size();
        for (int l = 0; l + len <= (int)text.size(); l++) {
            bool same = true;
            for (int j = 0; j < len; j++) {
                if (text[l + j] != pattern_list[i][j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                found = true;
                break;
            }
        }
        if (found) ans++;
    }

    cout << ans << "\n";

    return 0;
}
