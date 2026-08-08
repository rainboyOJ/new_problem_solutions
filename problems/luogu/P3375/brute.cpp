#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text_s, pat_s;
    cin >> text_s >> pat_s;

    int n = (int) text_s.size();
    int m = (int) pat_s.size();

    for (int i = 0; i + m <= n; i++) {
        bool same = true;
        for (int j = 0; j < m; j++) {
            if (text_s[i + j] != pat_s[j]) {
                same = false;
                break;
            }
        }
        if (same) {
            cout << i + 1 << '\n';
        }
    }

    for (int i = 0; i < m; i++) {
        int best = 0;
        for (int len = i; len >= 1; len--) {
            bool same = true;
            for (int j = 0; j < len; j++) {
                if (pat_s[j] != pat_s[i - len + 1 + j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                best = len;
                break;
            }
        }
        cout << best << (i + 1 == m ? '\n' : ' ');
    }

    return 0;
}
