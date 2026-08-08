#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int T;
int n, m;
long long L, V;
long long d[MAXN], v[MAXN], a[MAXN];
long long p[MAXN];
vector<pair<int, int> > intervals;

bool cmp_interval(const pair<int, int> &x, const pair<int, int> &y) {
    if (x.second != y.second) {
        return x.second < y.second;
    }
    return x.first < y.first;
}

bool is_speeding(long long d, long long v, long long a, long long pos) {
    long long value = v * v + 2LL * a * (pos - d);
    return value > V * V;
}

void add_interval(long long d, long long v, long long a) {
    int start = lower_bound(p + 1, p + m + 1, d) - p;
    if (start > m) {
        return;
    }

    if (a == 0) {
        if (v > V) {
            intervals.push_back(make_pair(start, m));
        }
        return;
    }

    if (a > 0) {
        int left = start, right = m;
        int first = m + 1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (is_speeding(d, v, a, p[mid])) {
                first = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        if (first <= m) {
            intervals.push_back(make_pair(first, m));
        }
        return;
    }

    if (v <= V || !is_speeding(d, v, a, p[start])) {
        return;
    }

    int left = start, right = m;
    int last = start;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (is_speeding(d, v, a, p[mid])) {
            last = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    intervals.push_back(make_pair(start, last));
}

int min_required_sensors() {
    // 区间按右端点排序，贪心选择当前区间的右端点。
    sort(intervals.begin(), intervals.end(), cmp_interval);

    int selected = 0;
    int last_pos = 0;
    for (int i = 0; i < (int)intervals.size(); i++) {
        if (last_pos < intervals[i].first) {
            selected++;
            last_pos = intervals[i].second;
        }
    }

    return selected;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n >> m >> L >> V;

        intervals.clear();

        for (int i = 1; i <= n; i++) {
            cin >> d[i] >> v[i] >> a[i];
        }

        for (int i = 1; i <= m; i++) {
            cin >> p[i];
        }

        for (int i = 1; i <= n; i++) {
            add_interval(d[i], v[i], a[i]);
        }

        int speeding_cars = (int)intervals.size();
        int required = min_required_sensors();

        cout << speeding_cars << ' ' << m - required << '\n';
    }

    return 0;
}
