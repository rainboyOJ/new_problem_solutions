/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:49
 * update_at: 2026-10-05 08:49
 */
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

typedef long long ll;

const int MAXN = 80005;
const ll MOD = 1000000;

ll n;
ll kind[MAXN];  // 第 i 个事件：0 表示宠物，1 表示领养者
ll value[MAXN]; // 第 i 个事件的特点值
ll idx[MAXN];   // value[i] 离散化后的下标（从 1 开始）

ll coord[MAXN]; // 所有出现过的特点值去重排序，下标从 1 开始
ll coord_cnt;

ll tree[MAXN]; // 树状数组，tree 维护每个离散化位置上待匹配对象的个数

int pool_type;  // 待匹配池当前的归属类型：0 宠物 / 1 领养者
ll pool_size;   // 待匹配池中的对象个数
ll answer;      // 所有匹配产生的不满意度总和（对 10^6 取模）

// 单点修改：离散化下标 p 的计数加上 delta。
void add(ll p, ll delta) {
    for (; p <= coord_cnt; p += p & -p) {
        tree[p] += delta;
    }
}

// 查询离散化下标 1..p 的前缀计数和。
ll prefix_sum(ll p) {
    ll sum = 0;
    for (; p > 0; p -= p & -p) {
        sum += tree[p];
    }
    return sum;
}

// 在树状数组上二进制倍增，求出第 k 小元素所在的离散化下标。
ll kth(ll k) {
    ll pos = 0;
    ll step = 1;
    while (step * 2 <= coord_cnt) {
        step *= 2;
    }
    for (; step > 0; step /= 2) {
        ll nxt = pos + step;
        if (nxt <= coord_cnt && tree[nxt] < k) {
            pos = nxt;
            k -= tree[nxt];
        }
    }
    return pos + 1;
}

void read_input() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> kind[i] >> value[i];
    }
}

// 把全部特点值收集、去重、排序，得到离散化下标。
void build_discretization() {
    for (ll i = 1; i <= n; i++) {
        coord[i] = value[i];
    }
    sort(coord + 1, coord + n + 1);
    coord_cnt = unique(coord + 1, coord + n + 1) - (coord + 1);
    for (ll i = 1; i <= n; i++) {
        idx[i] = lower_bound(coord + 1, coord + coord_cnt + 1, value[i]) - coord;
    }
}

void solve() {
    for (ll i = 1; i <= n; i++) {
        // 池为空或到来者与池中对象同类：直接入池。
        if (pool_size == 0 || pool_type == kind[i]) {
            pool_type = kind[i];
            add(idx[i], 1);
            pool_size++;
            continue;
        }

        // 异类到来：在池中找前驱（<=value 的最大值）与后继（>=value 的最小值）。
        ll left_cnt = prefix_sum(idx[i] - 1);
        ll best_pos;
        if (left_cnt == 0) {
            best_pos = kth(left_cnt + 1); // 没有前驱，只能取后继
        } else if (left_cnt == pool_size) {
            best_pos = kth(left_cnt); // 没有后继，只能取前驱
        } else {
            ll left_pos = kth(left_cnt);
            ll right_pos = kth(left_cnt + 1);
            // 差值相等时题面要求取较小的那个，即前驱。
            if (value[i] - coord[left_pos] <= coord[right_pos] - value[i]) {
                best_pos = left_pos;
            } else {
                best_pos = right_pos;
            }
        }

        answer = (answer + abs(value[i] - coord[best_pos])) % MOD;
        add(best_pos, -1);
        pool_size--;
    }
    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_discretization();
    solve();

    return 0;
}
