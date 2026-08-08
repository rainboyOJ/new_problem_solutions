#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int n;
int lc[25], rc[25];

struct Node {
    int left;
    int right;
};

vector<Node> trees[15];
map<tuple<int, int, int>, int> id_of[15];

void init_all_trees(int max_size) {
    trees[0].push_back({-1, -1});

    for (int sz = 1; sz <= max_size; sz++) {
        for (int left_size = 0; left_size <= sz - 1; left_size++) {
            int right_size = sz - 1 - left_size;
            for (int i = 0; i < (int) trees[left_size].size(); i++) {
                for (int j = 0; j < (int) trees[right_size].size(); j++) {
                    tuple<int, int, int> state = make_tuple(left_size, i, j);
                    if (id_of[sz].count(state)) {
                        continue;
                    }
                    id_of[sz][state] = (int) trees[sz].size();
                    trees[sz].push_back({i, j});
                }
            }
        }
    }
}

int calc_size_from_input(int u) {
    if (u == 0) {
        return 0;
    }
    return calc_size_from_input(lc[u]) + calc_size_from_input(rc[u]) + 1;
}

int build_id_from_input(int u) {
    if (u == 0) {
        return 0;
    }

    int left_size = calc_size_from_input(lc[u]);
    int right_size = calc_size_from_input(rc[u]);
    int left_id = build_id_from_input(lc[u]);
    int right_id = build_id_from_input(rc[u]);
    int total_size = left_size + right_size + 1;

    return id_of[total_size][make_tuple(left_size, left_id, right_id)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> lc[i] >> rc[i];
    }

    init_all_trees(n);

    int total_size = calc_size_from_input(1);
    int rank_in_same_size = build_id_from_input(1);

    i64 ans = 0;
    for (int i = 1; i < total_size; i++) {
        ans += (int) trees[i].size();
    }
    ans += rank_in_same_size;

    cout << ans << '\n';

    return 0;
}
