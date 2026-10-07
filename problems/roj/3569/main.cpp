/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:15
 * update_at: 2026-10-06 14:15
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

struct Person {
    int k; // 报名号
    int s; // 成绩
} a[MAXN];

int n, m;

// 成绩降序，成绩相同则报名号升序
bool cmp(const Person &x, const Person &y) {
    if (x.s != y.s) return x.s > y.s;
    return x.k < y.k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].k >> a[i].s;
    }

    sort(a + 1, a + n + 1, cmp);

    int r = m * 3 / 2; // 向下取整后的排名位置（1-indexed）
    int line = a[r].s; // 面试分数线

    // 统计不低于分数线的实际人数
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i].s >= line) ++cnt;
    }

    cout << line << " " << cnt << "\n";
    for (int i = 1; i <= n; ++i) {
        if (a[i].s >= line) {
            cout << a[i].k << " " << a[i].s << "\n";
        }
    }

    return 0;
}
