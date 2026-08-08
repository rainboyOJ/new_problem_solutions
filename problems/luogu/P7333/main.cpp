#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct NodeA {
    int value;
    int pos;
};

struct NodeB {
    int value;
    int pos;
};

int n;
int a[MAXN], b[MAXN];
int answer[MAXN];
NodeA arr_a[MAXN];
NodeB arr_b[MAXN];

int ring_distance(int x, int y) {
    int d = abs(x - y);
    return min(d, n - d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        arr_a[i].value = a[i];
        arr_a[i].pos = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        arr_b[i].value = b[i];
        arr_b[i].pos = i;
    }

    sort(arr_a + 1, arr_a + n + 1, [](const NodeA &x, const NodeA &y) {
        return x.value > y.value;
    });
    sort(arr_b + 1, arr_b + n + 1, [](const NodeB &x, const NodeB &y) {
        return x.value > y.value;
    });

    set<int> pos_set;
    int p = 1;

    for (int i = 1; i <= n; i++) {
        while (p <= n && arr_a[p].value >= arr_b[i].value) {
            pos_set.insert(arr_a[p].pos);
            p++;
        }

        int x = arr_b[i].pos;
        if (pos_set.empty() || (int)pos_set.size() == 1 && *pos_set.begin() == x) {
            answer[x] = -1;
            continue;
        }

        int best = n + 1;
        set<int>::iterator it = pos_set.lower_bound(x);

        if (it != pos_set.end()) {
            if (*it != x) {
                best = min(best, ring_distance(x, *it));
            }
            else {
                set<int>::iterator nx = it;
                nx++;
                if (nx != pos_set.end()) {
                    best = min(best, ring_distance(x, *nx));
                }
            }
        }
        if (it != pos_set.begin()) {
            set<int>::iterator pre = it;
            pre--;
            best = min(best, ring_distance(x, *pre));
        }

        int first_pos = *pos_set.begin();
        int last_pos = *pos_set.rbegin();
        if (first_pos != x) {
            best = min(best, ring_distance(x, first_pos));
        }
        if (last_pos != x) {
            best = min(best, ring_distance(x, last_pos));
        }

        answer[x] = best;
    }

    for (int i = 1; i <= n; i++) {
        cout << answer[i] << (i == n ? '\n' : ' ');
    }

    return 0;
}
