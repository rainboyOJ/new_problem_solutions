#include <bits/stdc++.h>
using namespace std;

static int P, Q;
static vector<int> need_release;
static vector<int> released;

int dfs(vector<int> cur) {
    if (cur.empty()) {
        return 0;
    }

    int best = INT_MAX;
    for (int x : cur) {
        int left = 0;
        int right = P + 1;
        for (int y : released) {
            if (y < x) {
                left = max(left, y);
            } else if (y > x) {
                right = min(right, y);
            }
        }
        int cost = right - left - 2;

        vector<int> next = cur;
        next.erase(find(next.begin(), next.end(), x));
        released.push_back(x);
        best = min(best, cost + dfs(next));
        released.pop_back();
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> P >> Q;
    need_release.resize(Q);
    for (int i = 0; i < Q; ++i) {
        cin >> need_release[i];
    }

    released.clear();
    released.push_back(0);
    released.push_back(P + 1);
    cout << dfs(need_release) << '\n';
    return 0;
}
