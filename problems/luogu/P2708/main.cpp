#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int n = (int) s.size();
    int ans = 0;

    // 每次相邻字符变化，说明至少要多做一次翻转来切换当前前缀状态。
    for (int i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            ans++;
        }
    }

    // 最右端如果还是 0，最后还必须再翻一次。
    if (s[n - 1] == '0') {
        ans++;
    }

    cout << ans << '\n';
    return 0;
}
