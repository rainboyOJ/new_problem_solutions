#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举长度并用 vector 序列精确计数，只适合小数据。

int n, k;
int a[105];

bool check_len(int len) {
    map<vector<int>, int> cnt;
    for (int i = 1; i + len - 1 <= n; i++) {
        vector<int> seq;
        for (int j = 0; j < len; j++) {
            seq.push_back(a[i + j]);
        }
        cnt[seq]++;
        if (cnt[seq] >= k) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int answer = 0;
    for (int len = 1; len <= n; len++) {
        if (check_len(len)) {
            answer = len;
        }
    }
    cout << answer << '\n';

    return 0;
}
