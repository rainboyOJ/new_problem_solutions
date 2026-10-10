#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    if (n == 0) {
        cout << 0 << "\n";
        return;
    }
    
    map<int, int> dp;
    int max_len = 0;
    
    for (int i = 0; i < n; i++) {
        dp[a[i]] = dp[a[i] - 1] + 1;
        if (dp[a[i]] > max_len) {
            max_len = dp[a[i]];
        }
    }
    
    cout << max_len << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}