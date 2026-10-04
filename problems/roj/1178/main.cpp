/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:26
 * update_at: 2026-10-05 04:26
 */
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

// n < 20，开 25 足够。
const ll MAXN = 25;

// stu[i] = 第 i 个学生的 (名字, 成绩)
string stu_name[MAXN];
ll stu_score[MAXN];

ll n;
// order[i] = 按规则排好后第 i 名的原始下标（用下标排序避免搬动 string）。
ll order[MAXN];

// 比较规则：成绩降序；成绩相同则名字字典序升序。
bool cmp_by_score_name(ll i, ll j) {
    if (stu_score[i] != stu_score[j]) return stu_score[i] > stu_score[j];
    return stu_name[i] < stu_name[j];
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> stu_name[i] >> stu_score[i];
        order[i] = i;
    }
}

void solve() {
    // 用下标数组排序，避免交换 string。
    sort(order + 1, order + n + 1, cmp_by_score_name);
    for (ll k = 1; k <= n; k++) {
        ll i = order[k];
        cout << stu_name[i] << " " << stu_score[i];
        if (k != n) cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}