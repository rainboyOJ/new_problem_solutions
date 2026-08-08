#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int balance = 0;
    bool ok = true;
    for (int i = 0; i < (int)s.size() && s[i] != '@'; i++) {
        if (s[i] == '(') {
            balance++;
        } else if (s[i] == ')') {
            balance--;
            if (balance < 0) {
                ok = false;
            }
        }
    }

    if (balance != 0) {
        ok = false;
    }
    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}
