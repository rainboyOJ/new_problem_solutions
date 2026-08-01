/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-01 11:35
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

Evaluation evaluate(long long reward_twice) {
    priority_queue<PairValue, vector<PairValue>, PairGreater> slopes;
    PairValue function_at_zero = {0, 0};

    for (int day = 1; day <= n; day++) {
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

void dfs_brute(int day, int balance, long long cost, int count,
               int &answer) {
    if (cost > budget) {
        return;
    }
    if (day == n + 1) {
        if (balance == 0) {
            answer = max(answer, count);
        }
        return;
    }
    dfs_brute(day + 1, balance, cost, count, answer);
    dfs_brute(day + 1, balance + 1,
              cost + make_cost[day], count, answer);
    if (balance > 0) {
        dfs_brute(day + 1, balance - 1,
                  cost + check_cost[day], count + 1, answer);
    }
    dfs_brute(day + 1, balance,
              cost + make_cost[day] + check_cost[day], count + 1, answer);
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
