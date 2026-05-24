---
oj: "OpenJ_Bailian"
problem_id: "1041"
title: "John&#39;s trip"
date: 2026-01-08 17:11
toc: true
tags: ["欧拉路"]
desc: "字典序最小欧拉路"
source: https://vjudge.net/problem/OpenJ_Bailian-1041#author=GPT_zh
---

[[TOC]]

> 模板题吧 字典序最小欧拉路

这是一道非常经典的 **欧拉回路 (Eulerian Circuit)** 题目，也是考察对 Hierholzer 算法理解深度的绝佳题目。

## 题目核心解析

1. 问题转化：欧拉回路的判定与构造

题目要求“每条街只走一次”且“最后回到家里”，这直接对应图论中的 欧拉回路 定义。

- **节点**：路口 (Junctions, $1 \dots M$)。
- **边**：街道 (Streets, $1 \dots N$)。
- **图类型**：无向多重图（两点之间可能有重边）。
- 存在的充要条件

对于无向图，存在欧拉回路必须满足两个条件：

1. **连通性**：所有度数大于 0 的点必须连通（题目保证数据基本连通，或者我们只跑有边的连通块）。
2. **度数限制**：**所有**节点的度数必须是 **偶数**。
   - 如果发现任何一个点的度数是奇数，直接输出 "Round trip does not exist."。
3. 难点：字典序最小 (Lexicographically Smallest)

题目要求：“如果有由多条这样的路线，输出序号序列字典序最小的那条。”

这意味着：

- 当我们站在路口 $u$，有做多条路 $e_1, e_2, \dots$ 可以走时，我们必须优先选择 **街道编号 (Street ID)** 最小的那条路。
- **解决策略**：在存储图（邻接表）时，对每个节点连接的边，按 **街道编号** 进行升序排序。在 DFS 遍历时，自然就会先走小编号的边。
- 算法选择：Hierholzer 算法 (变种)

为了处理死胡同并正确回溯，我们使用 Hierholzer 算法的思想（DFS 后序遍历入栈）：

- 从起点开始 DFS。
- 在当前节点 $u$，贪心地选择当前可用的、编号最小的边 $(u, v)$ 走向 $v$。
- **删除**这条边（标记为已访问），递归搜索 $v$。
- **关键点**：当从 $v$ 回溯回来（即 $u$ 的所有出边都走完了）时，将这条边的编号 **压入栈**。
- 最后，栈中的序列就是路径的 **逆序**。输出时将栈弹空即可。

------

## 代码



```cpp
/**
 * Author by Rainboy
 * Problem: POJ 1041 / OpenJ_Bailian 1041 John's trip
 * Analysis: 
 * 1. 欧拉回路判定：所有点度数为偶数。
 * 2. 字典序最小：邻接表排序 + 贪心 DFS。
 * 3. 算法：Hierholzer 算法 (后序遍历入栈)。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>

using namespace std;

const int MAXN = 2000; // 街道最大数量 1995
const int MAXM = 50;   // 路口最大编号 44

struct Edge {
    int to;     // 目标路口
    int id;     // 街道编号 (Z)
    
    // 重载小于号，用于排序，保证优先走编号小的边
    bool operator<(const Edge& other) const {
        return id < other.id;
    }
};

// 邻接表：adj[u] 存从 u 出发的所有边
vector<Edge> adj[MAXM];
// 度数数组
int deg[MAXM];
// 标记街道是否被访问过 (根据街道编号 Z 标记)
bool vis[MAXN];
// 结果栈
stack<int> ans;

// 边的总数，当前最大路口编号
int max_street_num;
int max_node_num;

void init() {
    for(int i = 0; i < MAXM; ++i) adj[i].clear();
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
    max_street_num = 0;
    max_node_num = 0;
}

// Hierholzer 算法核心 DFS
void dfs(int u) {
    // 遍历 u 的所有出边
    // 注意：这里不能用简单的 for(int i=0...) 索引遍历
    // 因为边会动态被标记 visited，我们需要找“下一条可用的边”
    // 在实际实现中，为了效率，通常不删除 vector 元素，而是检查 vis 标记
    for (int i = 0; i < adj[u].size(); ++i) {
        int edge_id = adj[u][i].id;
        int v = adj[u][i].to;

        // 如果这条街没走过
        if (!vis[edge_id]) {
            vis[edge_id] = true; // 标记这条街已走
            dfs(v);              // 递归走向下一个路口
            
            // 【关键】回溯时入栈
            // 此时记录的是 edge_id
            ans.push(edge_id);
        }
    }
}

int main() {
    int x, y, z;
    while (cin >> x >> y) {
        if (x == 0 && y == 0) break;
        
        init();
        cin >> z;
        
        // 读取第一条边，以此确定起点
        // 题目说：住在输入中第一个出现的...所连接的路口
        // 通常理解为：Edge 1 连接的 min(u, v) 或者直接就是输入的第一个 x, y
        // 本题为了字典序最小，且起点未明确固定，通常取整个图中 最小街道编号 所连接的 编号较小的路口
        // 但根据题意 "John lives at ... input first ... street", 我们记录起始边的信息
        int start_node = min(x, y); 
        
        // 记录第一条边
        max_node_num = max(max_node_num, max(x, y));
        deg[x]++; deg[y]++;
        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
        
        // 继续读取直到遇到 0 0 (本题是一个数据块以 0 0 结束输入，不是整个程序)
        // 修正：POJ 1041 的输入格式是每行 x y z，直到 x=0 y=0 结束一个 Case
        // 所以上面的 while 需要调整为处理 block
        
        // 重新组织输入逻辑：
        // 此时已经读了第一行 x, y, z
        while (true) {
            int u, v, w;
            cin >> u >> v;
            if (u == 0 && v == 0) break; // 当前 Case 结束
            cin >> w;
            
            deg[u]++; deg[v]++;
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
            max_node_num = max(max_node_num, max(u, v));
        }
        
        // 1. 检查度数 (欧拉回路判定)
        bool possible = true;
        for (int i = 1; i <= max_node_num; ++i) {
            if (deg[i] % 2 != 0) {
                possible = false;
                break;
            }
        }
        
        if (!possible) {
            cout << "Round trip does not exist." << endl;
            continue;
        }
        
        // 2. 对邻接表进行排序，保证字典序最小
        for (int i = 1; i <= max_node_num; ++i) {
            sort(adj[i].begin(), adj[i].end());
        }
        
        // 3. 执行 Hierholzer DFS
        // 起点选择：题目中暗示起点是输入的第一条街道连接的较小路口
        // 实际上，为了字典序最小，我们通常从输入的第一条边涉及的节点开始
        dfs(start_node);
        
        // 4. 输出结果
        // Hierholzer 算法得到的栈是逆序的路径，出栈即为正序
        // 但注意：我们是在 dfs(v) 之后 push 的
        // 比如 1->2, 递归2, 2无路，push(1-2的id)。
        // 最后的路径是 栈顶 -> 栈底
        while (!ans.empty()) {
            cout << ans.top() << (ans.size() == 1 ? "" : " ");
            ans.pop();
        }
        cout << endl;
    }
    return 0;
}
```

## 代码中的关键逻辑解释

1. start_node = min(x, y):

   题目描述有点绕，但核心是为了保证字典序最小。既然第一条输入的边通常是编号最小的边（如果不确定，我们可以遍历一遍找最小边），那么起点大概率就在这条边上。为了字典序最小，我们在两个端点中选编号更小的那个作为起点。

2. sort(adj[i].begin(), adj[i].end()):

   这是解决“字典序最小”的核心。当我们到达路口 u 时，可能有几条街可以走。因为我们先排序了，所以 dfs 循环中第一次尝试的边一定是编号最小的。

3. 栈的使用:

   在欧拉回路中，简单的 DFS 可能会走入死胡同（比如走了一圈回到起点，但还有另一半图没走）。Hierholzer 算法通过“走投无路时才入栈”的策略，巧妙地把死胡同（子环）拼接到主路径上。

   - 后进栈的边，代表是在图中“更深”或“更晚”被遍历完的子环。
   - 因为我们是递归 `dfs(v)` **之后** 才 `push`，所以栈顶存的是最后走的那条边……不对！
   - **纠正**：Hierholzer 记录的是**顶点**序列时，倒序输出。但这里记录的是**边**。
   - 逻辑：DFS 贪心走小编号边 $\to$ 走到头回溯 $\to$ 将边入栈。
   - 因为是回溯时入栈，所以**栈底**是最先“被确定无法再延伸”的边（通常是死胡同的尽头），**栈顶**是最后回到起点的边。
   - **等等！** 这里有个常见的思维陷阱。对于边序列，Hierholzer 产生的顺序也是逆序的。
   - 让我们模拟一下：A-B (1), B-A (2)。
     - DFS(A) -> 走 1 -> DFS(B) -> 走 2 -> DFS(A) -> 无路 -> Push(2) -> 回溯 -> Push(1)。
     - 栈：2, 1 (栈顶是2)。
     - 出栈：2, 1。
     - 路径是 1, 2。
     - **结论**：栈中存储的是逆序，所以 `top()` 到 `empty()` 输出就是正确的顺序（2, 1? 不对，例子里路径是1 then 2）。
     - **修正**：在上面的简单环例子中，路径应该是 1 然后 2。栈里是 {2, 1}。从栈顶弹出来是 2, 1。这反了！
     - **正确做法**：Hierholzer 算法得到的栈，**从栈顶到栈底** 是 **逆序** 的路径。所以应该先把栈里的元素倒到一个 vector 里，或者直接从栈底读（但这不支持）。或者... 难道代码里的 `ans.top()` 输出是错的？
     - **再思考**：标准 Hierholzer 是 `path.push_front(u)`。这里我们用 Stack，`push` 相当于 `push_front`。所以 Stack 从 Top 到 Bottom 存的是正序路径？
     - **最终确认**：DFS 回溯入栈 $\to$ 栈底是第一条被“走死”的边（最后那段路），栈顶是第一条出发的边（因为最后才回溯到起点）。
     - **验证**：A->B(1), B->C(2), C->A(3).
       - Start A.
       - Walk 1. Recurse B.
       - Walk 2. Recurse C.
       - Walk 3. Recurse A. (Stuck) -> Push 3. Return.
       - Push 2. Return.
       - Push 1. Return.
       - Stack: [Bottom] 3, 2, 1 [Top].
       - Pop: 1, 2, 3. **正确！**
       - 所以代码中的输出逻辑 `while(!ans.empty()) { cout << ans.top()... }` 是完全正确的。

这个题目在“图论”章节的表格中，应当归类为：

| **题面特征**                 | **可能的思考方向 (触发器)** | **经典/备注**             | **经典题目**             |
| ---------------------------- | --------------------------- | ------------------------- | ------------------------ |
| **"每条街走一次且回到起点"** | **欧拉回路**                | 判定度数全偶 + Hierholzer | **POJ 1041 John's trip** |
