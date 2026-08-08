#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main() {
    string pre, post;
    cin >> pre >> post;

    long long ans = 1;
    
    // 遍历前序字符串，注意范围是 0 到 length-2
    // 因为我们要访问 pre[i] 和 pre[i+1]
    for (int i = 0; i < pre.length() - 1; i++) {
        char root = pre[i];
        char child = pre[i+1];
        
        // 在后序遍历中找到 root 和 child 的位置
        // 实际上我们只需要判断：在 post 中，child 是否紧挨在 root 之前
        
        // 找到 root 在 post 中的位置
        int rootIdx = post.find(root);
        
        // 找到 child 在 post 中的位置
        int childIdx = post.find(child);
        
        // 如果 child 正好在 root 的前一位
        if (rootIdx == childIdx + 1) {
            ans *= 2;
        }
    }

    cout << ans << endl;

    return 0;
}
