/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:02
 * update_at: 2026-10-06 17:02
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 20; // N <= 18

ll n, capacity;
ll cat[MAXN];        // 按重量降序排列的猫
ll space_left[MAXN]; // 每辆已租车的剩余空间
ll suffix[MAXN];     // suffix[i] = 第 i 只及以后猫的重量和
ll least[MAXN];      // least[i] = 第 i 只及以后至少还要几辆车
ll best;             // 当前搜到的最小车数
ll free_sum;         // 所有已租车剩余空间之和
int car_cnt;         // 当前已租车数

// 贪心：按重量降序，每只猫塞进剩余空间最小且能装下的车，返回车数上界
ll fit_first() {
    vector<ll> spaces;
    for (int i = 0; i < n; i++) {
        ll weight = cat[i];
        int pick = -1;
        ll min_space = capacity + 1;
        for (int j = 0; j < (int)spaces.size(); j++) {
            if (spaces[j] >= weight && spaces[j] < min_space) {
                min_space = spaces[j];
                pick = j;
            }
        }
        if (pick < 0) {
            spaces.push_back(capacity - weight);
        } else {
            spaces[pick] -= weight;
        }
    }
    return (ll)spaces.size();
}

// 预处理 suffix 与 least 下界数组
void preprocess() {
    suffix[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + cat[i];
    }
    for (int i = 0; i < n; i++) {
        least[i] = 1;
        for (int k = 1; k <= n - i; k++) {
            // 第 i 只及以后最轻的 k 只中，最重的是 cat[i+k-1]
            ll per_car = capacity / cat[i + k - 1];
            if (per_car == 0) per_car = 1;
            ll need = (k + per_car - 1) / per_car;
            if (need > least[i]) least[i] = need;
        }
    }
}

// 第 dep 只猫选择落点：放进某辆已租车，或新租一辆
void dfs_choose(int dep) {
    if (car_cnt >= best) return; // 已用车数不优于当前最优解
    if (dep == n) {
        best = car_cnt; // 所有猫都安置完毕
        return;
    }
    if (least[dep] >= best) return; // 剩余最重几只的车数下界
    // 现有空位塞不下的重量还需 ceil((suffix[dep] - free_sum) / capacity) 辆车
    ll need = (suffix[dep] - free_sum + capacity - 1) / capacity;
    if (car_cnt + need >= best) return;

    ll weight = cat[dep];
    ll tried[MAXN]; // 本层已经试过的剩余空间值
    int tried_cnt = 0;

    // 尝试放进已有的车，剩余空间相同的车只试一辆
    for (int i = 0; i < car_cnt; i++) {
        if (space_left[i] < weight) continue;
        bool same = false;
        for (int j = 0; j < tried_cnt; j++) {
            if (tried[j] == space_left[i]) {
                same = true;
                break;
            }
        }
        if (same) continue;
        tried[tried_cnt++] = space_left[i];

        space_left[i] -= weight;
        free_sum -= weight;
        dfs_choose(dep + 1);
        space_left[i] += weight;
        free_sum += weight;
    }

    // 新租一辆车
    space_left[car_cnt] = capacity - weight;
    free_sum += capacity - weight;
    car_cnt++;
    dfs_choose(dep + 1);
    car_cnt--;
    free_sum -= capacity - weight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> capacity;
    for (int i = 0; i < n; i++) {
        cin >> cat[i];
    }
    // 按重量降序：重猫分支窄，能更快收紧 best
    sort(cat, cat + n, greater<ll>());

    preprocess();
    best = fit_first();
    car_cnt = 0;
    free_sum = 0;
    dfs_choose(0);

    cout << best << "\n";
    return 0;
}
