/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:52
 * update_at: 2026-10-07 00:53
 */
// main-stl.cpp：这是 STL 写法，用 list<int> 保存队伍，用 list<int>::iterator pos[] 记住每个同学在链表中的位置。
// 插入到 k 左边就把 pos[k] 交给 insert，插入到右边先 ++it；删除用 erase(pos[x])。
// 迭代器一直指向那个节点，插入/删除都不会让它失效，所以三种操作都是 O(1)，整体 O(N+M)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n, m;
list<int> line;                 // line 保存队伍，从左到右就是链表从头到尾的顺序
list<int>::iterator pos[MAXN];  // pos[x] 是编号 x 的同学在链表中的位置（迭代器）
bool removed[MAXN];             // removed[x] = true 表示编号 x 已出队，重复指令要忽略

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 1 号同学先入队，此时链表里只有他一个人
    line.push_back(1);
    pos[1] = line.begin();

    // 2~n 号同学依次插入到 k 号同学的左边或右边
    for (int i = 2; i <= n; i++) {
        int k, p;
        cin >> k >> p;

        if (p == 0) {
            // 插到 k 的左边：把 i 插在 pos[k] 这个位置之前，insert 返回新节点的迭代器
            pos[i] = line.insert(pos[k], i);
        } else {
            // 插到 k 的右边：先把游标后移一格到 k 的下一个节点，再在它之前插入 i
            list<int>::iterator it = pos[k];
            ++it;
            pos[i] = line.insert(it, i);
        }
    }

    // m 次删除，每次都是已知节点位置的 O(1) 删除
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if (removed[x]) {
            continue; // x 已经不在队列中，忽略这条指令
        }
        removed[x] = true;
        line.erase(pos[x]); // 删除 pos[x] 指向的节点，它的前后邻居自动接上
    }

    // 链表本身就是从左到右的顺序，用迭代器从头到尾输出
    for (list<int>::iterator it = line.begin(); it != line.end(); ++it) {
        cout << *it << ' ';
    }
    cout << '\n';

    return 0;
}
