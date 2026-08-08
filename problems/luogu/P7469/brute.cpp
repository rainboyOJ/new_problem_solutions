#include <bits/stdc++.h>
using namespace std;

int n;
string s, t;

// 检查 need 是否能作为 s 的子序列。
bool is_subsequence(const string &need) {
    int p = 0;
    for (int i = 0; i < (int)s.size() && p < (int)need.size(); i++) {
        if (s[i] == need[p]) {
            p++;
        }
    }
    return p == (int)need.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;

    // brute.cpp：枚举 Bob 保留的所有子串，再判断它是否能由 Alice 作为子序列留下。
    // 复杂度较高，只适合小数据验证和对拍。
    set<string> answer;
    for (int l = 0; l < n; l++) {
        string cur = "";
        for (int r = l; r < n; r++) {
            cur.push_back(t[r]);
            if (is_subsequence(cur)) {
                answer.insert(cur);
            }
        }
    }

    cout << answer.size() << '\n';

    return 0;
}
