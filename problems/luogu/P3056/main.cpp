#include <bits/stdc++.h>
using namespace std;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    int ans = 0;
    int balance = 0;

    for (char c : s) {
        if (c == '(') {
            balance++;
        } else {
            balance--;
        }

        if (balance < 0) {
            ans++;
            balance = 1;
        }
    }

    ans += balance / 2;
    cout << ans << '\n';
    return 0;
}
