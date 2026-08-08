#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;

    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }

    long long answer = 0;
    for (i64 x = x1; x <= x2; x++) {
        for (i64 y = y1; y <= y2; y++) {
            if (a * x + b * y + c == 0) {
                answer++;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
