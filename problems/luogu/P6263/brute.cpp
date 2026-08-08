// brute.cpp：直接按键盘分组逐字符统计每根手指的按键次数。
#include <bits/stdc++.h>
using namespace std;

string s;
int ans[8];

int get_finger(char ch) {
    string group[8] = {
        "1QAZ",
        "2WSX",
        "3EDC",
        "4RFV5TGB",
        "6YHN7UJM",
        "8IK,",
        "9OL.",
        "0P;/-['=]"
    };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (int) group[i].size(); j++) {
            if (group[i][j] == ch) {
                return i;
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);
    memset(ans, 0, sizeof(ans));

    for (int i = 0; i < (int) s.size(); i++) {
        int id = get_finger(s[i]);
        if (id != -1) {
            ans[id]++;
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
