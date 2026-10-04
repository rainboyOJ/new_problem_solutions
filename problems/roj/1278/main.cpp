/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:49
 * update_at: 2026-10-04 23:49
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXM = 505; // 书的数量最多 500 本，下标从 1 开始

ll m, k;
ll pages[MAXM];  // pages[i] 表示第 i 本书的页数
ll pre[MAXM];    // pre[i] = 前 i 本书的总页数

ll start_id[MAXM]; // start_id[person] = 第 person 个人抄写的起始书号
ll end_id[MAXM];   // end_id[person]   = 第 person 个人抄写的终止书号

// 判定函数：每人上限 limit 页时，从头「能装就装、装不下才换人」，
// 返回抄完整本书稿最少需要的人数。页数都是正数，所以这样贪心得到的段数最少。
ll people_needed(ll limit) {
    ll used = 0; // 当前这个人已抄的页数
    ll cnt = 0;  // 已经用掉的人数
    for (ll i = 1; i <= m; i++) {
        used += pages[i];
        if (used > limit) { // 第 i 本装不下：上一个人到此为止，它另起一段
            cnt++;
            used = pages[i];
        }
    }
    if (used > 0) cnt++; // 末尾没装满的那一段也得算一个人
    return cnt;
}

// 二分最短复制时间 C*：limit 越大所需人数越少，人数关于 limit 单调不增，
// 所以「最少人数不超过 k」一旦成立就不会再变回去，可以二分出最小的可行 limit。
ll shortest_limit() {
    ll lo = pages[1]; // 下界：至少要放得下最厚的那本书
    for (ll i = 1; i <= m; i++) {
        if (pages[i] > lo) lo = pages[i];
    }
    ll avg = (pre[m] + k - 1) / k; // 也不能低于人均页数（向上取整）
    if (avg > lo) lo = avg;
    ll hi = pre[m]; // 上界：一个人全抄完，必然可行
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (people_needed(mid) <= k) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

// 倒序贪心重建方案：让第 k、k-1、… 个人依次能吞多少吞多少，
// 「前面的人少抄」等价于「后面的人多抄」，于是第 1 个人剩下的最少。
// 注意这里是 1 下标扫描：收尾时第 i 本归新的（更靠前的）那个人，
// 前面只剩 1..i-1 共 i-1 本书，要够 person-1 个人每人一本。
void build_plan(ll limit) {
    ll person = k;
    ll used = 0;
    ll right_end = m; // 当前这个人已确定区间的右端书号
    for (ll i = m; i >= 1; i--) {
        // 收尾条件缺一不可：再吞第 i 本会超过 limit，
        // 或者前面剩的 i-1 本书不够 person-1 个人每人一本（即 i < person）。
        if (used + pages[i] > limit || i < person) {
            start_id[person] = i + 1;
            end_id[person] = right_end;
            person--;
            used = 0;
            right_end = i;
        }
        used += pages[i];
    }
    start_id[1] = 1;
    end_id[1] = right_end;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> k;
    if (m == 0 || k == 0) return 0; // 空书稿或没有人抄，不输出任何行

    for (ll i = 1; i <= m; i++) {
        cin >> pages[i];
        pre[i] = pre[i - 1] + pages[i];
    }

    build_plan(shortest_limit());

    for (ll person = 1; person <= k; person++) {
        cout << start_id[person] << ' ' << end_id[person] << '\n';
    }

    return 0;
}
