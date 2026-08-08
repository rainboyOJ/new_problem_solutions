/**
 * Radio Transmission - KMP 法
 *
 * 答案 = n - 字符串最长 border
 * 只需求模式串自身的 prefix 函数，再取 pref[n-1]
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    vector<int> pref(n);
    int j = 0;
    for (int i = 1; i < n; ++i) {
        while (j && s[i] != s[j])
            j = pref[j - 1];
        if (s[i] == s[j])
            ++j;
        pref[i] = j;
    }

    cout << n - pref[n - 1] << '\n';
    return 0;
}
