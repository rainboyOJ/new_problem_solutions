#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
string a[MAXN]; // 每个正整数按字符串保存，避免拼接后溢出

bool cmp_string(const string &x, const string &y) {
    return x + y > y + x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1, cmp_string);

    for (int i = 1; i <= n; i++) {
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
