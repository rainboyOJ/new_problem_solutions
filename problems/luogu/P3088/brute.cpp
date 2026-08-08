#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

struct Cow {
    int x, h;
};

int n, d;
Cow cow[MAXN];

bool cmp_by_x(const Cow &a, const Cow &b) {
    return a.x < b.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].x >> cow[i].h;
    }

    sort(cow + 1, cow + n + 1, cmp_by_x);

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        bool has_left = false;
        bool has_right = false;

        for (int j = i - 1; j >= 1; j--) {
            if (cow[i].x - cow[j].x > d) {
                break;
            }
            if ((long long)cow[j].h >= 2LL * cow[i].h) {
                has_left = true;
                break;
            }
        }

        for (int j = i + 1; j <= n; j++) {
            if (cow[j].x - cow[i].x > d) {
                break;
            }
            if ((long long)cow[j].h >= 2LL * cow[i].h) {
                has_right = true;
                break;
            }
        }

        if (has_left && has_right) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
