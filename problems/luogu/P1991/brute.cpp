#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举小数据的卫星分块划分，验证最小 D。

const int MAXP = 12;

int s, p;
int x_pos[MAXP], y_pos[MAXP];
int group_id[MAXP];
double answer;

double distance_between(int i, int j) {
    double dx = x_pos[i] - x_pos[j];
    double dy = y_pos[i] - y_pos[j];
    return sqrt(dx * dx + dy * dy);
}

void read_input() {
    cin >> s >> p;
    for (int i = 1; i <= p; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }
}

void evaluate() {
    double need = 0.0;
    for (int g = 1; g <= s; g++) {
        vector<int> nodes;
        for (int i = 1; i <= p; i++) {
            if (group_id[i] == g) {
                nodes.push_back(i);
            }
        }
        if ((int)nodes.size() <= 1) {
            continue;
        }

        bool used[MAXP];
        double dist[MAXP];
        for (int i = 0; i < (int)nodes.size(); i++) {
            used[i] = false;
            dist[i] = 1e100;
        }
        dist[0] = 0.0;

        for (int step = 0; step < (int)nodes.size(); step++) {
            int u = -1;
            for (int i = 0; i < (int)nodes.size(); i++) {
                if (!used[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }
            used[u] = true;
            need = max(need, dist[u]);

            for (int v = 0; v < (int)nodes.size(); v++) {
                if (!used[v]) {
                    double w = distance_between(nodes[u], nodes[v]);
                    if (w < dist[v]) {
                        dist[v] = w;
                    }
                }
            }
        }
    }

    answer = min(answer, need);
}

void dfs(int pos, int used_groups) {
    if (pos == p + 1) {
        if (used_groups == s) {
            evaluate();
        }
        return;
    }

    for (int g = 1; g <= used_groups; g++) {
        group_id[pos] = g;
        dfs(pos + 1, used_groups);
    }

    if (used_groups < s) {
        group_id[pos] = used_groups + 1;
        dfs(pos + 1, used_groups + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    answer = 1e100;
    group_id[1] = 1;
    dfs(2, 1);

    cout << fixed << setprecision(2) << answer << '\n';

    return 0;
}
