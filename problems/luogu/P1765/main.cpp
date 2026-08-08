#include <bits/stdc++.h>
using namespace std;

string s;
int cost[256];   // 每个字符需要按多少次

void init_cost() {
    memset(cost, 0, sizeof(cost));
    string groups[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (int) groups[i].size(); j++) {
            cost[(int) groups[i][j]] = j + 1;
        }
    }
    cost[(int) ' '] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);
    init_cost();

    int ans = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        ans += cost[(int) s[i]];
    }

    cout << ans << '\n';
    return 0;
}
