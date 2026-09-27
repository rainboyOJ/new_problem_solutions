/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 16:30
 * update_at: 2026-09-27 16:31
 */
// brute.cpp：小数据暴力解，枚举每头牛放进哪个牛棚，找出最少牛棚数。
// 每层递归依次处理第 dep 头牛，选择它可以放进哪一个已经开了的棚，或者新开一个棚。
// 只适合 n 很小的情况（指数级），用来帮助理解题意并和 main.cpp 对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 15;

int n;

struct Cow {
    int l;
    int r;
    int id; // 输入顺序
};
Cow cow[MAXN];

int stall_end[MAXN]; // stall_end[k] 表示第 k 个牛棚当前最后一头牛的结束时间
int choose[MAXN];    // choose[id] 表示第 id 头牛当前方案里去的牛棚编号
int best_ans[MAXN];  // 最优方案里每头牛去的牛棚编号
int best_cnt;        // 最优方案用了几个棚

// 按开始时间从小到大排序，先处理开始早的牛
bool cmp_cow(const Cow &a, const Cow &b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}

// dep：当前处理到第几头牛；used：当前已经开了几个棚
void dfs(int dep, int used) {
    // 已经不可能比当前最优解更好了，剪枝
    if (used >= best_cnt) return;

    if (dep == n + 1) {
        // 走到这里说明所有牛都安排好了，更新最优解
        best_cnt = used;
        for (int i = 1; i <= n; i++) {
            best_ans[i] = choose[i];
        }
        return;
    }

    // 尝试放进已经开好的某个棚（端点也算占用，要严格小于才开始）
    for (int k = 1; k <= used; k++) {
        if (stall_end[k] < cow[dep].l) {
            int old = stall_end[k];
            stall_end[k] = cow[dep].r;
            choose[cow[dep].id] = k;
            dfs(dep + 1, used);
            stall_end[k] = old; // 恢复现场
        }
    }

    // 或者为这头牛新开一个棚
    stall_end[used + 1] = cow[dep].r;
    choose[cow[dep].id] = used + 1;
    dfs(dep + 1, used + 1);
    stall_end[used + 1] = 0; // 恢复现场
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].l >> cow[i].r;
        cow[i].id = i;
    }

    sort(cow + 1, cow + 1 + n, cmp_cow);

    best_cnt = n + 1; // 初始化为一个一定更差的上界
    dfs(1, 0);

    cout << best_cnt << "\n";
    for (int i = 1; i <= n; i++) {
        cout << best_ans[i] << "\n";
    }

    return 0;
}
