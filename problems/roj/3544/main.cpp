/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:35
 * update_at: 2026-10-06 13:35
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // 排序后去重：先排序，再用 unique 把相邻重复挤到末尾
    sort(a + 1, a + n + 1);
    int m = unique(a + 1, a + n + 1) - (a + 1); // 互异元素个数

    cout << m << "\n";
    for (int i = 1; i <= m; ++i) {
        if (i > 1) cout << " ";
        cout << a[i];
    }
    cout << "\n";
    return 0;
}
