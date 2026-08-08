#include <bits/stdc++.h>
using namespace std;

struct Item {
    int t;
    int c;
    int p;
};

static int parse_time(const string &s) {
    size_t pos = s.find(':');
    int h = stoi(s.substr(0, pos));
    int m = stoi(s.substr(pos + 1));
    return h * 60 + m;
}

static vector<Item> items;
static vector<vector<int>> memo;

static int dfs(int idx, int rest) {
    if (idx == (int)items.size()) {
        return 0;
    }

    int &res = memo[idx][rest];
    if (res != -1) {
        return res;
    }

    res = dfs(idx + 1, rest);

    const Item &it = items[idx];
    int limit = rest / it.t;
    if (it.p > 0) {
        limit = min(limit, it.p);
    }

    for (int take = 1; take <= limit; ++take) {
        res = max(res, dfs(idx + 1, rest - take * it.t) + take * it.c);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start_s, end_s;
    int n;
    if (!(cin >> start_s >> end_s >> n)) {
        return 0;
    }

    int limit = parse_time(end_s) - parse_time(start_s);
    if (limit < 0) {
        limit += 24 * 60;
    }

    items.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].t >> items[i].c >> items[i].p;
    }

    memo.assign(n, vector<int>(limit + 1, -1));
    cout << dfs(0, limit) << '\n';
    return 0;
}
