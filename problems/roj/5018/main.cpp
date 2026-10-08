/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 20:00
 * update_at: 2026-10-08 20:00
 */

#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 5005; // 题面 N 上限

struct Job {
    ll deadline; // 截止时刻 d_i = M - C_i：做完第 i 项工作时手上钱最少只能是 M - d_i
    ll cost;     // 净支出 p_i = D_i - C_i > 0：做完这项工作上钱恰好少这么多
};

Job job[MAXN];   // job[1..n]，按 deadline 升序排好后的工作
ll money;        // 初始钱数 M

// 按截止时刻升序（即 C_i 降序）排；并列时按净支出升序，平局顺序不影响答案
bool cmp_job(const Job& a, const Job& b) {
    if (a.deadline != b.deadline) return a.deadline < b.deadline;
    return a.cost < b.cost;
}

// 反悔贪心（Moore-Hodgson 解单机 1||ΣU_j）：先把工作接进来，一旦已接工作的总净支出
// 超过当前截止时刻，就退掉已接工作中净支出最大的那一项（计数不变、回钱最多）。
void solve() {
    ll n;
    if (!(cin >> n >> money)) return;

    for (ll i = 1; i <= n; i++) cin >> job[i].cost; // 先存 D_i，稍后减去 C_i 得净支出
    for (ll i = 1; i <= n; i++) {
        ll c;
        cin >> c;
        job[i].cost -= c;             // p_i = D_i - C_i
        job[i].deadline = money - c;  // d_i = M - C_i
    }

    sort(job + 1, job + n + 1, cmp_job);

    priority_queue<ll> chosen; // 已接工作的净支出，大根堆方便反悔丢最大者
    ll used = 0;               // 已接工作的总净支出
    for (ll i = 1; i <= n; i++) {
        used += job[i].cost;
        chosen.push(job[i].cost);
        if (used > job[i].deadline) { // 当前截止时刻已装不下，反悔丢掉最大的一项
            used -= chosen.top();
            chosen.pop();
        }
    }

    cout << chosen.size() << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
