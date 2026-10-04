/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:05
 * update_at: 2026-10-04 22:05
 */

#include <iostream>

// 要输出的目标字符串：Hello 和 World 之间只有一个英文逗号，逗号后和感叹号前都没有空格
const char *ANSWER = "Hello,World!";

int main() {
    std::cout << ANSWER << std::endl; // 输出一行并换行，与评测数据逐字节一致
    return 0;
}
