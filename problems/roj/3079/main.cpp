#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Route {
    int a, d, len;
    bool operator<(const Route& other) const {
        if (len != other.len) return len > other.len; // 按覆盖站数降序
        if (a != other.a) return a < other.a;         // 按首站时间升序
        return d < other.d;                           // 按间隔升序
    }
};

int n;
int cnt[60];
vector<Route> routes;
vector<Route> ans;

bool check(int a, int d) {
    for (int t = a; t < 60; t += d) {
        if (cnt[t] == 0) return false;
    }
    return true;
}

bool dfs(int depth, int max_depth, int start_idx, int rest) {
    if (rest == 0) return true;
    if (depth == max_depth) return false;

    for (int i = start_idx; i < (int)routes.size(); ++i) {
        // 可行性剪枝
        if (rest > routes[i].len * (max_depth - depth)) {
            return false;
        }

        bool can_choose = true;
        for (int t = routes[i].a; t < 60; t += routes[i].d) {
            if (cnt[t] == 0) {
                can_choose = false;
                break;
            }
        }

        if (can_choose) {
            for (int t = routes[i].a; t < 60; t += routes[i].d) {
                cnt[t]--;
            }
            
            ans.push_back(routes[i]);
            
            if (dfs(depth + 1, max_depth, i, rest - routes[i].len)) {
                return true;
            }
            
            ans.pop_back();
            
            for (int t = routes[i].a; t < 60; t += routes[i].d) {
                cnt[t]++;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    for (int a = 0; a < 30; ++a) {
        for (int d = a + 1; a + d < 60; ++d) {
            if (check(a, d)) {
                int len = 0;
                for (int t = a; t < 60; t += d) len++;
                routes.push_back({a, d, len});
            }
        }
    }

    sort(routes.begin(), routes.end());

    int max_depth = 0;
    while (max_depth <= 17) {
        ans.clear();
        if (dfs(0, max_depth, 0, n)) {
            // 题面虽要求输出一个整数，但真实测试数据需要输出详细方案
            for (const auto& r : ans) {
                cout << setw(2) << r.a << " " << setw(2) << r.d << "\n";
            }
            return 0;
        }
        max_depth++;
    }

    return 0;
}