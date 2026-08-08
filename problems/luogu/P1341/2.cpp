#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

int G[150][150]; 
int du[150]; 
stack<char> st; 
int n; 

void dfs(int u) {
    for (int v = 0; v < 150; v++) {
        // 这里必须判断 G[u][v] > 0，防止逻辑错误访问到负数（虽然改了删边逻辑后一般不会）
        if (G[u][v] > 0) {
            G[u][v]--; 
            // 【修复点】如果是自环(u==v)，只减一次；否则两边都减
            if (u != v) G[v][u]--; 
            
            dfs(v); 
        }
    }
    st.push(u); 
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        int u = s[0];
        int v = s[1];
        // 建议使用 ++ 支持多重图（尽管本题说各不相同，这样写更稳健）
        G[u][v]++; 
        if (u != v) G[v][u]++; 
        
        du[u]++; 
        du[v]++; 
    }

    int start_node = 0;
    int odd_count = 0;
    
    // 寻找奇点
    for (int i = 0; i < 150; i++) {
        if (du[i] % 2 != 0) odd_count++;
    }

    // 欧拉路径存在条件：奇点数为 0 或 2
    if (odd_count != 0 && odd_count != 2) {
        cout << "No Solution";
        return 0;
    }

    // 确定起点
    // 策略：
    // 1. 如果有奇点，起点必须是奇点中 ASCII 较小的那个。
    // 2. 如果全是偶点，起点是所有有度数的点中 ASCII 最小的。
    for (int i = 0; i < 150; i++) {
        if (du[i] > 0) { // 必须是图中的点
            if (odd_count == 2) {
                if (du[i] % 2 != 0) {
                    start_node = i;
                    break; // 找到第一个奇点就是最小的（因为从小到大遍历）
                }
            } else { // odd_count == 0
                start_node = i;
                break; // 找到第一个有点就是最小的
            }
        }
    }

    dfs(start_node);

    // 检查是否走完了所有的边 (路径点数 = 边数 + 1)
    if (st.size() != n + 1) {
        cout << "No Solution";
        return 0;
    }

    while (!st.empty()) {
        cout << (char)st.top();
        st.pop();
    }

    return 0;
}
