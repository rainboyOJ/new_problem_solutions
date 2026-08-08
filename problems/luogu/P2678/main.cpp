#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;

long long L;
int N, M;
long long stone[MAXN];

bool check(long long d) {
    long long removed = 0;
    long long last = 0;

    for (int i = 1; i <= N + 1; i++) {
        if (stone[i] - last < d) {
            removed++;
        } else {
            last = stone[i];
        }
        if (removed > M) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> N >> M;
    for (int i = 1; i <= N; i++) cin >> stone[i];
    sort(stone + 1, stone + N + 1);
    stone[N + 1] = L;

    long long left = 0, right = L, ans = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
