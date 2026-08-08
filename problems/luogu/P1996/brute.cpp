#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        a.push_back(i);
    }

    int pos = 0;
    while (!a.empty()) {
        pos = (pos + m - 1) % a.size();
        cout << a[pos];
        a.erase(a.begin() + pos);
        if (!a.empty()) {
            cout << ' ';
        }
    }

    cout << '\n';
    return 0;
}
