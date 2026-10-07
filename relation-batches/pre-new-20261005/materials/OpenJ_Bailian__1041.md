   1| # OpenJ_Bailian 1041 John&#39;s trip
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/OpenJ_Bailian/1041/index.md`（内容哈希 40c3adbaa86ca483）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及+/提高；标签：['欧拉路']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ## 题目核心解析
  12| 
  13| 1. 问题转化：欧拉回路的判定与构造
  14| 
  15| 题目要求“每条街只走一次”且“最后回到家里”，这直接对应图论中的 欧拉回路 定义。
  16| 
  17| - **节点**：路口 (Junctions, $1 \dots M$)。
  18| - **边**：街道 (Streets, $1 \dots N$)。
  19| - **图类型**：无向多重图（两点之间可能有重边）。
  20| - 存在的充要条件
  21| 
  22| 对于无向图，存在欧拉回路必须满足两个条件：
  23| 
  24| 1. **连通性**：所有度数大于 0 的点必须连通（题目保证数据基本连通，或者我们只跑有边的连通块）。
  25| 2. **度数限制**：**所有**节点的度数必须是 **偶数**。
  26|    - 如果发现任何一个点的度数是奇数，直接输出 "Round trip does not exist."。
  27| 3. 难点：字典序最小 (Lexicographically Smallest)
  28| 
  29| 题目要求：“如果有由多条这样的路线，输出序号序列字典序最小的那条。”
  30| 
  31| 这意味着：
  32| 
  33| - 当我们站在路口 $u$，有做多条路 $e_1, e_2, \dots$ 可以走时，我们必须优先选择 **街道编号 (Street ID)** 最小的那条路。
  34| - **解决策略**：在存储图（邻接表）时，对每个节点连接的边，按 **街道编号** 进行升序排序。在 DFS 遍历时，自然就会先走小编号的边。
  35| - 算法选择：Hierholzer 算法 (变种)
  36| 
  37| 为了处理死胡同并正确回溯，我们使用 Hierholzer 算法的思想（DFS 后序遍历入栈）：
  38| 
  39| - 从起点开始 DFS。
  40| - 在当前节点 $u$，贪心地选择当前可用的、编号最小的边 $(u, v)$ 走向 $v$。
  41| - **删除**这条边（标记为已访问），递归搜索 $v$。
  42| - **关键点**：当从 $v$ 回溯回来（即 $u$ 的所有出边都走完了）时，将这条边的编号 **压入栈**。
  43| - 最后，栈中的序列就是路径的 **逆序**。输出时将栈弹空即可。
  44| 
  45| ------
  46| 
  47| ## 代码
  48| 
  49| 
  50| 
  51| ```cpp
  52| /**
  53|  * Author by Rainboy
  54|  * Problem: POJ 1041 / OpenJ_Bailian 1041 John's trip
  55|  * Analysis: 
  56|  * 1. 欧拉回路判定：所有点度数为偶数。
  57|  * 2. 字典序最小：邻接表排序 + 贪心 DFS。
  58|  * 3. 算法：Hierholzer 算法 (后序遍历入栈)。
  59|  */
  60| 
  61| #include <iostream>
  62| #include <vector>
  63| #include <algorithm>
  64| #include <cstring>
  65| #include <stack>
  66| 
  67| using namespace std;
  68| 
  69| const int MAXN = 2000; // 街道最大数量 1995
  70| const int MAXM = 50;   // 路口最大编号 44
  71| 
  72| struct Edge {
  73|     int to;     // 目标路口
  74|     int id;     // 街道编号 (Z)
  75|     
  76|     // 重载小于号，用于排序，保证优先走编号小的边
  77|     bool operator<(const Edge& other) const {
  78|         return id < other.id;
  79|     }
  80| };
  81| 
  82| // 邻接表：adj[u] 存从 u 出发的所有边
  83| vector<Edge> adj[MAXM];
  84| // 度数数组
  85| int deg[MAXM];
  86| // 标记街道是否被访问过 (根据街道编号 Z 标记)
  87| bool vis[MAXN];
  88| // 结果栈
  89| stack<int> ans;
  90| 
  91| // 边的总数，当前最大路口编号
  92| int max_street_num;
  93| int max_node_num;
  94| 
  95| void init() {
  96|     for(int i = 0; i < MAXM; ++i) adj[i].clear();
  97|     memset(deg, 0, sizeof(deg));
  98|     memset(vis, 0, sizeof(vis));
  99|     max_street_num = 0;
 100|     max_node_num = 0;
 101| }
 102| 
 103| // Hierholzer 算法核心 DFS
 104| void dfs(int u) {
 105|     // 遍历 u 的所有出边
 106|     // 注意：这里不能用简单的 for(int i=0...) 索引遍历
 107|     // 因为边会动态被标记 visited，我们需要找“下一条可用的边”
 108|     // 在实际实现中，为了效率，通常不删除 vector 元素，而是检查 vis 标记
 109|     for (int i = 0; i < adj[u].size(); ++i) {
 110|         int edge_id = adj[u][i].id;
 111|         int v = adj[u][i].to;
 112| 
 113|         // 如果这条街没走过
 114|         if (!vis[edge_id]) {
 115|             vis[edge_id] = true; // 标记这条街已走
 116|             dfs(v);              // 递归走向下一个路口
 117|             
 118|             // 【关键】回溯时入栈
 119|             // 此时记录的是 edge_id
 120|             ans.push(edge_id);
 121|         }
 122|     }
 123| }
 124| 
 125| int main() {
 126|     int x, y, z;
 127|     while (cin >> x >> y) {
 128|         if (x == 0 && y == 0) break;
 129|         
 130|         init();
 131|         cin >> z;
 132|         
 133|         // 读取第一条边，以此确定起点
 134|         // 题目说：住在输入中第一个出现的...所连接的路口
 135|         // 通常理解为：Edge 1 连接的 min(u, v) 或者直接就是输入的第一个 x, y
 136|         // 本题为了字典序最小，且起点未明确固定，通常取整个图中 最小街道编号 所连接的 编号较小的路口
 137|         // 但根据题意 "John lives at ... input first ... street", 我们记录起始边的信息
 138|         int start_node = min(x, y); 
 139|         
 140|         // 记录第一条边
 141|         max_node_num = max(max_node_num, max(x, y));
 142|         deg[x]++; deg[y]++;
 143|         adj[x].push_back({y, z});
 144|         adj[y].push_back({x, z});
 145|         
 146|         // 继续读取直到遇到 0 0 (本题是一个数据块以 0 0 结束输入，不是整个程序)
 147|         // 修正：POJ 1041 的输入格式是每行 x y z，直到 x=0 y=0 结束一个 Case
 148|         // 所以上面的 while 需要调整为处理 block
 149|         
 150|         // 重新组织输入逻辑：
 151|         // 此时已经读了第一行 x, y, z
 152|         while (true) {
 153|             int u, v, w;
 154|             cin >> u >> v;
 155|             if (u == 0 && v == 0) break; // 当前 Case 结束
 156|             cin >> w;
 157|             
 158|             deg[u]++; deg[v]++;
 159|             adj[u].push_back({v, w});
 160|             adj[v].push_back({u, w});
 161|             max_node_num = max(max_node_num, max(u, v));
 162|         }
 163|         
 164|         // 1. 检查度数 (欧拉回路判定)
 165|         bool possible = true;
 166|         for (int i = 1; i <= max_node_num; ++i) {
 167|             if (deg[i] % 2 != 0) {
 168|                 possible = false;
 169|                 break;
 170|             }
 171|         }
 172|         
 173|         if (!possible) {
 174|             cout << "Round trip does not exist." << endl;
 175|             continue;
 176|         }
 177|         
 178|         // 2. 对邻接表进行排序，保证字典序最小
 179|         for (int i = 1; i <= max_node_num; ++i) {
 180|             sort(adj[i]
 181| 
 182| ## 代码位置
 183| - `problems/OpenJ_Bailian/1041/1.cpp`