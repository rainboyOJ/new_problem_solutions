/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 16:30
 * update_at: 2026-09-27 16:31
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 50005;

int n;
int ans[MAXN]; // ans[i] 表示第 i 头牛被分到的牛棚编号

// 一头牛：挤奶区间 [l, r]，id 是输入顺序
struct Cow {
    int l;
    int r;
    int id;
};
Cow cow[MAXN];

// 按挤奶开始时间从小到大排序；开始时间相同则结束早的排前面
bool cmp_cow(const Cow &a, const Cow &b) {
    if (a.l != b.l) return a.l < b.l;
    return a.r < b.r;
}

// 牛棚：id 是编号，cow 是这个棚当前最后一头牛的结束时间
struct Node {
    int id;
    int cow;
    // priority_queue 默认是大根堆，重载 < 让结束时间早的排在堆顶
    bool operator<(const Node &b) const {
        return cow > b.cow;
    }
};
priority_queue<Node> pq; // 小根堆，堆顶是“最快空出来”的牛棚

void read_data() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cow[i].l >> cow[i].r;
        cow[i].id = i;
    }
}

void solve() {
    sort(cow + 1, cow + 1 + n, cmp_cow);

    int cnt = 0; // 当前已经启用的牛棚数，也就是最少牛棚数
    for (int i = 1; i <= n; i++) {
        int l = cow[i].l;
        int r = cow[i].r;
        int id = cow[i].id;

        // 区间端点也算使用时间，所以必须堆顶的结束时间严格小于 l 才能复用
        if (!pq.empty() && pq.top().cow < l) {
            Node t = pq.top();
            pq.pop();
            ans[id] = t.id; // 复用这个最早空出来的棚
            t.cow = r;      // 它的占用时间更新为当前这头牛
            pq.push(t);
        } else {
            // 所有已开的棚都还没空，只能新开一个
            cnt++;
            Node t;
            t.id = cnt;
            t.cow = r;
            ans[id] = cnt;
            pq.push(t);
        }
    }

    cout << cnt << "\n";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    read_data();
    solve();

    return 0;
}
