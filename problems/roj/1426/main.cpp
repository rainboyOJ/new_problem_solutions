/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:22
 * update_at: 2026-10-05 23:22
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 505;

struct Game {
    int t; // 期限
    int w; // 扣款
} a[MAXN];

bool cmp(Game x, Game y) {
    return x.t < y.t;
}

int n;
ll m;
int heap[MAXN]; // 小根堆，存已安排游戏的扣款
int heap_size;  // 堆当前大小

void push(int x) {
    heap[++heap_size] = x;
    int i = heap_size;
    while (i > 1 && heap[i] < heap[i / 2]) {
        swap(heap[i], heap[i / 2]);
        i /= 2;
    }
}

int pop() {
    int res = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (i * 2 <= heap_size) {
        int son = i * 2;
        if (son + 1 <= heap_size && heap[son + 1] < heap[son])
            son++;
        if (heap[son] < heap[i]) {
            swap(heap[son], heap[i]);
            i = son;
        } else break;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].t;
    for (int i = 1; i <= n; ++i) cin >> a[i].w;

    sort(a + 1, a + n + 1, cmp); // 按期限从小到大排序

    ll sum_w = 0; // 全部扣款总和
    for (int i = 1; i <= n; ++i) {
        sum_w += a[i].w;
        push(a[i].w);
        if (heap_size > a[i].t) { // 已安排数超过当前期限，淘汰扣款最小的
            pop();
        }
    }

    ll keep = 0; // 堆中保住的扣款总和
    for (int i = 1; i <= heap_size; ++i) keep += heap[i];

    cout << m - (sum_w - keep) << "\n";
    return 0;
}
