#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);

    int ans = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (s[i] != ' ') {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
