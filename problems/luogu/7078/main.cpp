// main.cpp：双队列维护强弱顺序，先处理必吃局面，再递归判断冒险吃。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

struct Snake {
    long long value;
    int id;
    int from_queue;
};

int T, n;
long long a[MAXN];
Snake q1[MAXN * 2], q2[MAXN * 2];
int l1, r1, l2, r2;
int eaten_count;

bool weaker_than(const Snake &a, const Snake &b) {
    if (a.value != b.value) {
        return a.value < b.value;
    }
    return a.id < b.id;
}

bool stronger_than(const Snake &a, const Snake &b) {
    if (a.value != b.value) {
        return a.value > b.value;
    }
    return a.id > b.id;
}

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

Snake make_after_eat(const Snake &strongest, const Snake &weakest) {
    Snake result;
    result.value = strongest.value - weakest.value;
    result.id = strongest.id;
    result.from_queue = 2;
    return result;
}

// 判断 strongest 吃 weakest 后是否一定不是当前最弱蛇。
bool after_eat_not_weakest(const Snake &strongest, const Snake &weakest, const Snake &second_min) {
    Snake changed = make_after_eat(strongest, weakest);
    return stronger_than(changed, second_min);
}

void solve_forced_part() {
    while (n - eaten_count > 1) {
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
    if (can_eat_in_risky_part(n - eaten_count)) {
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
            long long y;
            cin >> x >> y;
            a[x] = y;
        }
        cout << solve_current_case() << '\n';
    }

    return 0;
}
