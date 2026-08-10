#include <bits/stdc++.h>
using namespace std;

struct Cand {
    int diff, left, right;
    bool operator<(const Cand& o) const {
        if (diff != o.diff) return diff < o.diff;
        return left < o.left;
    }
};

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

    // 双向链表：当前队伍中每个编号的左右邻居
    vector<int> prev(n), nxt(n);
    for (int i = 0; i < n; i++) {
        prev[i] = i - 1;
        nxt[i] = i + 1;
    }
    nxt[n - 1] = -1;

    // 手写小根堆（1-based）；pos[i] = 以 i 为左端点的候选在堆中的下标，-1 表示不在堆中
    vector<Cand> heap(n + 1);
    vector<int> pos(n, -1);
    int size = 0;

    auto swap_pos = [&](int a, int b) {
        swap(heap[a], heap[b]);
        pos[heap[a].left] = a;
        pos[heap[b].left] = b;
    };
    auto up = [&](int p) {
        while (p > 1 && heap[p] < heap[p >> 1]) {
            swap_pos(p, p >> 1);
            p >>= 1;
        }
    };
    auto down = [&](int p) {
        while ((p << 1) <= size) {
            int best = p;
            int left_child = p << 1;
            if (heap[left_child] < heap[best]) best = left_child;
            int right_child = left_child + 1;
            if (right_child <= size && heap[right_child] < heap[best]) best = right_child;
            if (best == p) break;
            swap_pos(p, best);
            p = best;
        }
    };
    auto push = [&](int l, int r) {
        heap[++size] = {abs(skill[l] - skill[r]), l, r};
        pos[l] = size;
        up(size);
    };
    // 删除堆中下标 p 处的候选
    auto erase_at = [&](int p) {
        swap_pos(p, size);
        --size;
        pos[heap[size + 1].left] = -1; // heap[size+1] 就是要删除的候选
        if (p <= size) {
            down(p);
            up(p);
        }
    };
    auto pop_top = [&]() {
        pos[heap[1].left] = -1;
        swap_pos(1, size);
        --size;
        if (size >= 1) down(1);
    };

    for (int i = 0; i + 1 < n; i++) {
        if (gender[i] != gender[i + 1]) push(i, i + 1);
    }

    vector<pair<int, int>> answer;
    while (size > 0) {
        int l = heap[1].left, r = heap[1].right;
        answer.emplace_back(l + 1, r + 1);
        pop_top();

        int nl = prev[l], nr = nxt[r];
        if (nl >= 0) nxt[nl] = nr;
        if (nr >= 0) prev[nr] = nl;

        // 旧候选 (r, nxt[r]) 失效，从堆中删除
        if (nr >= 0 && pos[r] != -1) {
            erase_at(pos[r]);
        }

        // 旧候选 (prev[l], l)：新候选 (nl, nr) 左端点相同，原地覆盖或删除
        if (nl >= 0 && pos[nl] != -1) {
            if (nr >= 0 && gender[nl] != gender[nr]) {
                int p = pos[nl];
                heap[p] = {abs(skill[nl] - skill[nr]), nl, nr};
                down(p);
                up(p);
            } else {
                erase_at(pos[nl]);
            }
        } else if (nl >= 0 && nr >= 0 && gender[nl] != gender[nr]) {
            // (nl, l) 是同性对从未入堆，新候选需要直接插入
            push(nl, nr);
        }
    }

    cout << answer.size() << "\n";
    for (auto [a, b] : answer) {
        cout << a << " " << b << "\n";
    }

    return 0;
}
