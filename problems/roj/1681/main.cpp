/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:00
 * update_at: 2026-10-06 02:00
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const ll MAXN = 100005;

ll a[MAXN];        // 原数组，按输入顺序保存
ll sorted_a[MAXN]; // a 的副本，排序去重用
ll vals[MAXN];     // 去重后的递增值表，vals[1] < vals[2] < ...
ll k;              // 不同值的个数

int main() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sorted_a[i] = a[i];
    }

    // 排序后相邻去重，得到递增值表
    sort(sorted_a + 1, sorted_a + n + 1);
    for (ll i = 1; i <= n; i++) {
        if (i == 1 || sorted_a[i] != sorted_a[i - 1]) {
            k++;
            vals[k] = sorted_a[i];
        }
    }

    // 每个原数在值表中第一次出现的位置（从 1 开始）就是它的编号
    for (ll i = 1; i <= n; i++) {
        ll pos = lower_bound(vals + 1, vals + k + 1, a[i]) - vals;
        if (i > 1) {
            cout << " ";
        }
        cout << pos;
    }
    cout << "\n";
    return 0;
}
