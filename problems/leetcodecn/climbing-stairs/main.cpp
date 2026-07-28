#include <bits/stdc++.h>
using namespace std;
class Solution { public:
    int climbStairs(int n) {
        int a = 1, b = 1;
        for (int i = 2; i <= n; i++) { int c = a + b; a = b; b = c; }
        return b;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; cout << Solution().climbStairs(n) << '\n';
    return 0;
}
