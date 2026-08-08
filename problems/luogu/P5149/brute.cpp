#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 2005;

int n;
int a[MAXN];
map<string, int> pos;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        pos[name] = i;
    }

    for (int i = 1; i <= n; i++) {
        string name;
        cin >> name;
        a[i] = pos[name];
    }

    ll answer = 0;

    // brute.cpp：转成原序列下标后，直接枚举所有下标对统计逆序对。
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
