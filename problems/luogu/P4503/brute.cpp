#include <bits/stdc++.h>
using namespace std;

int n, L, S;
string str[205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L >> S;
    for (int i = 1; i <= n; i++) {
        cin >> str[i];
    }

    // brute.cpp：直接枚举两两字符串，统计恰好只有一位不同的对数。
    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int diff = 0;
            for (int k = 0; k < L; k++) {
                if (str[i][k] != str[j][k]) {
                    diff++;
                }
            }
            if (diff == 1) {
                answer++;
            }
        }
    }

    cout << answer << '\n';

    return 0;
}
