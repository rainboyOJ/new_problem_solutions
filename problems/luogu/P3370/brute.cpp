#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接用 set<string> 去重，作为小数据对拍基准。

int n;
string s;
set<string> all_strings;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        all_strings.insert(s);
    }
    cout << (int)all_strings.size() << '\n';

    return 0;
}
