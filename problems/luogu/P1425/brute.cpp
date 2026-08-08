#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int start = a * 60 + b;
    int end = c * 60 + d;
    int diff = end - start;

    cout << diff / 60 << ' ' << diff % 60 << '\n';
    return 0;
}
