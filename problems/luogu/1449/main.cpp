#include <bits/stdc++.h>
using namespace std;

long long st[105]; // 计算后缀表达式时使用的栈
int top_idx;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    long long number = 0;
    bool reading_number = false;

    for (int i = 0; i < (int)s.size(); i++) {
        char ch = s[i];
        if ('0' <= ch && ch <= '9') {
            number = number * 10 + (ch - '0');
            reading_number = true;
        } else if (ch == '.') {
            if (reading_number) {
                st[++top_idx] = number;
                number = 0;
                reading_number = false;
            }
        } else if (ch == '@') {
            break;
        } else {
            long long b = st[top_idx--];
            long long a = st[top_idx--];
            if (ch == '+') {
                st[++top_idx] = a + b;
            } else if (ch == '-') {
                st[++top_idx] = a - b;
            } else if (ch == '*') {
                st[++top_idx] = a * b;
            } else {
                st[++top_idx] = a / b;
            }
        }
    }

    cout << st[top_idx] << '\n';
    return 0;
}
