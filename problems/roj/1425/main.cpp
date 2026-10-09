/*
 * Author: 2026-10-09 08:30
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 10005;

struct Job {
    int id;
    int a;
    int b;
    int group;
};

Job jobs[MAXN];

bool cmp(const Job &x, const Job &y) {
    if (x.group != y.group) {
        return x.group < y.group;
    }
    if (x.group == 1) {
        if (x.a != y.a) return x.a < y.a;
        return x.b > y.b;
    } else {
        if (x.b != y.b) return x.b > y.b;
        return x.a < y.a;
    }
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].a;
        jobs[i].id = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i].b;
    }

    for (int i = 0; i < n; ++i) {
        if (jobs[i].a <= jobs[i].b) {
            jobs[i].group = 1;
        } else {
            jobs[i].group = 2;
        }
    }

    sort(jobs, jobs + n, cmp);

    ll ta = 0;
    ll tb = 0;
    for (int i = 0; i < n; ++i) {
        ta += jobs[i].a;
        if (tb < ta) {
            tb = ta;
        }
        tb += jobs[i].b;
    }

    cout << tb << "\n";
    for (int i = 0; i < n; ++i) {
        cout << jobs[i].id << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}