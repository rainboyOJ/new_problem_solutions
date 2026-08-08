#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举 k 个不重叠子串并拼接，只适合很小的数据。

int n, m, need_k;
string a, b;
long long answer;

void dfs(int start_pos, int used, const string &built) {
    if ((int)built.size() > m) {
        return;
    }
    if (used == need_k) {
        if (built == b) {
            answer++;
        }
        return;
    }
    for (int l = start_pos; l <= n; l++) {
        string next = built;
        for (int r = l; r <= n; r++) {
            next.push_back(a[r - 1]);
            if ((int)next.size() > m) {
                break;
            }
            dfs(r + 1, used + 1, next);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> need_k;
    cin >> a >> b;
    dfs(1, 0, "");
    cout << answer % 1000000007 << '\n';

    return 0;
}
