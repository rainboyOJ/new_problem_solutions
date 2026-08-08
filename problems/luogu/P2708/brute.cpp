// brute.cpp：从右往左真正模拟翻前缀，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

string s;

void flip_prefix(int right_pos) {
    for (int i = 0; i <= right_pos; i++) {
        if (s[i] == '0') {
            s[i] = '1';
        }
        else {
            s[i] = '0';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int ans = 0;
    int n = (int) s.size();

    // 从右往左定死每个位置：如果当前位置是 0，只能翻到这里为止。
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            flip_prefix(i);
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
