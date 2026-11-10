/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:43
 * update_at: 2026-11-11 00:43
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 数组模拟队列以追求极致常数和性能
const int MAXN = 100005;
const int MAXM = 7000005;

int q1[MAXN], head1 = 0, tail1 = 0;
int q2[MAXM], head2 = 0, tail2 = 0;
int q3[MAXM], head3 = 0, tail3 = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q, u, v, t;
    if (!(cin >> n >> m >> q >> u >> v >> t)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.rbegin(), a.rend());
    for (int i = 0; i < n; ++i) {
        q1[tail1++] = a[i];
    }

    // 第一行输出：每秒被切断的蚯蚓长度
    bool first_out = true;
    for (int i = 1; i <= m; ++i) {
        // 从三个队列头选取最大元素
        int best_q = -1;
        int max_val = -2e9;

        if (head1 < tail1 && q1[head1] > max_val) {
            max_val = q1[head1];
            best_q = 1;
        }
        if (head2 < tail2 && q2[head2] > max_val) {
            max_val = q2[head2];
            best_q = 2;
        }
        if (head3 < tail3 && q3[head3] > max_val) {
            max_val = q3[head3];
            best_q = 3;
        }

        if (best_q == 1) head1++;
        else if (best_q == 2) head2++;
        else head3++;

        // 真实长度 = 基准值 + 累积偏移 (i - 1) * q
        long long real_len = max_val + 1LL * (i - 1) * q;

        if (i % t == 0) {
            if (!first_out) cout << " ";
            cout << real_len;
            first_out = false;
        }

        // 切成两段：向下取整
        long long part1 = real_len * u / v;
        long long part2 = real_len - part1;

        // 存入队列时的基准值 = 实际切出值 - 当前时间 i * q
        q2[tail2++] = static_cast<int>(part1 - 1LL * i * q);
        q3[tail3++] = static_cast<int>(part2 - 1LL * i * q);
    }
    cout << "\n";

    // 第二行输出：m 秒后所有蚯蚓长度按从大到小排序
    first_out = true;
    int total_worms = n + m;
    long long final_delta = 1LL * m * q;

    for (int rank = 1; rank <= total_worms; ++rank) {
        int best_q = -1;
        int max_val = -2e9;

        if (head1 < tail1 && q1[head1] > max_val) {
            max_val = q1[head1];
            best_q = 1;
        }
        if (head2 < tail2 && q2[head2] > max_val) {
            max_val = q2[head2];
            best_q = 2;
        }
        if (head3 < tail3 && q3[head3] > max_val) {
            max_val = q3[head3];
            best_q = 3;
        }

        if (best_q == 1) head1++;
        else if (best_q == 2) head2++;
        else head3++;

        if (rank % t == 0) {
            if (!first_out) cout << " ";
            cout << max_val + final_delta;
            first_out = false;
        }
    }
    cout << "\n";

    return 0;
}
