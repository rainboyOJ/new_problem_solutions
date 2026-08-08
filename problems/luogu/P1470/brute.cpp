#include <bits/stdc++.h>
using namespace std;

vector<string> prims;
string s;

bool can_split(int len) {
    vector<int> ok(len + 1, 0);
    ok[0] = 1;
    for (int i = 0; i < len; i++) {
        if (!ok[i]) {
            continue;
        }
        for (string p : prims) {
            int plen = (int) p.size();
            if (i + plen > len) {
                continue;
            }
            bool same = true;
            for (int j = 0; j < plen; j++) {
                if (s[i + j] != p[j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                ok[i + plen] = 1;
            }
        }
    }
    return ok[len];
}

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

    for (int len = (int) s.size(); len >= 0; len--) {
        if (can_split(len)) {
            cout << len << '\n';
            return 0;
        }
    }
    return 0;
}
