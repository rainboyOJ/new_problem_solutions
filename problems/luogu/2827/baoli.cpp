#include <iostream>
#include <vector>
#include <algorithm> // 用于 max_element
#include <cmath>     // 用于 floor

using namespace std;

int main() {
    // 优化一下输入输出，虽然暴力算法本身慢，但输入习惯要好
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;

    // 使用 vector 存储当前所有的蚯蚓长度
    vector<int> worms;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        worms.push_back(temp);
    }

    // --- 模拟开始，循环 m 秒 ---
    for (int i = 1; i <= m; i++) {
        
        // [步骤 1: 找出最大的蚯蚓]
        // max_element 会遍历整个 vector 找到最大值的迭代器
        auto max_it = max_element(worms.begin(), worms.end());
        int max_val = *max_it; // 取出最大值的数值

        // [步骤 2: 将其从队伍中取出/移除]
        // 这一步非常慢，因为 vector 删除元素需要移动后面的所有数据
        worms.erase(max_it);

        // 按题目要求，每隔 t 秒输出一次被切断蚯蚓的长度
        if (i % t == 0) {
            cout << max_val << " ";
        }

        // [步骤 3: 这里的代码完成了 "其余蚯蚓增加 q"]
        // 注意：此时最大的那只已经被 erase 移除了，新的两只还没放进去。
        // 所以现在 vector 里剩下的，就是所有 "其余的蚯蚓"。
        for (int &w : worms) {
            w += q; 
        }

        // [步骤 4: 切割产生两只新蚯蚓]
        // 计算长度，注意整数运算
        // 题目公式：长度1 = floor(x * u / v)
        long long len1_long = (long long)max_val * u / v; 
        int len1 = (int)len1_long;
        int len2 = max_val - len1;

        // [步骤 5: 将新蚯蚓放回队伍]
        // 题目说：新产生的两只蚯蚓这一秒不增加长度，所以它们是在上面的 for 循环之后加入的
        worms.push_back(len1);
        worms.push_back(len2);
    }

    cout << endl; // 第一行输出结束

    // [步骤 6: 输出最后的结果]
    // 题目要求输出第 m 秒结束后，所有蚯蚓长度（从大到小）
    // 暴力解法直接排序即可
    sort(worms.begin(), worms.end(), greater<int>());

    for (int i = 0; i < worms.size(); i++) {
        if ((i + 1) % t == 0) {
            cout << worms[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
