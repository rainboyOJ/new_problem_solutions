/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:49
 * update_at: 2026-10-01 22:49
 */
// main.cpp：满分做法，排序后用双指针贪心：给每个最弱目标找最弱的能击杀它的攻击者。
// 核心思路：排序后，如果当前攻击者能杀当前目标就杀，否则攻击者后移。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;
int r[MAXN]; // 每只怪兽的攻击力/防御力（≤ 10^5，int 足够）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> r[i];
    }

    // 按攻击力从小到大排序。
    sort(r + 1, r + n + 1);

    ll victim = 1;   // 当前最弱的目标
    ll attacker = 1; // 当前攻击者
    ll killed = 0;

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
