/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 21:11
 * update_at: 2026-10-01 22:33
 */
// main.cpp：双队列维护强弱顺序，先处理必吃局面，再递归判断冒险吃。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1000005;

struct Snake {
    ll value;
    int id;
    int from_queue;
};

int T, n;
ll a[MAXN];
Snake q1[MAXN * 2], q2[MAXN * 2];
int l1, r1, l2, r2;
int eaten_count;

// 比较两条蛇的强弱：体力值大者强，相同则编号大者强。
// 参数用 x/y，避开全局体力值数组 a[]。
bool weaker_than(const Snake &x, const Snake &y) {
    if (x.value != y.value) {
        return x.value < y.value;
    }
    return x.id < y.id;
}

bool stronger_than(const Snake &x, const Snake &y) {
    if (x.value != y.value) {
        return x.value > y.value;
    }
    return x.id > y.id;
}

// 从两个队列的队首取出较弱者。
Snake get_min_snake() {
    Snake result;
    if (l1 <= r1 && l2 <= r2) {
        if (weaker_than(q1[l1], q2[l2])) {
            result = q1[l1++];
        } else {
            result = q2[l2++];
        }
    } else if (l1 <= r1) {
        result = q1[l1++];
    } else {
        result = q2[l2++];
    }
    return result;
}

// 从两个队列的队尾取出较强者。
Snake get_max_snake() {
    Snake result;
    if (l1 <= r1 && l2 <= r2) {
        if (stronger_than(q1[r1], q2[r2])) {
            result = q1[r1--];
        } else {
            result = q2[r2--];
        }
    } else if (l1 <= r1) {
        result = q1[r1--];
    } else {
        result = q2[r2--];
    }
    return result;
}

void push_back_original(const Snake &x) {
    q1[++r1] = x;
}

void push_front_original(const Snake &x) {
    q1[--l1] = x;
}

void push_back_new(const Snake &x) {
    q2[++r2] = x;
}

void push_front_new(const Snake &x) {
    q2[--l2] = x;
}

void restore_front(const Snake &x) {
    if (x.from_queue == 1) {
        push_front_original(x);
    } else {
        push_front_new(x);
    }
}

void restore_back(const Snake &x) {
    if (x.from_queue == 1) {
        push_back_original(x);
    } else {
        push_back_new(x);
    }
}

// 最强蛇吃掉最弱蛇后生成的新蛇。
Snake make_after_eat(const Snake &strongest, const Snake &weakest) {
    Snake result;
    result.value = strongest.value - weakest.value;
    result.id = strongest.id;
    result.from_queue = 2;
    return result;
}

// 判断 strongest 吃 weakest 后，新蛇是否一定不是当前最弱蛇。
bool after_eat_not_weakest(const Snake &strongest, const Snake &weakest, const Snake &second_min) {
    Snake changed = make_after_eat(strongest, weakest);
    return stronger_than(changed, second_min);
}

// 第一阶段：处理所有"必吃"局面。
// 若最强蛇吃完后不是最弱，则它一定会吃，继续循环。
// 只剩两条时不进循环（见 solve_current_case 的特判），保证取第二弱时队列非空。
void solve_forced_part() {
    while (n - eaten_count > 2) {
        Snake strongest = get_max_snake();
        Snake weakest = get_min_snake();
        Snake second_min = get_min_snake();

        if (after_eat_not_weakest(strongest, weakest, second_min)) {
            eaten_count++;
            Snake changed = make_after_eat(strongest, weakest);

            // 新蛇在这一阶段不会成为最弱；为了维持双队列顺序，先放新蛇，再还回第二弱蛇。
            push_front_new(changed);
            restore_front(second_min);
        } else {
            restore_back(strongest);
            restore_front(second_min);
            restore_front(weakest);
            return;
        }
    }
}

// 第二阶段：递归判断当前局面下，最强蛇是否敢冒险吃最弱蛇。
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

    Snake changed = make_after_eat(strongest, weakest);
    restore_front(second_min);
    push_front_new(changed);

    // 如果下一条蛇会吃掉它，那么当前蛇就不能冒险；否则当前蛇可以吃。
    return !can_eat_in_risky_part(alive_count - 1);
}

// 求解单组测试数据，返回最终存活蛇的数量。
int solve_current_case() {
    l1 = MAXN;
    r1 = MAXN - 1;
    l2 = MAXN;
    r2 = MAXN - 1;
    eaten_count = 0;

    for (int i = 1; i <= n; i++) {
        Snake x;
        x.value = a[i];
        x.id = i;
        x.from_queue = 1;
        push_back_original(x);
    }

    solve_forced_part();
    int alive_count = n - eaten_count;
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
