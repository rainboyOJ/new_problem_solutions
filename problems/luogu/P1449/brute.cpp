// brute.cpp：小数据朴素解，直接按后缀表达式从左到右模拟。
#include <bits/stdc++.h>
using namespace std;

vector<long long> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int i = 0;
    while (i < (int)s.size() && s[i] != '@') {
        if ('0' <= s[i] && s[i] <= '9') {
            long long x = 0;
            while (i < (int)s.size() && '0' <= s[i] && s[i] <= '9') {
                x = x * 10 + (s[i] - '0');
                i++;
            }
            st.push_back(x);
            if (i < (int)s.size() && s[i] == '.') {
                i++;
            }
            continue;
        }

        long long b = st.back();
        st.pop_back();
        long long a = st.back();
        st.pop_back();
        if (s[i] == '+') {
            st.push_back(a + b);
        } else if (s[i] == '-') {
            st.push_back(a - b);
        } else if (s[i] == '*') {
            st.push_back(a * b);
        } else {
            st.push_back(a / b);
        }
        i++;
    }

    cout << st.back() << '\n';
    return 0;
}
