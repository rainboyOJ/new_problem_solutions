import sys
from array import array

data = sys.stdin.buffer.read().split()
n = int(data[0])
color = array("i", [0])
color.extend(map(int, data[1 : n + 1]))

# 链式前向星存树：head[u] 是 u 的第一条出边，to/nxt 用 -1 表示空。
head = array("i", [-1]) * (n + 1)
to = array("i", [0]) * (2 * n - 2)
nxt = array("i", [0]) * (2 * n - 2)
edge_cnt = 0
pos = n + 1
for _ in range(n - 1):
    u = int(data[pos])
    v = int(data[pos + 1])
    pos += 2
    to[edge_cnt] = v
    nxt[edge_cnt] = head[u]
    head[u] = edge_cnt
    edge_cnt += 1
    to[edge_cnt] = u
    nxt[edge_cnt] = head[v]
    head[v] = edge_cnt
    edge_cnt += 1

total_cnt = array("i", [0]) * (n + 1)
first_node = array("i", [0]) * (n + 1)
for i in range(1, n + 1):
    c = color[i]
    total_cnt[c] += 1
    if first_node[c] == 0:
        first_node[c] = i

parent = array("i", [0]) * (n + 1)
subtree = array("i", [0]) * (n + 1)
done_cnt = array("i", [0]) * (n + 1)       # done_cnt[c]：颜色 c 已处理完的节点数
leaf_cnt = array("i", [0]) * (n + 1)       # leaf_cnt[c]：颜色 c 已找到的端点个数
too_many = array("i", [0]) * (n + 1)       # too_many[c]：分叉方向 >= 3，答案 0
side_first = array("q", [0]) * (n + 1)     # 第一个端点的外侧连通块大小
side_second = array("q", [0]) * (n + 1)    # 第二个端点的外侧连通块大小
answer = array("q", [0]) * (n + 1)

# 显式栈迭代 DFS：等价于递归「进入 u -> 依次处理儿子 -> 离开 u」。
# 树可能退化成深度 10^6 的链，递归会爆栈，这里统一用迭代写法。
st_u = [1]
st_edge = [head[1]]
st_sub = [1]
st_same = [1]
st_positive = [0]
st_only = [0]
st_before = [0]
parent[1] = 0

while st_u:
    u = st_u[-1]
    e = st_edge[-1]
    if e != -1:
        st_edge[-1] = nxt[e]
        v = to[e]
        if v == parent[u]:
            continue
        parent[v] = u
        st_before[-1] = done_cnt[color[u]]  # 进入儿子前的快照
        st_u.append(v)
        st_edge.append(head[v])
        st_sub.append(1)
        st_same.append(1)
        st_positive.append(0)
        st_only.append(0)
        st_before.append(0)
        continue

    # 儿子都处理完了，结算 u。
    inside = st_same.pop()
    positive = st_positive.pop()
    only_child = st_only.pop()
    sub = st_sub.pop()
    st_before.pop()  # 本帧的 before 已用完, 与 C++ 版同步出栈
    st_edge.pop()
    st_u.pop()

    c = color[u]
    subtree[u] = sub
    done_cnt[c] += 1

    if total_cnt[c] > 1:
        # 同色点分布在几个方向：含同色点的儿子各算一个，子树外还有同色点再算一个。
        outside = total_cnt[c] - inside
        directions = positive + (1 if outside > 0 else 0)
        if directions >= 3:
            too_many[c] = 1          # 三点散开，不存在装得下它们的路径
        elif directions == 1:
            # u 是最外层的端点，外侧连通块 = 含同色点那一侧的补集
            if positive == 1:
                side = n - subtree[only_child]
            else:
                side = sub
            leaf_cnt[c] += 1
            if leaf_cnt[c] == 1:
                side_first[c] = side
            elif leaf_cnt[c] == 2:
                side_second[c] = side

    if st_u:
        # 把 u 这棵子树的结果累加到父亲身上。
        p = st_u[-1]
        p_color = color[p]
        added = done_cnt[p_color] - st_before[-1]
        st_sub[-1] += sub
        st_same[-1] += added
        if added > 0:
            st_positive[-1] += 1
            st_only[-1] = u

all_pairs = n * (n - 1) // 2
for c in range(1, n + 1):
    answer[c] = all_pairs  # 没有该颜色节点时所有点对都合法

for c in range(1, n + 1):
    if total_cnt[c] == 0:
        continue
    if total_cnt[c] == 1:
        # 只有 1 个同色点 x：用补集减去「两端点在同一连通块」的点对
        x = first_node[c]
        out = n - subtree[x]
        excluded = out * (out - 1) // 2
        e = head[x]
        while e != -1:
            v = to[e]
            if parent[v] == x:
                size = subtree[v]
                excluded += size * (size - 1) // 2
            e = nxt[e]
        answer[c] = all_pairs - excluded
    else:
        # 恰好两个端点才共线，否则答案为 0
        if too_many[c] or leaf_cnt[c] != 2:
            answer[c] = 0
        else:
            answer[c] = side_first[c] * side_second[c]

out_lines = []
for c in range(1, n + 1):
    out_lines.append(str(answer[c]))
sys.stdout.write("\n".join(out_lines) + "\n")
