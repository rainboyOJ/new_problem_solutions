/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
int wish[50005][2];   // 编号 i+1 最希望相邻的两人（0 基）

// 愿望图是单一环时返回环上顺序，否则 -1
vector<int> walk_cycle() {
    int total = n;
    vector<int> order;
    order.push_back(0);
    int prev = -1, cur = 0;
    for (int step = 0; step < total; step++) {
        int a = wish[cur][0], b = wish[cur][1];
        int nxt = (a == prev) ? b : a;
        if (nxt == 0) {
            if ((int)order.size() == total) return order;
            return vector<int>();
        }
        order.push_back(nxt);
        prev = cur;
        cur = nxt;
    }
    return vector<int>();
}

int min_cost() {
    int total = n;
    // 愿望必须互相成立
    for (int i = 0; i < total; i++) {
        int a = wish[i][0], b = wish[i][1];
        bool ok_a = (wish[a][0] == i || wish[a][1] == i);
        bool ok_b = (wish[b][0] == i || wish[b][1] == i);
        if (!ok_a || !ok_b) return -1;
    }
    vector<int> order = walk_cycle();
    if (order.empty()) return -1;

    vector<int> hit_fwd(total, 0), hit_rev(total, 0);
    for (int seat = 0; seat < total; seat++) {
        int person = order[seat];
        hit_fwd[((person - seat) % total + total) % total]++;
        hit_rev[((person + seat) % total + total) % total]++;
    }
    int keep = 0;
    for (int i = 0; i < total; i++) keep = max(keep, hit_fwd[i]);
    for (int i = 0; i < total; i++) keep = max(keep, hit_rev[i]);
    return total - keep;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> wish[i][0] >> wish[i][1];
        wish[i][0]--; wish[i][1]--;
    }
    cout << min_cost() << "\n";
    return 0;
}
