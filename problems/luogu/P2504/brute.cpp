// brute.cpp：枚举所有可能的跳跃阈值，直接检查图是否连通。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 505;
const int MAXN = 1005;

int monkey_cnt, tree_cnt;
long long jump_len[MAXM];
long long x[MAXN], y[MAXN];
bool vis[MAXN];

long long dis2(int i, int j) {
    long long dx = x[i] - x[j];
    long long dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

bool connected(long long limit2) {
    queue<int> q;
    for (int i = 1; i <= tree_cnt; i++) {
        vis[i] = false;
    }

    q.push(1);
    vis[1] = true;
    int cnt = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 1; v <= tree_cnt; v++) {
            if (vis[v]) {
                continue;
            }
            if (dis2(u, v) > limit2) {
                continue;
            }
            vis[v] = true;
            q.push(v);
            cnt++;
        }
    }

    return cnt == tree_cnt;
}

long long brute_need() {
    vector<long long> cand;
    cand.push_back(0);

    for (int i = 1; i <= tree_cnt; i++) {
        for (int j = i + 1; j <= tree_cnt; j++) {
            cand.push_back(dis2(i, j));
        }
    }

    sort(cand.begin(), cand.end());
    cand.erase(unique(cand.begin(), cand.end()), cand.end());

    for (int i = 0; i < (int)cand.size(); i++) {
        if (connected(cand[i])) {
            return cand[i];
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> monkey_cnt;
    for (int i = 1; i <= monkey_cnt; i++) {
        cin >> jump_len[i];
    }

    cin >> tree_cnt;
    for (int i = 1; i <= tree_cnt; i++) {
        cin >> x[i] >> y[i];
    }

    long long need = brute_need();

    int answer = 0;
    for (int i = 1; i <= monkey_cnt; i++) {
        if (jump_len[i] * jump_len[i] >= need) {
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
