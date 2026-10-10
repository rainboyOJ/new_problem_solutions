/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int m, n;
int order_[405];            // 安排顺序（展开后的工件号序列）
int mach[25][25], cost[25][25];   // mach[j][k]/cost[j][k]：工件 j 第 k 道工序
int step[25];
int job_free[25];
vector<pair<int, int> > slots[25];   // 每台机器的占用区间 (start, end)

// 在机器已占用的区间里，找到能放下长度 dur 任务的最早开始时刻
int earliest_slot(int machine, int release, int dur) {
    int prev_end = 0;
    vector<pair<int, int> >& iv = slots[machine];
    for (size_t i = 0; i < iv.size(); i++) {
        int s = iv[i].first, e = iv[i].second;
        int start = max(prev_end, release);
        if (start + dur <= s) return start;
        prev_end = e;
    }
    return max(prev_end, release);
}

// 把新区间有序插入
void insert_slot(int machine, int start, int end) {
    vector<pair<int, int> >& iv = slots[machine];
    pair<int, int> p = make_pair(start, end);
    // 按 start 升序插入
    vector<pair<int, int> >::iterator it = iv.begin();
    while (it != iv.end() && it->first < start) ++it;
    iv.insert(it, p);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 0; i < n * m; i++) cin >> order_[i];
    for (int j = 1; j <= n; j++) {
        mach[j][0] = 0; cost[j][0] = 0;
        for (int k = 1; k <= m; k++) cin >> mach[j][k];
    }
    for (int j = 1; j <= n; j++) {
        for (int k = 1; k <= m; k++) cin >> cost[j][k];
    }
    for (int j = 1; j <= n; j++) { step[j] = 0; job_free[j] = 0; }
    for (int mi = 1; mi <= m; mi++) slots[mi].clear();

    for (int idx = 0; idx < n * m; idx++) {
        int j = order_[idx];
        step[j]++;
        int k = step[j];
        int machine = mach[j][k], dur = cost[j][k];
        int start = earliest_slot(machine, job_free[j], dur);
        insert_slot(machine, start, start + dur);
        job_free[j] = start + dur;
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) ans = max(ans, job_free[j]);
    cout << ans << "\n";
    return 0;
}
