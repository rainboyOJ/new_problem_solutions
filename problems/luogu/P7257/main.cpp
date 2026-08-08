#include <bits/stdc++.h>
using namespace std;

int reverse_num(int x) {
    int y = 0;
    while (x > 0) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    cout << max(reverse_num(a), reverse_num(b)) << '\n';
    return 0;
}
