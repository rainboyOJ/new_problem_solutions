#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> st;
        st.push(-1);
        int ans = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(')
                st.push(i);
            else {
                st.pop();
                if (st.empty())
                    st.push(i);
                else
                    ans = max(ans, i - st.top());
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    cout << Solution().longestValidParentheses(s) << '\n';
    return 0;
}
