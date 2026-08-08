#include <bits/stdc++.h>
using namespace std;

const int MAXP = 105;

int n, k, p;
int a[MAXP];

int answer; // 当前找到的最优答案

// brute.cpp：小数据暴力解。
// 枚举每次缺车时把地板上的哪一辆拿回书架，求最少拿下来的次数。
void dfs(int pos, vector<int> floor_cars, int cost) {
    if (cost >= answer) {
        return;
    }
    if (pos > p) {
        answer = cost;
        return;
    }

    for (int x : floor_cars) {
        if (x == a[pos]) {
            dfs(pos + 1, floor_cars, cost);
            return;
        }
    }

    if ((int) floor_cars.size() < k) {
        // 地板还没放满，直接把当前这辆车拿下来。
        floor_cars.push_back(a[pos]);
        dfs(pos + 1, floor_cars, cost + 1);
        return;
    }

    // 地板已满，暴力枚举拿走哪一辆旧车。
    for (int i = 0; i < (int) floor_cars.size(); i++) {
        int old = floor_cars[i];
        floor_cars[i] = a[pos];
        dfs(pos + 1, floor_cars, cost + 1);
        floor_cars[i] = old;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;
    for (int i = 1; i <= p; i++) {
        cin >> a[i];
    }

    answer = p + 1;
    vector<int> start;
    dfs(1, start, 0);
    cout << answer << '\n';
    return 0;
}
