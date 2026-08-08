#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

struct HashValue {
    unsigned long long h1, h2;
};

int n;
HashValue value_hash[MAXN];
string s;

bool cmp_hash(const HashValue &a, const HashValue &b) {
    if (a.h1 != b.h1) {
        return a.h1 < b.h1;
    }
    return a.h2 < b.h2;
}

bool same_hash(const HashValue &a, const HashValue &b) {
    return a.h1 == b.h1 && a.h2 == b.h2;
}

HashValue calc_hash(const string &text) {
    const unsigned long long base1 = 131;
    const unsigned long long base2 = 13331;

    HashValue res;
    res.h1 = 0;
    res.h2 = 0;
    for (int i = 0; i < (int)text.size(); i++) {
        unsigned long long x = (unsigned char)text[i] + 1;
        res.h1 = res.h1 * base1 + x;
        res.h2 = res.h2 * base2 + x;
    }
    return res;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        value_hash[i] = calc_hash(s);
    }

    sort(value_hash + 1, value_hash + n + 1, cmp_hash);

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1 || !same_hash(value_hash[i], value_hash[i - 1])) {
            answer++;
        }
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
