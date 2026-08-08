#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MOD = 998244353;

int control_id, test_count;
int n, m;
long long a[MAXN];
int comb[MAXN][MAXN]; // comb[i][j] = C(i, j)
int pow2[MAXN];       // pow2[i] = 2^i

void prepare() {
    pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow2[i] = pow2[i - 1] * 2LL % MOD;
    }

    comb[0][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            if (comb[i][j] >= MOD) {
                comb[i][j] -= MOD;
            }
        }
    }
}

int get_comb(int x, int y) {
    if (x < 0 || y < 0 || y > x) {
        return 0;
    }
    return comb[x][y];
}

void solve_one() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1, greater<long long>());

    long long bad = 0;

    // 枚举最优解会买的 2 元糖果 i，以及贪心会用来卡住它的 1 元糖果 j。
    for (int i = 1; i <= n; i++) {
        int need_extra = m - i - 1;
        if (need_extra < 0) {
            break;
        }

        int p = n + 1;
        int start_j = max(i + 1, m - i + 1);

        for (int j = start_j; j <= n; j++) {
            if (a[i] == a[j]) {
                continue;
            }
            if (a[i] >= 2LL * a[j]) {
                break;
            }

            // p 是最靠前的位置，使得 [p, n] 的糖果都能作为“较低性价比的 1 元糖果”。
            while (p > 1 && a[p - 1] + a[j] < a[i]) {
                p--;
            }

            bad += 1LL * get_comb(j - 2, need_extra) * pow2[n - p + 1] % MOD;
            if (bad >= MOD) {
                bad -= MOD;
            }
        }
    }

    int ans = (pow2[n] - (int)(bad % MOD) + MOD) % MOD;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    prepare();

    cin >> control_id >> test_count;
    while (test_count--) {
        solve_one();
    }

    return 0;
}
