#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temps) {
        int n = temps.size();
        vector<int> ans(n, 0);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temps[st.top()] < temps[i]) {
                ans[st.top()] = i - st.top(); st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n; vector<int> a(n); for (int& x : a) cin >> x;
    for (int x : Solution().dailyTemperatures(a)) cout << x << ' ';
    return 0;
}
