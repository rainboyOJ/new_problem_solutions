#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        heights.push_back(0);
        stack<int> st;
        int ans = 0;
        for (int i = 0; i < (int)heights.size(); i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int h = heights[st.top()];
                st.pop();
                int l = st.empty() ? -1 : st.top();
                ans = max(ans, h * (i - l - 1));
            }
            st.push(i);
        }
        heights.pop_back();
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a)
        cin >> x;
    cout << Solution().largestRectangleArea(a) << '\n';
    return 0;
}
