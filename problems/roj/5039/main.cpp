/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:53
 * update_at: 2026-10-08 23:06
 */
#include <iostream>

using namespace std;

typedef long long ll;

// 题意：N 个人围成一圈，从第 1 个人开始报数（第 1 个人报 1），数到 M 的人出圈，
//       再由出圈者的下一个人从 1 重新报数；按出圈次序输出 N 个人的编号。
// 数据范围（题面【提示】）：2 <= N, M <= 1000，单组输入。

const int MAXN = 1005;  // 题面 N <= 1000，留几个空位

ll n, m;                // 人数、报数步长
ll people[MAXN];        // people[0 .. left-1] 依次存放尚未出圈者的编号，删除靠左移覆盖

// 模拟出圈过程：每轮从下标 idx 处前进 m-1 步（环形取模），该位置的人出圈。
// 出圈者被其后面的人左移覆盖，因此下一轮起点下标仍是同一个 idx，不需要额外加一。
void solve() {
    ll left = n;                        // 圈中剩余人数
    for (ll i = 0; i < left; i++) people[i] = i + 1;

    ll idx = 0;                         // 本轮报数起点的下标，初始从第 1 个人开始
    bool first = true;                  // 是否尚未输出任何编号，用来控制分隔符
    while (left > 0) {
        idx = (idx + m - 1) % left;     // 前进 m-1 步即"数到第 m 个"，越界则绕回起点
        if (!first) cout << " ";        // 编号之间恰一个空格，行首行末都不留空格
        cout << people[idx];
        first = false;

        for (ll i = idx; i + 1 < left; i++) people[i] = people[i + 1]; // 左移覆盖，等价于删除
        left--;
    }
    cout << "\n";                       // 题面要求一行，末尾补单个换行
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;     // 无输入时直接退出

    solve();

    return 0;
}
