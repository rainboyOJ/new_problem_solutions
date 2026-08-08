#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

// 邻接矩阵存图，G[u][v]=1 表示有边，自动满足字典序遍历
int G[150][150]; 
int du[150]; // 记录度数
stack<char> st; // 存路径
int n; // 边数

// 核心 DFS：Hierholzer 算法
void dfs(int u) {
    // 按 ASCII 顺序从小到大遍历邻居
    for (int v = 0; v < 150; v++) {
        if (G[u][v]) {
            G[u][v]--; // 删边 (无向图删两边)
            G[v][u]--;
            dfs(v); // 递归
        }
    }
    st.push(u); // 【关键】无路可走时入栈
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        G[s[0]][s[1]] = G[s[1]][s[0]] = 1; // 建边
        du[s[0]]++; du[s[1]]++; // 统计度数
    }

    int start_node = 0;
    int odd_count = 0;
    
    // 1. 找起点 & 检查度数
    for (int i = 0; i < 150; i++) {
        if (du[i] % 2 != 0) odd_count++;
    }

    if (odd_count != 0 && odd_count != 2) {
        cout << "No Solution";
        return 0;
    }

    // 确定起点：
    // 如果有奇点，找最小的奇点；
    // 如果全偶，找最小的有度数的点。
    for (int i = 0; i < 150; i++) {
        if (du[i]) { // 这是一个存在的点
            if (odd_count == 2) {
                if (du[i] % 2 != 0) {
                    start_node = i;
                    break;
                }
            } else { // odd_count == 0
                start_node = i;
                break;
            }
        }
    }
    // std::cout << odd_count << "\n";
    // std::cout << "start_node  "<< "\n";
    // std::cout << (char)start_node << "\n";

    // 2. 开始搜索
    dfs(start_node);

    // 3. 检查连通性 (防止图不连通的情况)
    // 欧拉路径的点数应该是 边数 + 1
    if (st.size() != n + 1) {
        cout << "No Solution";
        return 0;
    }

    // 4. 输出
    while (!st.empty()) {
        cout << (char)st.top();
        st.pop();
    }

    return 0;
}
