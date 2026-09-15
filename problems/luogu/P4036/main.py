import sys


sys.setrecursionlimit(1_000_000)

BASE = 233
MASK = (1 << 64) - 1
seed = 712367821
power = []


def next_priority():
    """xorshift64：给 FHQ Treap 生成随机优先级。"""
    global seed
    seed ^= (seed << 7) & MASK
    seed ^= seed >> 9
    return seed


class Node:
    __slots__ = ("value", "priority", "size", "hash_value", "left", "right")

    def __init__(self, value):
        self.value = value
        self.priority = next_priority()
        self.size = 1
        self.hash_value = value
        self.left = None
        self.right = None


def size(node):
    return node.size if node is not None else 0


def hash_of(node):
    return node.hash_value if node is not None else 0


def pull(node):
    """由“左子串 + 当前字符 + 右子串”更新长度和整段哈希。"""
    left_size = size(node.left)
    right_size = size(node.right)
    node.size = left_size + 1 + right_size
    node.hash_value = (
        hash_of(node.left) * power[right_size + 1]
        + node.value * power[right_size]
        + hash_of(node.right)
    ) & MASK


def split(node, first_count):
    """按位置分裂：返回前 first_count 个字符和其余字符。"""
    if node is None:
        return None, None

    if size(node.left) >= first_count:
        left_tree, node.left = split(node.left, first_count)
        pull(node)
        return left_tree, node

    node.right, right_tree = split(node.right, first_count - size(node.left) - 1)
    pull(node)
    return node, right_tree


def merge(left_tree, right_tree):
    """连接两个相邻的字符段。"""
    if left_tree is None:
        return right_tree
    if right_tree is None:
        return left_tree

    if left_tree.priority < right_tree.priority:
        left_tree.right = merge(left_tree.right, right_tree)
        pull(left_tree)
        return left_tree

    right_tree.left = merge(left_tree, right_tree.left)
    pull(right_tree)
    return right_tree


def range_hash(node, left, right):
    """返回当前子树内第 left 到第 right 个字符的哈希（下标从 1 开始）。"""
    if left == 1 and right == node.size:
        return node.hash_value

    left_size = size(node.left)
    result = 0

    if left <= left_size:
        part_left = left
        part_right = min(right, left_size)
        part_hash = range_hash(node.left, part_left, part_right)
        result = (result * power[part_right - part_left + 1] + part_hash) & MASK

    middle_pos = left_size + 1
    if left <= middle_pos <= right:
        result = (result * BASE + node.value) & MASK

    if right > middle_pos:
        part_left = max(1, left - middle_pos)
        part_right = right - middle_pos
        part_hash = range_hash(node.right, part_left, part_right)
        result = (result * power[part_right - part_left + 1] + part_hash) & MASK

    return result


def insert_after(root, position, value):
    """在 position 后插入；position 为 0 时插在开头。"""
    left_tree, right_tree = split(root, position)
    return merge(merge(left_tree, Node(value)), right_tree)


def replace(root, position, value):
    """将第 position 个字符改为 value。"""
    node = root
    path = []
    while True:
        path.append(node)
        left_size = size(node.left)
        if position <= left_size:
            node = node.left
        elif position == left_size + 1:
            node.value = value
            break
        else:
            position -= left_size + 1
            node = node.right

    for node in reversed(path):
        pull(node)
    return root


def solve():
    global power
    readline = sys.stdin.buffer.readline
    initial = readline().strip()
    operation_count = int(readline())
    operations = [readline().split() for _ in range(operation_count)]

    # 最多每个操作都插入一个字符，预处理全部可能长度的 base 幂。
    power = [1] * (len(initial) + operation_count + 2)
    for i in range(1, len(power)):
        power[i] = (power[i - 1] * BASE) & MASK

    root = None
    for char in initial:
        root = merge(root, Node(char - 96))

    answers = []
    for operation in operations:
        kind = operation[0]
        if kind == b'I':
            position = int(operation[1])
            root = insert_after(root, position, operation[2][0] - 96)
        elif kind == b'R':
            position = int(operation[1])
            root = replace(root, position, operation[2][0] - 96)
        else:
            x = int(operation[1])
            y = int(operation[2])
            length = root.size
            if x == y:
                answers.append(str(length - x + 1))
                continue

            upper = min(length - x + 1, length - y + 1)
            low, high = 0, upper
            # rbook 二分模板的“找第一个 true”在这里等价为：
            # 对单调的“前 k 个相同”寻找最后一个 true。
            while low < high:
                middle = (low + high + 1) // 2
                if range_hash(root, x, x + middle - 1) == range_hash(root, y, y + middle - 1):
                    low = middle
                else:
                    high = middle - 1
            answers.append(str(low))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()
