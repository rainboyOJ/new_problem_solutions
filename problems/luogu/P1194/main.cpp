#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;
const int INF = 1e9;

int direct_cost, gift_cnt;
int discount[MAXN][MAXN];
int dist_to_tree[MAXN];
bool vis[MAXN];

int prim() {
    for (int i = 1; i <= gift_cnt; i++) {
        dist_to_tree[i] = direct_cost;
        vis[i] = false;
    }

    int answer = 0;

    for (int i = 1; i <= gift_cnt; i++) {
        int u = 0;
        for (int j = 1; j <= gift_cnt; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_to_tree[j] < dist_to_tree[u]) {
                u = j;
            }
        }

        vis[u] = true;
        answer += dist_to_tree[u];

        for (int v = 1; v <= gift_cnt; v++) {
            if (vis[v]) {
                continue;
            }
            if (discount[u][v] < dist_to_tree[v]) {
                dist_to_tree[v] = discount[u][v];
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> direct_cost >> gift_cnt;
    for (int i = 1; i <= gift_cnt; i++) {
        for (int j = 1; j <= gift_cnt; j++) {
            cin >> discount[i][j];
        }
    }

    cout << prim() << '\n';

    return 0;
}
