#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string gender;
    cin >> gender;
    vector<int> skill(n);
    for (int i = 0; i < n; i++) {
        cin >> skill[i];
    }

    // 最多只能配 min(B, G) 对，与排列顺序无关：
    // 只要两队都还有人，就必然存在相邻异性对，所以总能配到一方归零
    int cnt_b = 0, cnt_g = 0;
    for (char c : gender) {
        if (c == 'B') cnt_b++;
        else cnt_g++;
    }
    int max_pairs = min(cnt_b, cnt_g);

    // 双向链表：prev[i]/nxt[i] 记录当前队伍中 i 的左右邻居
    vector<int> prev(n), nxt(n);
    for (int i = 0; i < n; i++) {
        prev[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[n - 1] = -1;

    vector<char> alive(n, 1);
    // (差值, 左编号, 右编号)：字典序让差值最小、平局最左的候选在堆顶
    using Candidate = tuple<int, int, int>;
    priority_queue<Candidate, vector<Candidate>, greater<Candidate>> heap;
    for (int i = 0; i + 1 < n; i++) {
        if (gender[i] != gender[i + 1]) {
            heap.emplace(abs(skill[i] - skill[i + 1]), i, i + 1);
        }
    }

    vector<pair<int, int>> answer;
    while (!heap.empty()) {
        auto [diff, left, right] = heap.top();
        heap.pop();
        // 懒删除：有人已出列，或已不再相邻，则跳过
        if (!alive[left] || !alive[right] || nxt[left] != right) {
            continue;
        }
        answer.emplace_back(left + 1, right + 1);
        if ((int)answer.size() == max_pairs) {
            break; // 已配满 min(B, G) 对，剩余全是同性，不可能再配
        }
        alive[left] = alive[right] = 0;
        // 删除后只剩可能新产生一个跨过两人的邻对
        int new_left = prev[left], new_right = nxt[right];
        if (new_left >= 0) nxt[new_left] = new_right;
        if (new_right >= 0) prev[new_right] = new_left;
        if (new_left >= 0 && new_right >= 0 && gender[new_left] != gender[new_right]) {
            heap.emplace(abs(skill[new_left] - skill[new_right]), new_left, new_right);
        }
    }

    cout << answer.size() << "\n";
    for (auto [a, b] : answer) {
        cout << a << " " << b << "\n";
    }

    return 0;
}
