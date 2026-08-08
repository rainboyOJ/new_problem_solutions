#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> cur;
    for (int i = 1; i <= n; i++) {
        cur.push_back(i);
    }

    while (!cur.empty()) {
        vector<int> take;
        vector<int> nxt;
        for (int i = 0; i < (int) cur.size(); ) {
            int j = i;
            while (j < (int) cur.size() && a[cur[j]] == a[cur[i]]) {
                j++;
            }
            take.push_back(cur[i]);
            for (int k = i + 1; k < j; k++) {
                nxt.push_back(cur[k]);
            }
            i = j;
        }

        for (int i = 0; i < (int) take.size(); i++) {
            if (i) cout << ' ';
            cout << take[i];
        }
        cout << '\n';
        cur.swap(nxt);
    }

    return 0;
}
