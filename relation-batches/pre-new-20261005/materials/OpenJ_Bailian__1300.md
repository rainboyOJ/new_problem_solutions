   1| # OpenJ_Bailian 1300 Door Man
   2| 
   3| > 原文摘录，非模型摘要。来源：`problems/OpenJ_Bailian/1300/index.md`（内容哈希 6d1b5028a05b6853）。
   4| > 摘录可能在 4000 字符处截断；作结论前必须能补读原文全文。
   5| 
   6| ## 元信息（frontmatter 摘录）
   7| - 难度：普及/提高-；标签：['欧拉路']
   8| 
   9| ## 题目解析（原文摘录）
  10| 
  11| ## 题目解析
  12| 
  13| 
  14| 这是一个非常经典的 **欧拉回路 / 欧拉路径 (Eulerian Path/Circuit)** 判定题目。
  15| 
  16| ## 题目核心解析
  17| 
  18| **1. 问题模型化**
  19| 
  20| - **房间**：看作图的 **节点 (Vertex)**。
  21| - **打开的门**：看作图的 **边 (Edge)**。
  22| - **规则翻译**：
  23|   - “穿过门后立即关上” $\rightarrow$ **每条边只能走一次**。
  24|   - “不能打开关闭的门” $\rightarrow$ **不能重复走边**。
  25|   - “关闭所有打开的门” $\rightarrow$ **遍历图中所有的边**。
  26|   - “起点是 M，终点必须是 0” $\rightarrow$ **寻找一条从 M 到 0 的欧拉路径**。
  27| - 判定条件
  28| 
  29| 这是一个 无向图 的欧拉路径判定问题。
  30| 
  31| - 基本条件（连通性）：
  32| 
  33|   所有有门的房间（度数 $>0$ 的节点）必须连通。如果图是分裂的（比如房间 0-1 有门，房间 3-4 有门，但 1 和 3 没连通），管家不可能关上所有的门。(题目隐含暗示通常是连通的，但严谨的代码需要检查，或者只检查度数条件在某些弱数据下也能过，不过 POJ 1300 数据比较强，建议判连通)。
  34| 
  35| - 核心条件（度数奇偶性）：
  36| 
  37|   设 $deg[i]$ 为节点 $i$ 的度数（连接的门的数量）。
  38| 
  39|   - **情况 A：起点 M == 0**
  40|     - 这意味着起点和终点重合。
  41|     - 我们需要找的是 **欧拉回路 (Eulerian Circuit)**。
  42|     - **判定条件**：**所有节点的度数必须是偶数**。
  43|   - **情况 B：起点 M != 0**
  44|     - 这意味着起点和终点不同。
  45|     - 我们需要找的是 **欧拉路径 (Eulerian Path)**。
  46|     - **判定条件**：
  47|       1. **起点 M** 的度数必须是 **奇数**。
  48|       2. **终点 0** 的度数必须是 **奇数**。
  49|       3. **其他所有节点** 的度数必须是 **偶数**。
  50| 
  51| - 输入处理上的坑
  52| 
  53| 这个题目的输入格式稍微有点“古老”，需要注意：
  54| 
  55| - 它是多组数据，以 `START M N` 开始，`END` 结束一组，`ENDOFINPUT` 结束所有。
  56| - 读取边的列表时，题目说：“第 $i$ 行列出的是房间 $i$ 连接到的**编号比它大**的房间”。
  57|   - 这意味着如果我们读到 `Room 0: 1 5`，我们连边 `(0, 1)` 和 `(0, 5)`。
  58|   - 不需要担心重复加边。
  59|   - 需要使用 `getline` 和 `stringstream` 来处理每一行的输入，因为每行的数字个数不确定。
  60| 
  61| ------
  62| 
  63| ## 代码
  64| 
  65| 
  66| ```cpp
  67| /**
  68|  * Author by Rainboy
  69|  * Problem: POJ 1300 Door Man
  70|  * Analysis: 
  71|  * 1. 这是一个无向图欧拉路径/回路判定问题。
  72|  * 2. 目标：判断是否存在从起点 M 走到终点 0 的路径，且经过所有边恰好一次。
  73|  * 3. 判定逻辑：
  74|  * - 首先：图必须是连通的（忽略孤立点）。
  75|  * - 情况1 (M == 0): 需要欧拉回路 -> 所有点度数为偶数。
  76|  * - 情况2 (M != 0): 需要欧拉路径 -> deg[M]和deg[0]为奇数，其余为偶数。
  77|  */
  78| 
  79| #include <iostream>
  80| #include <vector>
  81| #include <string>
  82| #include <sstream>
  83| #include <cstring>
  84| #include <algorithm>
  85| 
  86| using namespace std;
  87| 
  88| const int MAXN = 25; // 题目说 N <= 20
  89| 
  90| int start_node, n; // 起点M，房间总数N
  91| int deg[MAXN];     // 度数数组
  92| int edge_count;    // 总边数（门的数量）
  93| 
  94| // 并查集用于判连通
  95| struct DSU {
  96|     int fa[MAXN];
  97|     void init(int n) {
  98|         for(int i = 0; i < n; i++) fa[i] = i;
  99|     }
 100|     int find(int x) {
 101|         return fa[x] == x ? x : fa[x] = find(fa[x]);
 102|     }
 103|     void merge(int u, int v) {
 104|         int fu = find(u);
 105|         int fv = find(v);
 106|         if (fu != fv) fa[fu] = fv;
 107|     }
 108| } dsu;
 109| 
 110| void solve() {
 111|     string line;
 112|     // 读取 START M N 中的 M 和 N
 113|     // 此时 cin 已经在 main 函数读取了 "START"
 114|     cin >> start_node >> n;
 115|     
 116|     // 清空状态
 117|     memset(deg, 0, sizeof(deg));
 118|     edge_count = 0;
 119|     dsu.init(n);
 120|     
 121|     // 消耗掉 START 行末尾的换行符
 122|     getline(cin, line); 
 123| 
 124|     // 读取 N 行，每行代表 Room i 连接到的更高编号房间
 125|     for (int i = 0; i < n; i++) {
 126|         getline(cin, line); // 读取整行
 127|         if (line.empty()) continue;
 128| 
 129|         stringstream ss(line);
 130|         int target;
 131|         while (ss >> target) {
 132|             // 连边 i <-> target
 133|             deg[i]++;
 134|             deg[target]++;
 135|             edge_count++;
 136|             dsu.merge(i, target);
 137|         }
 138|     }
 139| 
 140|     // 读取该组数据的结束标记 "END"
 141|     string dummy;
 142|     cin >> dummy; 
 143| 
 144|     // === 核心判定逻辑 ===
 145| 
 146|     // 1. 连通性检查
 147|     // 找到第一个有度数的点作为基准 root
 148|     int root = -1;
 149|     for (int i = 0; i < n; i++) {
 150|         if (deg[i] > 0) {
 151|             if (root == -1) root = dsu.find(i);
 152|             else if (dsu.find(i) != root) {
 153|                 // 发现有度数的点不在同一个连通分量，说明图不连通
 154|                 cout << "NO" << endl;
 155|                 return;
 156|             }
 157|         }
 158|     }
 159|     
 160|     // 特判：如果没有边，且起点就是终点(0)，且start_node==0，算YES 0？
 161|     // 题目 implied "non-empty series"，通常会有门。
 162|     // 如果没有门，M=0时在自己房间不需要动，M!=0时过不去。
 163|     if (edge_count == 0) {
 164|         if (start_node == 0) cout << "YES 0" << endl;
 165|         else cout << "NO" << endl;
 166|         return;
 167|     }
 168|     
 169|     // 还需要检查起点是否在连通分量里 (防止起点是孤立点，虽然没门的情况上面排除了)
 170|     // 但如果有门，起点必须能通向这些门
 171|     if (deg[start_node] == 0) {
 172|         cout << "NO" << endl;
 173|         return;
 174|     }
 175| 
 176| 
 177|     // 2. 度数检查
 178|     bool possible = false;
 179| 
 180|     if (start_node == 0) {
 181|         // 情况 A: 欧拉回路 (起点=0, 终点=0)
 182|         // 要求：所有点度数均为偶数
 183|         possible = true;
 184|         for (int i = 0; i < n; i++) {
 185|             if (deg[i] % 2 != 0) {
 186|                 possible = false;
 187|                 break;
 188|             }
 189|         }
 190|     } else {
 191|         // 情况 B: 欧拉路径 (起点=M, 终点=0)
 192|         // 要求：起点和终点度数为奇数，其他为偶数
 193|       
 194| 
 195| ## 代码位置
 196| - （无）