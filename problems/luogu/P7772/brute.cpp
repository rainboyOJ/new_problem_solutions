#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, I;
    cin >> A >> I;

    long long N = 1;
    while ((N + A - 1) / A < I) {
        N++;
    }

    cout << N << '\n';
    return 0;
}
