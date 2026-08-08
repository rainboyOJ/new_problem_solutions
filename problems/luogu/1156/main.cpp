#include <bits/stdc++.h>
using namespace std;

struct Garbage {
    int t, f, h;
    bool operator<(const Garbage& o) const {
        return t < o.t;                  // 按掉落时间升序
    }
};

const int MAXD = 105;

int D, G;
vector<Garbage> gb;
// dp[h] 表示当前堆叠高度为 h 时，奶牛的最大生命值。
int dp[MAXD];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> D >> G;
    gb.resize(G);
    for (int i = 0; i < G; i++) {
        cin >> gb[i].t >> gb[i].f >> gb[i].h;
    }
    sort(gb.begin(), gb.end());

    fill(dp, dp + D + 1, -1);
    dp[0] = 10;                           // 初始生命为 10

    for (int i = 0; i < G; i++) {
        int t = gb[i].t, f = gb[i].f, h = gb[i].h;
        vector<int> ndp(dp, dp + D + 1);  // 旧状态备份
        for (int j = 0; j <= D; j++) {
            if (dp[j] < t) continue;     // 活不到这个垃圾落下的时刻
            int newh = j + h;
            if (newh >= D) {             // 堆叠高度足够，逃出
                cout << t << '\n';
                return 0;
            }
            ndp[newh] = max(ndp[newh], dp[j]);       // 堆放：高度增加，生命不变
            ndp[j] = max(ndp[j], dp[j] + f);          // 吃掉：高度不变，生命增加
        }
        memcpy(dp, ndp.data(), (D + 1) * sizeof(int));
    }

    int ans = 10;
    for (int j = 0; j <= D; j++) {
        if (dp[j] >= 0) {
            ans = max(ans, dp[j]);
        }
    }
    cout << ans << '\n';
    return 0;
}
