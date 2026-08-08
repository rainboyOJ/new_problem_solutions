#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 5;

int n, m;
vector<vector<int>> groups;
vector<vector<int>> belong;
vector<int> rest_count;
vector<char> invited;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    groups.assign(m + 1, vector<int>());
    belong.assign(n + 1, vector<int>());
    rest_count.assign(m + 1, 0);
    invited.assign(n + 1, 0);

    for (int group_id = 1; group_id <= m; ++group_id) {
        int size;
        cin >> size;
        rest_count[group_id] = size;
        groups[group_id].resize(size);

        for (int i = 0; i < size; ++i) {
            int cow;
            cin >> cow;
            groups[group_id][i] = cow;
            belong[cow].push_back(group_id);
        }
    }

    queue<int> q;
    int ans = 0;

    auto invite_cow = [&](int cow) {
        if (invited[cow]) return;
        invited[cow] = 1;
        q.push(cow);
        ++ans;
    };

    invite_cow(1);
    for (int group_id = 1; group_id <= m; ++group_id) {
        if (rest_count[group_id] == 1) {
            invite_cow(groups[group_id][0]);
        }
    }

    while (!q.empty()) {
        int cow = q.front();
        q.pop();

        for (int group_id : belong[cow]) {
            --rest_count[group_id];
            if (rest_count[group_id] != 1) {
                continue;
            }

            // 这个组已经邀请了 k-1 头牛，找出最后一头没有邀请的牛。
            for (int other : groups[group_id]) {
                if (!invited[other]) {
                    invite_cow(other);
                    break;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
