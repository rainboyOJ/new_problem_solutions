// brute.cpp：按题意逐条判断本地车、外地车和尾号限行规则。
#include <bits/stdc++.h>
using namespace std;

string s;

int get_tail_digit() {
    for (int i = (int) s.size() - 1; i >= 0; i--) {
        if (s[i] >= '0' && s[i] <= '9') {
            return s[i] - '0';
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    if (s.substr(0, 3) != "MDA") {
        cout << "1 1 1 1 1\n";
        return 0;
    }

    int tail = get_tail_digit();
    int ans[5] = {0, 0, 0, 0, 0};

    if (tail == 1 || tail == 9) ans[0] = 1;
    if (tail == 2 || tail == 8) ans[1] = 1;
    if (tail == 3 || tail == 7) ans[2] = 1;
    if (tail == 4 || tail == 6) ans[3] = 1;
    if (tail == 5 || tail == 0) ans[4] = 1;

    for (int i = 0; i < 5; i++) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
