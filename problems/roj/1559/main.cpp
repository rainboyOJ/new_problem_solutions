/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-30 18:02
 * update_at: 2026-10-05 08:18
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 一个状态就是三颗棋子升序排列后的位置
struct State {
    ll a;
    ll b;
    ll c;
};

// 收缩步数上界：任何状态的深度都远小于它，用来表示“一直收缩到根”
const ll INF_STEPS = 1000000000000000000LL;

// 比较两个状态是否完全相同（即是否为树上的同一个节点）
bool same_state(State x, State y) {
    return x.a == y.a && x.b == y.b && x.c == y.c;
}

// 从状态 s 沿唯一的父边向根收缩，最多走 limit 步。
// 返回收缩后的状态，实际步数写入 out_steps。
State climb(State s, ll limit, ll &out_steps) {
    ll d1 = s.b - s.a; // 左间隙
    ll d2 = s.c - s.b; // 右间隙
    ll done = 0;
    // 两间隙相等时已经是根，无法继续向根收缩
    while (d1 != d2 && done < limit) {
        if (d1 < d2) {
            // 右间隙大：最右棋子连续跳过中轴，等价于右间隙反复减去左间隙。
            // 一次整除算出这批能走多少步，避免 (1, 1e9) 这类数据单步退化。
            ll t = (d2 - 1) / d1;
            if (t > limit - done) {
                t = limit - done;
            }
            s.a += t * d1;
            s.b += t * d1;
            d2 -= t * d1;
            done += t;
        } else {
            // 左间隙大：最左棋子连续跳过中轴，等价于左间隙反复减去右间隙
            ll t = (d1 - 1) / d2;
            if (t > limit - done) {
                t = limit - done;
            }
            s.b -= t * d2;
            s.c -= t * d2;
            d1 -= t * d2;
            done += t;
        }
    }
    out_steps = done;
    return s;
}

// 求跳动树上两状态的距离（最少跳动次数）。
// reachable 用来区分“根不同，无解”这种情况。
ll tree_distance(State start, State goal, bool &reachable) {
    ll depth_start = 0;
    ll depth_goal = 0;
    State root_start = climb(start, INF_STEPS, depth_start);
    State root_goal = climb(goal, INF_STEPS, depth_goal);
    if (!same_state(root_start, root_goal)) {
        reachable = false;
        return 0;
    }
    reachable = true;

    // 先把较深的一方收缩到和另一方同深度
    if (depth_start > depth_goal) {
        ll ignored = 0;
        start = climb(start, depth_start - depth_goal, ignored);
    } else if (depth_goal > depth_start) {
        ll ignored = 0;
        goal = climb(goal, depth_goal - depth_start, ignored);
    }

    // 同深度下“两边各收缩 k 步后相遇”对 k 单调，二分最小 k 即到达 LCA
    ll common_depth = min(depth_start, depth_goal);
    ll lo = 0;
    ll hi = common_depth;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        ll ignored_start = 0;
        ll ignored_goal = 0;
        State up_start = climb(start, mid, ignored_start);
        State up_goal = climb(goal, mid, ignored_goal);
        if (same_state(up_start, up_goal)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    ll lca_depth = common_depth - lo; // 最近公共祖先到根的深度
    return depth_start + depth_goal - 2 * lca_depth;
}

void read_data(State &start, State &goal) {
    ll p[3];
    for (int i = 0; i < 3; i++) {
        cin >> p[i];
    }
    sort(p, p + 3);
    start.a = p[0];
    start.b = p[1];
    start.c = p[2];

    for (int i = 0; i < 3; i++) {
        cin >> p[i];
    }
    sort(p, p + 3);
    goal.a = p[0];
    goal.b = p[1];
    goal.c = p[2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    State start;
    State goal;
    read_data(start, goal);

    bool reachable = false;
    ll steps = tree_distance(start, goal, reachable);
    if (!reachable) {
        cout << "NO" << "\n";
    } else {
        cout << "YES" << "\n";
        cout << steps << "\n";
    }

    return 0;
}
