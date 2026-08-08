#include <bits/stdc++.h>
using namespace std;

const int maxx = 100000 + 5;

struct Person {
    int time;
    int country;
};

int n;
int t, k, x;
int ans;
int cnt[maxx];
queue<Person> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> t >> k;

        while (!q.empty() && q.front().time <= t - 86400) {
            int country = q.front().country;
            q.pop();
            cnt[country]--;
            if (cnt[country] == 0) {
                ans--;
            }
        }

        for (int j = 1; j <= k; j++) {
            cin >> x;
            q.push({t, x});
            if (cnt[x] == 0) {
                ans++;
            }
            cnt[x]++;
        }

        cout << ans << '\n';
    }

    return 0;
}
