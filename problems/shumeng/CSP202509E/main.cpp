/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:03
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;

struct PairValue {
    long long cost;
    long long negative_count;
};

struct PairGreater {
    bool operator()(const PairValue &x, const PairValue &y) const {
        if (x.cost != y.cost) {
            return x.cost > y.cost;
        }
        return x.negative_count > y.negative_count;
    }
};

struct Evaluation {
    long long count;
    long long real_cost;
};

int n;
long long budget;
long long make_cost[MAXN + 1];
long long check_cost[MAXN + 1];

PairValue add_pair(const PairValue &x, const PairValue &y) {
    return {x.cost + y.cost, x.negative_count + y.negative_count};
}

PairValue subtract_pair(const PairValue &x, const PairValue &y) {
    return {x.cost - y.cost, x.negative_count - y.negative_count};
}

bool pair_less(const PairValue &x, const PairValue &y) {
    if (x.cost != y.cost) {
        return x.cost < y.cost;
    }
    return x.negative_count < y.negative_count;
}

// 对给定奖励 reward_twice 求最优解。
// 函数值存 2 倍，避免除 2 丢失精度；count 为完成题数，real_cost 为真实花费。
Evaluation evaluate(long long reward_twice) {
    priority_queue<PairValue, vector<PairValue>, PairGreater> slopes; // 斜率小根堆
    PairValue function_at_zero = {0, 0}; // F(0)：余额为 0 时的最小调整费用

    for (int day = 1; day <= n; day++) {
        // 当天的四种选择，用斜率序列的常数次堆操作完成转移（详见题解推导）
        PairValue idle = {0, 0};
        PairValue both = {2LL * (make_cost[day] + check_cost[day])
                              - reward_twice, -1};
        PairValue center = pair_less(both, idle) ? both : idle;
        PairValue down = {2LL * check_cost[day] - reward_twice, -1};
        PairValue up = {2LL * make_cost[day], 0};
        PairValue lower = subtract_pair(center, down);
        PairValue upper = subtract_pair(up, center);

        function_at_zero = add_pair(function_at_zero, center);
        if (!slopes.empty() && pair_less(slopes.top(), lower)) {
            PairValue smallest = slopes.top();
            slopes.pop();
            function_at_zero = add_pair(function_at_zero,
                                         subtract_pair(smallest, lower));
            slopes.push(lower);
        }
        slopes.push(upper);
    }

    long long count = -function_at_zero.negative_count;
    long long real_cost_twice = function_at_zero.cost + reward_twice * count;
    return {count, real_cost_twice / 2};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> budget;
    long long maximum_reward = 0;
    for (int i = 1; i <= n; i++) {
        cin >> make_cost[i];
        maximum_reward = max(maximum_reward, make_cost[i]);
    }
    for (int i = 1; i <= n; i++) {
        cin >> check_cost[i];
        maximum_reward = max(maximum_reward, check_cost[i]);
    }

    // 二分奖励值，找到实际花费不超过预算的最大完成题数
    long long low = 0;
    long long high = 1;
    while (evaluate(high).count < n) {
        high *= 2;
    }
    while (low < high) {
        long long middle = (low + high + 1) / 2;
        Evaluation current = evaluate(middle);
        if (current.real_cost <= budget) {
            low = middle;
        } else {
            high = middle - 1;
        }
    }

    // 奖励不是整数时的修正：在相邻两个奖励点之间按边际花费线性插值
    Evaluation left = evaluate(low);
    if (left.count == n) {
        cout << n << '\n';
        return 0;
    }

    Evaluation right = evaluate(low + 1);
    if (right.real_cost <= budget) {
        cout << right.count << '\n';
        return 0;
    }
    if (right.count == left.count) {
        cout << left.count << '\n';
        return 0;
    }
    long long marginal = (right.real_cost - left.real_cost)
                         / (right.count - left.count);
    long long extra = (budget - left.real_cost) / marginal;
    extra = min(extra, right.count - left.count);
    cout << left.count + extra << '\n';
    return 0;
}
