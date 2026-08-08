#include <bits/stdc++.h>
using namespace std;

string s;

bool ok(const string& t) {
    int balance = 0;
    for (char c : t) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return balance == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int n = s.size();
    int ans = n;
    for (int mask = 0; mask < (1 << n); mask++) {
        string t = s;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                cnt++;
                t[i] = (t[i] == '(' ? ')' : '(');
            }
        }
        if (ok(t)) ans = min(ans, cnt);
    }

    cout << ans << '\n';
    return 0;
}
