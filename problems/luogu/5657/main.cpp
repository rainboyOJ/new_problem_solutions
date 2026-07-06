// main.cpp：用公式 gray = k ^ (k >> 1) 求第 k 个 n 位格雷码。
#include <bits/stdc++.h>
using namespace std;

int n;
unsigned long long k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    unsigned long long gray = k ^ (k >> 1);

    for (int bit = n - 1; bit >= 0; bit--) {
        cout << ((gray >> bit) & 1ULL);
    }
    cout << '\n';

    return 0;
}
