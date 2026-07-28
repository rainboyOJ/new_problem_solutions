#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    double findMedianSortedArrays(vector<int>& a, vector<int>& b) {
        if (a.size() > b.size()) swap(a, b);
        int m = a.size(), n = b.size(), lo = 0, hi = m;
        while (lo <= hi) {
            int i = (lo+hi)/2, j = (m+n+1)/2 - i;
            int al = (i==0 ? INT_MIN : a[i-1]), ar = (i==m ? INT_MAX : a[i]);
            int bl = (j==0 ? INT_MIN : b[j-1]), br = (j==n ? INT_MAX : b[j]);
            if (al <= br && bl <= ar) {
                if ((m+n)%2) return max(al, bl);
                return (max(al,bl) + min(ar,br)) / 2.0;
            }
            if (al > br) hi = i-1; else lo = i+1;
        }
        return 0;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin >> m >> n;
    vector<int> a(m), b(n);
    for (int& x : a) cin >> x; for (int& x : b) cin >> x;
    cout << fixed << setprecision(5) << Solution().findMedianSortedArrays(a,b) << '\n';
    return 0;
}
