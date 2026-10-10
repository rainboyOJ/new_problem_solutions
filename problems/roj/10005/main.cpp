/*
 * Author: 2026-10-09 22:30
 */
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll a[MAXN];
int n;

bool cmp(ll x, ll y) {
    return x > y;
}

void solve() {
    if (!(cin >> n)) return;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    sort(a, a + n, cmp);
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] >= i) {
            ans = i + 1;
        } else {
            break;
        }
    }
    
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
