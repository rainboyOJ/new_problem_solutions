/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// subtask_55.cpp：55/70 分档解法。先用两条贪心结论把"敢不敢吃"理清
// （吃完不是最弱必吃；吃完变最弱则递归看下一条蛇敢不敢吃），
// 再用 std::set 维护强弱顺序，单组 O(n log n)。n <= 1e6 时建议换双队列 O(n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// (体力值, 编号) 升序即从弱到强：体力值小者弱，相同则编号小者弱。
typedef pair<ll, int> Snake;

int T, n;
ll a[1000005];  // a[i]：第 i 条蛇的体力值
set<Snake> alive; // 当前存活的蛇，begin() 最弱，rbegin() 最强
int eaten_count;  // 已经被吃掉的蛇的数量

// 取出当前最弱蛇。
Snake get_min_snake() {
    Snake result = *alive.begin();
    alive.erase(alive.begin());
    return result;
}

// 取出当前最强蛇。
Snake get_max_snake() {
    set<Snake>::iterator it = alive.end();
    it--;
    Snake result = *it;
    alive.erase(it);
    return result;
}

// 最强蛇吃掉最弱蛇后生成的新蛇：体力值相减，编号保留。
Snake make_after_eat(const Snake &strongest, const Snake &weakest) {
    return make_pair(strongest.first - weakest.first, strongest.second);
}

// 判断 strongest 吃 weakest 后，新蛇是否一定不是当前最弱蛇（即可安全吃）。
bool after_eat_not_weakest(const Snake &strongest, const Snake &weakest, const Snake &second_min) {
    return make_after_eat(strongest, weakest) > second_min;
}

// 第一阶段：处理所有"必吃"局面。
// 只剩两条时不进循环（见 solve_current_case 的特判），保证取第二弱时集合非空。
void solve_forced_part() {
    while ((int)alive.size() > 2) {
        Snake strongest = get_max_snake();
        Snake weakest = get_min_snake();
        Snake second_min = get_min_snake();

        if (after_eat_not_weakest(strongest, weakest, second_min)) {
            eaten_count++;
            alive.insert(make_after_eat(strongest, weakest));
            alive.insert(second_min);
        } else {
            // 吃完会变最弱：把取出来的三条还回去，交给冒险阶段递归判断。
            alive.insert(strongest);
            alive.insert(second_min);
            alive.insert(weakest);
            return;
        }
    }
}

// 第二阶段：递归判断当前局面下最强蛇是否敢冒险吃最弱蛇。
// 吃完变最弱时模拟吃完的后果：下一条蛇会吃它 -> 它不敢吃；否则敢吃。
bool can_eat_in_risky_part(int alive_count) {
    if (alive_count <= 1) {
        return false;
    }
    if (alive_count == 2) {
        return true;
    }

    Snake strongest = get_max_snake();
    Snake weakest = get_min_snake();
    Snake second_min = get_min_snake();

    if (after_eat_not_weakest(strongest, weakest, second_min)) {
        return true;
    }

    alive.insert(second_min);
    alive.insert(make_after_eat(strongest, weakest));
    return !can_eat_in_risky_part(alive_count - 1);
}

// 求解单组测试数据，返回最终存活蛇的数量。
int solve_current_case() {
    alive.clear();
    eaten_count = 0;
    for (int i = 1; i <= n; i++) {
        alive.insert(make_pair(a[i], i));
    }

    solve_forced_part();

    int alive_count = (int)alive.size();
    if (alive_count == 2) {
        // 只剩两条：最强吃最弱后独自存活，必吃。
        eaten_count++;
    } else if (can_eat_in_risky_part(alive_count)) {
        eaten_count++;
    }

    return n - eaten_count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cout << solve_current_case() << '\n';

    for (int tc = 2; tc <= T; tc++) {
        int k;
        cin >> k;
        for (int i = 1; i <= k; i++) {
            int x;
            ll y;
            cin >> x >> y;
            a[x] = y;
        }
        cout << solve_current_case() << '\n';
    }

    return 0;
}
