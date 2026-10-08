#include <iostream>
#include <vector>

using namespace std;

bool check(long long x, int n, long long b, const vector<int>& a) {
    long long need = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] < x) {
            need += x - a[i];
            if (need > x) return false;
        }
    }
    return need <= b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    long long b;
    if (!(cin >> n >> b)) return 0;
    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    
    long long lo = 0, hi = (sum + b) / n + 1;
    long long ans = 0;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (check(mid, n, b, a)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    
    cout << ans << "\n";
    return 0;
}
