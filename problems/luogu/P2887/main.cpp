#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

struct Cow {
    int min_spf;
    int max_spf;
};

struct Lotion {
    int spf;
    int cover;
};

int c, l;
Cow cows[MAXN];
Lotion lotions[MAXN];

bool cmp_cow_min(const Cow &a, const Cow &b) {
    if (a.min_spf != b.min_spf) {
        return a.min_spf < b.min_spf;
    }
    return a.max_spf < b.max_spf;
}

bool cmp_lotion(const Lotion &a, const Lotion &b) {
    return a.spf < b.spf;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> c >> l;
    for (int i = 1; i <= c; i++) {
        cin >> cows[i].min_spf >> cows[i].max_spf;
    }
    for (int i = 1; i <= l; i++) {
        cin >> lotions[i].spf >> lotions[i].cover;
    }

    sort(cows + 1, cows + c + 1, cmp_cow_min);
    sort(lotions + 1, lotions + l + 1, cmp_lotion);

    priority_queue<int, vector<int>, greater<int> > pq;
    int ptr = 1;
    int ans = 0;

    for (int i = 1; i <= l; i++) {
        int spf = lotions[i].spf;
        while (ptr <= c && cows[ptr].min_spf <= spf) {
            pq.push(cows[ptr].max_spf);
            ptr++;
        }

        int cnt = lotions[i].cover;
        while (cnt > 0 && !pq.empty()) {
            int max_spf = pq.top();
            pq.pop();
            if (max_spf < spf) {
                continue;
            }
            ans++;
            cnt--;
        }
    }

    cout << ans << '\n';
    return 0;
}
