#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    long long ans = 0;
    int day_value = 1;
    int used = 0;
    for (int day = 1; day <= k; day++) {
        ans += day_value;
        used++;
        if (used == day_value) {
            day_value++;
            used = 0;
        }
    }

    cout << ans << '\n';
    return 0;
}
