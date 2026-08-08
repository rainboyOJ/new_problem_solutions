#include <bits/stdc++.h>
using namespace std;

vector<string> split_tokens(const string &s) {
    vector<string> tokens;
    int n = (int)s.size();
    int i = 0;
    while (i < n) {
        while (i < n && s[i] == ' ') {
            ++i;
        }
        if (i >= n) {
            break;
        }
        int j = i;
        while (j < n && s[j] != ' ') {
            ++j;
        }
        tokens.push_back(s.substr(i, j - i));
        i = j;
    }
    return tokens;
}

int evaluate_once(const vector<string> &tokens, const vector<int> &value, int flip_id) {
    vector<int> st;
    st.reserve(tokens.size());

    for (const string &token : tokens) {
        if (token[0] == 'x') {
            int id = stoi(token.substr(1));
            st.push_back(value[id] ^ (id == flip_id));
        } else if (token == "!") {
            int x = st.back();
            st.pop_back();
            st.push_back(x ^ 1);
        } else {
            int right = st.back();
            st.pop_back();
            int left = st.back();
            st.pop_back();
            if (token == "&") {
                st.push_back(left & right);
            } else {
                st.push_back(left | right);
            }
        }
    }
    return st.back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string expr;
    getline(cin, expr);
    vector<string> tokens = split_tokens(expr);

    int n;
    cin >> n;
    vector<int> value(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> value[i];
    }

    int q;
    cin >> q;
    while (q--) {
        int x;
        cin >> x;
        cout << evaluate_once(tokens, value, x) << '\n';
    }
    return 0;
}
