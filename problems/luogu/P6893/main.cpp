#include <bits/stdc++.h>
using namespace std;

const long double NEG_INF = -1e100L;

struct DiscreteDish {
    int weight;
    long double t;
    long double d;
};

struct ContinuousDish {
    long double t;
    long double d;
};

struct Line {
    long double m, b;
};

int n, W;
vector<DiscreteDish> discrete_dishes;
vector<ContinuousDish> continuous_dishes;
vector<long double> dp, ndp;
vector<long double> cont_best;

long double value_of_line(const Line &line, long double x) {
    return line.m * x + line.b;
}

long double intersect_x(const Line &a, const Line &b) {
    return (a.b - b.b) / (b.m - a.m);
}

void add_line(deque<Line> &q, Line cur) {
    if (!q.empty() && fabsl(q.back().m - cur.m) < 1e-18L) {
        if (q.back().b >= cur.b) {
            return;
        }
        q.pop_back();
    }
    while (q.size() >= 2) {
        Line a = q[q.size() - 2];
        Line b = q[q.size() - 1];
        if (intersect_x(a, b) >= intersect_x(b, cur) - 1e-18L) {
            q.pop_back();
        } else {
            break;
        }
    }
    q.push_back(cur);
}

void solve_discrete_knapsack() {
    dp.assign(W + 1, NEG_INF);
    dp[0] = 0;

    for (size_t idx = 0; idx < discrete_dishes.size(); idx++) {
        int cost = discrete_dishes[idx].weight;
        long double t = discrete_dishes[idx].t;
        long double d = discrete_dishes[idx].d;

        ndp = dp;

        for (int r = 0; r < cost; r++) {
            vector<long double> old;
            for (int pos = r; pos <= W; pos += cost) {
                old.push_back(dp[pos]);
            }

            deque<Line> q;
            int cnt = (int) old.size();

            for (int m = 0; m < cnt; m++) {
                if (old[m] > NEG_INF / 2) {
                    Line cur;
                    cur.m = d * m;
                    cur.b = old[m] - d * m * m / 2.0L - (t + d / 2.0L) * m;
                    add_line(q, cur);
                }

                while (q.size() >= 2 && value_of_line(q[0], m) <= value_of_line(q[1], m) + 1e-18L) {
                    q.pop_front();
                }

                if (!q.empty()) {
                    long double best =
                        -d * m * m / 2.0L + (t + d / 2.0L) * m + value_of_line(q[0], m);
                    int pos = r + m * cost;
                    ndp[pos] = max(ndp[pos], best);
                }
            }
        }

        dp.swap(ndp);
    }
}

void solve_continuous_part() {
    cont_best.assign(W + 1, NEG_INF);
    cont_best[0] = 0;

    if (continuous_dishes.empty()) {
        return;
    }

    long double best_const = NEG_INF;
    vector<ContinuousDish> quad;

    for (size_t i = 0; i < continuous_dishes.size(); i++) {
        if (fabsl(continuous_dishes[i].d) < 1e-18L) {
            best_const = max(best_const, continuous_dishes[i].t);
        } else {
            quad.push_back(continuous_dishes[i]);
        }
    }

    if (best_const > NEG_INF / 2) {
        vector<ContinuousDish> filtered;
        for (size_t i = 0; i < quad.size(); i++) {
            if (quad[i].t > best_const + 1e-18L) {
                filtered.push_back(quad[i]);
            }
        }
        quad.swap(filtered);
    }

    sort(quad.begin(), quad.end(), [](const ContinuousDish &a, const ContinuousDish &b) {
        return a.t > b.t;
    });

    int c = (int) quad.size();
    vector<long double> pref_a(c + 1, 0), pref_b(c + 1, 0), pref_c(c + 1, 0);

    for (int i = 1; i <= c; i++) {
        long double inv = 1.0L / quad[i - 1].d;
        pref_a[i] = pref_a[i - 1] + inv;
        pref_b[i] = pref_b[i - 1] + quad[i - 1].t * inv;
        pref_c[i] = pref_c[i - 1] + quad[i - 1].t * quad[i - 1].t * inv / 2.0L;
    }

    if (best_const > NEG_INF / 2 && c == 0) {
        for (int x = 1; x <= W; x++) {
            cont_best[x] = best_const * x;
        }
        return;
    }

    for (int k = 1; k <= c; k++) {
        long double low = pref_b[k] - pref_a[k] * quad[k - 1].t;
        if (low < 0) {
            low = 0;
        }

        long double next_t;
        if (k < c) {
            next_t = quad[k].t;
            if (best_const > NEG_INF / 2) {
                next_t = max(next_t, best_const);
            }
        } else if (best_const > NEG_INF / 2) {
            next_t = best_const;
        } else {
            next_t = -1e100L;
        }

        long double high;
        if (next_t < -1e90L) {
            high = W;
        } else {
            high = pref_b[k] - pref_a[k] * next_t;
        }

        int left = (int) ceill(low - 1e-18L);
        int right = (int) floorl(high + 1e-18L);
        if (left < 0) {
            left = 0;
        }
        if (right > W) {
            right = W;
        }

        for (int x = left; x <= right; x++) {
            long double lambda = (pref_b[k] - x) / pref_a[k];
            long double val = pref_c[k] - lambda * lambda * pref_a[k] / 2.0L;
            cont_best[x] = max(cont_best[x], val);
        }
    }

    if (best_const > NEG_INF / 2) {
        long double x0 = pref_b[c] - pref_a[c] * best_const;
        if (x0 < 0) {
            x0 = 0;
        }
        long double base = pref_c[c] - best_const * best_const * pref_a[c] / 2.0L;
        int start = (int) ceill(x0 - 1e-18L);
        if (start < 0) {
            start = 0;
        }
        for (int x = start; x <= W; x++) {
            cont_best[x] = max(cont_best[x], base + (x - x0) * best_const);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> W;
    for (int i = 1; i <= n; i++) {
        char type;
        cin >> type;
        if (type == 'D') {
            DiscreteDish dish;
            cin >> dish.weight >> dish.t >> dish.d;
            discrete_dishes.push_back(dish);
        } else {
            ContinuousDish dish;
            cin >> dish.t >> dish.d;
            continuous_dishes.push_back(dish);
        }
    }

    solve_discrete_knapsack();
    solve_continuous_part();

    long double answer = NEG_INF;

    if (continuous_dishes.empty()) {
        answer = dp[W];
    } else {
        for (int used = 0; used <= W; used++) {
            if (dp[used] <= NEG_INF / 2 || cont_best[W - used] <= NEG_INF / 2) {
                continue;
            }
            answer = max(answer, dp[used] + cont_best[W - used]);
        }
    }

    if (answer <= NEG_INF / 2) {
        cout << "impossible\n";
    } else {
        cout << fixed << setprecision(9) << (double) answer << '\n';
    }

    return 0;
}
