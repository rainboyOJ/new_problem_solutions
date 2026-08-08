#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接用集合存所有合法姓名，
// 再用 map 记录某个姓名是否已经被点过。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n;

    set<string> names;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        names.insert(s);
    }

    map<string, int> vis;

    cin >> m;
    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;

        if (names.find(s) == names.end()) {
            cout << "WRONG\n";
        } else if (vis[s] == 0) {
            vis[s] = 1;
            cout << "OK\n";
        } else {
            cout << "REPEAT\n";
        }
    }

    return 0;
}
