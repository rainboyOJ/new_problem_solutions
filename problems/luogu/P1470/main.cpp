#include <bits/stdc++.h>
using namespace std;

const int MAXS = 200005;

vector<string> prims;
string s;
bool ok[MAXS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string t;
    while (cin >> t) {
        if (t == ".") {
            break;
        }
        prims.push_back(t);
    }

    string part;
    while (cin >> part) {
        s += part;
    }

    int n = (int) s.size();
    ok[0] = true;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            continue;
        }
        ans = max(ans, i);
        for (string p : prims) {
            int len = (int) p.size();
            if (i + len > n) {
                continue;
            }
            bool same = true;
            for (int j = 0; j < len; j++) {
                if (s[i + j] != p[j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                ok[i + len] = true;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        if (ok[i]) {
            ans = max(ans, i);
        }
    }

    cout << ans << '\n';
    return 0;
}
