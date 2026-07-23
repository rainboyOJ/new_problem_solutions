# 前置知识：每个单词按字典序输入，保证前缀一定在前面出现
# 用字典树，插入时统计路径上遇到几个已结束的单词（即前缀）
import sys

data = sys.stdin.buffer.read().split()
n = int(data[0])
words = [w.decode() for w in data[1:]]

trie = {}  # 根节点
ans = 1

for w in words:
    node = trie
    chain = 0

    # 沿着 w 的每个字符在字典树中往下走
    for ch in w:
        if ch not in node:
            node[ch] = {}  # 新建子节点
        node = node[ch]

        # 路过的节点如果是某个已插入单词的结尾，说明这个单词是 w 的前缀
        if '#' in node:
            chain += 1

    # 当前单词自己也算进去
    chain += 1

    # 标记当前单词的结尾
    node['#'] = True

    ans = max(ans, chain)

print(ans)
