#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> groups(m + 1);
    for (int group_id = 1; group_id <= m; ++group_id) {
        int size;
        cin >> size;
        groups[group_id].resize(size);
        for (int i = 0; i < size; ++i) {
            cin >> groups[group_id][i];
        }
    }

    vector<int> invited(n + 1, 0);
    invited[1] = 1;

    bool changed = true;
    while (changed) {
        changed = false;

        for (int group_id = 1; group_id <= m; ++group_id) {
            int not_invited_count = 0;
            int last_cow = 0;

            for (int cow : groups[group_id]) {
                if (!invited[cow]) {
                    ++not_invited_count;
                    last_cow = cow;
                }
            }

            if (not_invited_count == 1) {
                invited[last_cow] = 1;
                changed = true;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (invited[i]) ++ans;
    }

    cout << ans << '\n';
    return 0;
}
