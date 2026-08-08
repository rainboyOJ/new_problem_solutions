#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXS = 600;

int n, w;
int a[MAXN];
int cnt[MAXS + 5];

int get_line(int need) {
    int sum = 0;
    for (int score = MAXS; score >= 0; score--) {
        sum += cnt[score];
        if (sum >= need) {
            return score;
        }
    }
    return 0;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        int need = i * w / 100;
        if (need < 1) {
            need = 1;
        }
        int line = get_line(need);
        if (i > 1) {
            cout << ' ';
        }
        cout << line;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
