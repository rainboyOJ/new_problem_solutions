/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:02
 * update_at: 2026-10-06 13:02
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int DAYS = 7; // 周一到周日共 7 天
const ll LIMIT = 8; // 恰好 8 小时仍算高兴，严格超过 8 小时才不高兴

ll a[DAYS + 1]; // a[i] 表示第 i 天在校上课的小时数
ll b[DAYS + 1]; // b[i] 表示第 i 天妈妈安排的课时数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= DAYS; i++) {
        cin >> a[i] >> b[i];
    }

    // 求一天的最大总课时；平局时保留最早出现的那天，满足“输出时间最靠前的一天”。
    ll max_load = -1;
    int worst_day = 0;
    for (int i = 1; i <= DAYS; i++) {
        ll load = a[i] + b[i];
        if (load > max_load) {
            max_load = load;
            worst_day = i;
        }
    }

    if (max_load > LIMIT) {
        cout << worst_day << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}
