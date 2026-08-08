#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll answer = 0;

    // brute.cpp：直接枚举所有下标对，按逆序对定义统计。
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j]) {
                answer++;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
