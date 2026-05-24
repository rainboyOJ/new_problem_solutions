#include <bits/stdc++.h>
using namespace std;

struct Pear {
    int A, B;
    long long V;  // V = C1*A + C2*B
    int id;
};

class BIT {
private:
    vector<int> tree;
    int n;
    
public:
    BIT(int size) : n(size) {
        tree.assign(n + 1, 0);
    }
    
    void add(int idx, int val) {
        for (int i = idx; i <= n; i += i & (-i)) {
            tree[i] += val;
        }
    }
    
    int query(int idx) {
        int sum = 0;
        for (int i = idx; i > 0; i -= i & (-i)) {
            sum += tree[i];
        }
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    int C1, C2, C3;
    cin >> C1 >> C2 >> C3;
    
    vector<Pear> pears(N);
    for (int i = 0; i < N; i++) {
        cin >> pears[i].A >> pears[i].B;
        pears[i].V = 1LL * C1 * pears[i].A + 1LL * C2 * pears[i].B;
        pears[i].id = i;
    }
    
    // 收集所有可能的V值进行离散化
    vector<long long> allV;
    for (int i = 0; i < N; i++) {
        allV.push_back(pears[i].V);
        // 还需要加上所有可能的threshold值
        for (int j = 0; j < N; j++) {
            long long threshold = C3 + 1LL * C1 * pears[i].A + 1LL * C2 * pears[j].B;
            allV.push_back(threshold);
        }
    }
    
    sort(allV.begin(), allV.end());
    allV.erase(unique(allV.begin(), allV.end()), allV.end());
    
    // 获取离散化后的排名
    auto getRank = [&](long long val) -> int {
        return (int)(lower_bound(allV.begin(), allV.end(), val) - allV.begin() + 1);
    };
    
    // 获取小于等于val的最大离散值的排名
    auto getMaxRank = [&](long long val) -> int {
        auto it = upper_bound(allV.begin(), allV.end(), val);
        if (it == allV.begin()) return 0;
        --it;
        return (int)(it - allV.begin() + 1);
    };
    
    int maxCount = 0;
    
    // 按A排序
    sort(pears.begin(), pears.end(), [](const Pear& a, const Pear& b) {
        return a.A < b.A;
    });
    
    // 外层循环：枚举A0
    for (int i = 0; i < N; i++) {
        int A0 = pears[i].A;
        
        // 收集候选梨子（A >= A0）
        vector<Pear> candidates;
        for (int j = i; j < N; j++) {
            candidates.push_back(pears[j]);
        }
        
        // 按B排序
        sort(candidates.begin(), candidates.end(), [](const Pear& a, const Pear& b) {
            return a.B < b.B;
        });
        
        // 初始化BIT，将所有候选梨子加入
        BIT bit(allV.size());
        for (const auto& pear : candidates) {
            bit.add(getRank(pear.V), 1);
        }
        
        // 内层循环：枚举B0
        for (int k = 0; k < candidates.size(); k++) {
            int B0 = candidates[k].B;
            long long threshold = C3 + 1LL * C1 * A0 + 1LL * C2 * B0;
            
            // 查询满足条件的梨子数量
            int count = bit.query(getMaxRank(threshold));
            maxCount = max(maxCount, count);
            
            // 移除当前梨子（因为下一个B0会更大，这个梨子不能再选）
            bit.add(getRank(candidates[k].V), -1);
        }
    }
    
    cout << maxCount << endl;
    return 0;
}