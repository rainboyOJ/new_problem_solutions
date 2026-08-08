#include <bits/stdc++.h>
using namespace std;

string t, s;

// Z 函数：z[i] 表示 str[i..] 与 str[0..] 的最长公共前缀长度。
vector<int> z_function(const string &str) {
    int len = (int) str.size();
    vector<int> z(len, 0);
    int l = 0, r = 0;
    z[0] = len;
    for (int i = 1; i < len; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < len && str[z[i]] == str[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int len_t, len_s;
    cin >> len_t >> len_s;
    cin >> t >> s;

    int m = (int) t.size();
    int n = (int) s.size();

    string merged = t + "#" + s;
    vector<int> zf = z_function(merged);

    vector<int> reach(n, 0);
    for (int i = 0; i < n; i++) {
        reach[i] = min(zf[m + 1 + i], m);
    }

    // 把每个位置 i 看成一个区间 [i, i + reach[i]]。
    // 问最少用多少段覆盖到 n，就是经典最少跳数贪心。
    int ans = 0;
    int cur_end = 0;
    int far = 0;
    int i = 0;

    while (cur_end < n) {
        while (i <= cur_end && i < n) {
            far = max(far, i + reach[i]);
            i++;
        }
        if (far <= cur_end) {
            cout << "Fake\n";
            return 0;
        }
        ans++;
        cur_end = far;
    }

    cout << ans << '\n';
    return 0;
}
