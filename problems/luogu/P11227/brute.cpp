// brute.cpp：小数据暴力解，枚举完整牌库中的 52 种牌，检查原牌中缺多少种。
#include <bits/stdc++.h>
using namespace std;

bool have[256][256];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string card;
        cin >> card;
        have[(int)card[0]][(int)card[1]] = true;
    }

    string suits = "DCHS";
    string ranks = "A23456789TJQK";
    int missing = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            if (!have[(int)suits[i]][(int)ranks[j]]) {
                missing++;
            }
        }
    }

    cout << missing << '\n';
    return 0;
}
