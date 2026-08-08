#include <bits/stdc++.h>
using namespace std;

const int mod = 10000;

string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    long long ans = 0;
    long long cur = 0;
    long long num = 0;
    char last_op = '+';

    for (int i = 0; i <= (int) s.size(); i++) {
        if (i < (int) s.size() && isdigit(s[i])) {
            num = (num * 10 + (s[i] - '0')) % mod;
        } else {
            if (last_op == '*') {
                cur = cur * num % mod;
            } else {
                ans = (ans + cur) % mod;
                cur = num;
            }

            if (i < (int) s.size()) {
                last_op = s[i];
            }
            num = 0;
        }
    }

    ans = (ans + cur) % mod;
    cout << ans % mod << '\n';
    return 0;
}
