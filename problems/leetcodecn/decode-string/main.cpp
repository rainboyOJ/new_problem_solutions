#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string decodeString(string s) {
        stack<string> st; stack<int> nums;
        string cur; int num = 0;
        for (char ch : s) {
            if (isdigit(ch)) num = num*10 + (ch-'0');
            else if (ch == '[') { st.push(cur); nums.push(num); cur = ""; num = 0; }
            else if (ch == ']') {
                string tmp = cur; cur = st.top(); st.pop();
                int n = nums.top(); nums.pop();
                while (n--) cur += tmp;
            } else cur += ch;
        }
        return cur;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string s; cin >> s; cout << Solution().decodeString(s) << '\n';
    return 0;
}
