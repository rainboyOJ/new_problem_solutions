#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, a, d;
        cin >> n >> a >> d;

        set<int> s;
        for (int i = 0; i < n; i++) {
            s.insert(a + i * d);
        }

        bool changed = true;
        while (changed) {
            changed = false;
            vector<int> cur(s.begin(), s.end());
            int m = (int) cur.size();
            for (int i = 0; i < m; i++) {
                for (int j = i + 1; j < m; j++) {
                    int sum = cur[i] + cur[j];
                    if (sum & 1) continue;
                    int mid = sum / 2;
                    if (s.count(mid)) continue;
                    s.insert(mid);
                    changed = true;
                }
            }
        }

        cout << (int) s.size() - n << '\n';
    }

    return 0;
}
