#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1000;

int n;
int vis[MAXV + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        vis[x] = 1;
    }

    int cnt = 0;
    for (int i = 1; i <= MAXV; i++) {
        cnt += vis[i];
    }

    cout << cnt << '\n';
    bool first = true;
    for (int i = 1; i <= MAXV; i++) {
        if (vis[i]) {
            if (!first) {
                cout << ' ';
            }
            cout << i;
            first = false;
        }
    }
    cout << '\n';

    return 0;
}
