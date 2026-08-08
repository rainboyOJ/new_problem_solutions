#include <bits/stdc++.h>
using namespace std;

int n;
string u;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> u;

    // brute.cpp：枚举插入位置，删除这一位后检查剩下的串能否分成完全相同的两半。
    // 复杂度较高，只适合小数据验证。
    set<string> answer;

    for (int i = 0; i < n; i++) {
        string v = u.substr(0, i) + u.substr(i + 1);
        if ((int)v.size() % 2 != 0) {
            continue;
        }
        int len = (int)v.size() / 2;
        if (len == 0) {
            continue;
        }
        if (v.substr(0, len) == v.substr(len, len)) {
            answer.insert(v.substr(0, len));
        }
    }

    if (answer.empty()) {
        cout << "NOT POSSIBLE\n";
    }
    else if ((int)answer.size() > 1) {
        cout << "NOT UNIQUE\n";
    }
    else {
        cout << *answer.begin() << '\n';
    }

    return 0;
}
