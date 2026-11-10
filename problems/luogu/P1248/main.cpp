/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:50
 * update_at: 2026-11-09 20:53
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 双机流水作业调度（Johnson 法则）：先按规则排序，再顺序模拟两台机器。
struct Job {
    int id; // 原始编号（1 开始），用于输出加工顺序
    ll a;   // 在 A 车间加工时间
    ll b;   // 在 B 车间加工时间
};

const int maxn = 1005;
Job job[maxn];

// Johnson 比较器：a<=b 的前段作业在前（按 a 升序），a>b 的后段作业在后（按 b 降序）。
bool johnson_cmp(const Job &x, const Job &y) {
    bool x_front = x.a <= x.b; // x 是否属于前段
    bool y_front = y.a <= y.b; // y 是否属于前段
    if (x_front != y_front) return x_front > y_front; // 前段整体排在后段之前
    if (x_front) return x.a < y.a;                    // 前段：a 升序
    return x.b > y.b;                                 // 后段：b 降序
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> job[i].a;
    for (int i = 1; i <= n; ++i) {
        cin >> job[i].b;
        job[i].id = i;
    }

    sort(job + 1, job + n + 1, johnson_cmp);

    // 顺序模拟：finish_a 是 A 完成当前作业的时刻，finish_b 是 B 完成当前作业的时刻。
    ll finish_a = 0;
    ll finish_b = 0;
    for (int i = 1; i <= n; ++i) {
        finish_a += job[i].a;
        finish_b = max(finish_b, finish_a) + job[i].b;
    }

    cout << finish_b << '\n';
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << job[i].id;
    }
    cout << '\n';

    return 0;
}
