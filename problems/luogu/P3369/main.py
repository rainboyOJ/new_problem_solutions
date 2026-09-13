import sys
from bisect import bisect_left, bisect_right


# ===== 快速读入 =====
# sys.stdin.buffer.read() 一次性读入全部字节（比逐行 input() 快得多）。
# .split() 按空白切成 bytes 列表，交给 map(int, ...) 惰性转换。
# 注意 map 返回的是迭代器，只能顺着取一次，所以用 iter() 包一层后统一用 next() 取值。
data = iter(map(int, sys.stdin.buffer.read().split()))

# 第一项是操作次数 m，之后每条操作占两个数：op 和 x。
# 列表推导式一次把 m 条操作取成 (op, x) 元组；因为输入保证成对出现，这里不会越界。
operations = [(next(data), next(data)) for _ in range(next(data))]


# ===== 坐标压缩（离线）=====
# 题目叫“平衡树”，但所有操作已经在输入里给全了，可以先纵览全局：
# 收集所有出现过的数值 x（操作 4 的 x 是排名，不是数值，要排除），
# 用集合去重后排序，得到“值 -> 下标”的映射。之后树状数组只需在这些下标上工作，
# 长度从 1e9 级别的值域压缩到 O(m)。
coordinates = sorted({value for operation, value in operations if operation != 4})

# 树状数组本体，1-indexed，多开一格让 sizes+1 个元素都进得来。
tree = [0] * (len(coordinates) + 1)


def add(index, delta):
    """把坐标 index（0-based，调用方传入）的出现次数增加 delta。"""
    index += 1  # Fenwick 内部从 1 开始，外部统一用 0-based 坐标
    while index < len(tree):
        tree[index] += delta
        index += index & -index  # 跳到下一个被该点覆盖的位置（加最低位的 1）


def prefix(end):
    """返回区间 [0, end) 内的总计数，即前 end 个坐标的出现次数之和。"""
    result = 0
    while end:
        result += tree[end]
        end -= end & -end  # 抹掉最低位的 1，跳到上一层区间
    return result


def kth(rank):
    """返回整棵树上第 rank 小（1-based）的数值。"""
    index = 0  # 已经走过的前缀长度（也是 1-based 坐标）
    # bit_length() 取二进制位数，向下取到最大的 2 的幂作为第一步长，
    # 这正是树状数组能直接二分（二进制提升）的原因。
    step = 1 << (len(tree).bit_length() - 1)
    while step:
        target = index + step
        # 若 target 这一整段的前缀和仍小于 rank，说明答案不在这段里，整段跳过
        # 为什么这里用到了tree[target]? 这里是BITree的二进制跳跃的最大的性质: 正好是跳跃的区间
        if target < len(tree) and tree[target] < rank:
            index = target
            rank -= tree[target]
        step >>= 1
    # 循环结束时 index 是最后一个前缀和 < rank 的坐标，加 1 才是答案坐标；
    # 函数开头 index = 0，所以 coordinates[index] 恰好取到 0-based 的答案。
    return coordinates[index]


# ===== 第二遍处理操作 =====
# 结果先存进列表，最后用 "\n".join 一次输出：
# 比在循环里反复 print() 少很多次系统调用，是 Python 提速的常用技巧。
answers = []
for operation, value in operations:
    if operation == 1:  # 插入 x：该值计数 +1
        add(bisect_left(coordinates, value), 1)
    elif operation == 2:  # 删除一个 x：该值计数 -1
        add(bisect_left(coordinates, value), -1)
    elif operation == 3:  # 查询 x 的排名 = 小于 x 的个数 + 1
        # bisect_left 返回第一个 >= value 的下标，正好是“严格小于 value”的个数
        answers.append(str(prefix(bisect_left(coordinates, value)) + 1))
    elif operation == 4:  # 查询第 x 小
        answers.append(str(kth(value)))
    elif operation == 5:  # 严格前驱：小于 x 的个数，对应第 count 小
        answers.append(str(kth(prefix(bisect_left(coordinates, value)))))
    else:  # operation == 6，严格后继：小于等于 x 的个数 + 1，对应那个排名
        # bisect_right 返回第一个 > value 的下标，即“小于等于 value”的个数
        answers.append(str(kth(prefix(bisect_right(coordinates, value)) + 1)))

print("\n".join(answers))
