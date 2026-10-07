/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:14
 * update_at: 2026-10-05 23:14
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 活动数不超过 1000

struct Activity {
    ll start;
    ll end;
};

Activity act[MAXN]; // act[i] 表示第 i 个活动的起止时间

// 按结束时间升序排序的比较函数
bool cmp_end(const Activity &a, const Activity &b) {
    return a.end < b.end;
}

int main() {
    ll n;
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> act[i].start >> act[i].end;
    }

    // 贪心：按结束时间升序排序后，尽量选择结束早且不冲突的活动
    sort(act + 1, act + n + 1, cmp_end);

    ll count = 0;
    ll last_end = -1; // 上一个已选活动的结束时间
    for (ll i = 1; i <= n; i++) {
        if (act[i].start >= last_end) {
            count++;
            last_end = act[i].end;
        }
    }

    cout << count << endl;
    return 0;
}
