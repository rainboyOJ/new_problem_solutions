#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int r[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> r[i];
    }

    sort(r + 1, r + n + 1);

    int victim = 1;
    int attacker = 1;
    int killed = 0;

    // 给每个当前最弱的目标，找一个尽量弱但严格更强的攻击者。
    while (victim <= n && attacker <= n) {
        if (r[attacker] > r[victim]) {
            killed++;
            victim++;
            attacker++;
        } else {
            attacker++;
        }
    }

    cout << n - killed << '\n';

    return 0;
}
