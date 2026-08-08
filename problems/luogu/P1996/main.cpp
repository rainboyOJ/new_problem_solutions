#include <bits/stdc++.h>
using namespace std;

int n, m;
queue<int> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    int cnt = 0;
    while (!q.empty()) {
        cnt++;
        int x = q.front();
        q.pop();

        if (cnt == m) {
            cout << x;
            if (!q.empty()) {
                cout << ' ';
            }
            cnt = 0;
        } else {
            q.push(x);
        }
    }

    cout << '\n';
    return 0;
}
