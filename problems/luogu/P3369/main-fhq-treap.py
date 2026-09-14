import random
import sys
from typing import Optional, Tuple, Any

# FHQ-Treap 的 split / merge 都是递归实现的。
# 随机优先级保证树高期望为 O(log n)，但为了保险仍把递归上限调高。
sys.setrecursionlimit(300000)


class Node:
    """Treap 节点"""
    __slots__ = ("val", "pri", "size", "l", "r")

    def __init__(self, val: Any, pri: int):
        self.val = val
        self.pri = pri
        self.size = 1
        self.l: Optional["Node"] = None
        self.r: Optional["Node"] = None


class FHQTreap:
    """
    FHQ-Treap（无旋平衡树）
    基于按值分裂 (split) 与合并 (merge) 维护动态有序集合。
    支持：插入、删除单次出现、按值查排名、查第 k 小、查前驱、查后继。
    所有基本操作的期望时间复杂度均为 O(log n)。
    """

    def __init__(self, seed: Optional[int] = 233):
        self.root: Optional[Node] = None
        self.rng = random.Random(seed)

    def _size(self, u: Optional[Node]) -> int:
        return u.size if u is not None else 0

    def _push_up(self, u: Node) -> None:
        """由左右子树大小更新当前节点子树大小"""
        u.size = self._size(u.l) + self._size(u.r) + 1

    def _new_node(self, val: Any) -> Node:
        return Node(val, self.rng.randint(1, 2**31 - 1))

    def split(self, u: Optional[Node], val: Any) -> Tuple[Optional[Node], Optional[Node]]:
        """
        按数值 val 分裂：
        - 左树 x：包含所有节点值 <= val 的节点
        - 右树 y：包含所有节点值 > val 的节点
        """
        if u is None:
            return None, None
        if u.val <= val:
            x, y = self.split(u.r, val)
            u.r = x
            self._push_up(u)
            return u, y
        else:
            x, y = self.split(u.l, val)
            u.l = y
            self._push_up(u)
            return x, u

    def merge(self, x: Optional[Node], y: Optional[Node]) -> Optional[Node]:
        """
        合并两棵树 x 和 y：
        前提：x 中所有节点的值 <= y 中所有节点的值
        依据节点的随机优先级保持大根堆性质
        """
        if x is None or y is None:
            return x if y is None else y
        if x.pri > y.pri:
            x.r = self.merge(x.r, y)
            self._push_up(x)
            return x
        else:
            y.l = self.merge(x, y.l)
            self._push_up(y)
            return y

    def insert(self, val: Any) -> None:
        """插入一个数值 val"""
        x, y = self.split(self.root, val)
        node = self._new_node(val)
        self.root = self.merge(self.merge(x, node), y)

    def delete(self, val: Any) -> None:
        """
        删除一个数值等于 val 的节点（若存在多个同值节点仅删除其中一个）。
        通过将集合切为 (< val)、(== val)、(> val) 三部分，丢弃 (== val) 的一个节点后拼回。
        """
        x, z = self.split(self.root, val)
        x, y = self.split(x, val - 1)
        if y is not None:
            # 丢弃 y 的根节点，将其左右子树合并
            y = self.merge(y.l, y.r)
        self.root = self.merge(self.merge(x, y), z)

    def rank(self, val: Any) -> int:
        """
        查询数值 val 在集合中的排名（小于 val 的元素个数 + 1）。
        采用 BST 遍历，常数小于 split/merge 且无需改变树结构。
        """
        u = self.root
        ans = 0
        while u is not None:
            if u.val < val:
                ans += self._size(u.l) + 1
                u = u.r
            else:
                u = u.l
        return ans + 1

    def kth(self, k: int) -> Any:
        """
        查询集合中第 k 小的元素（1-based）。
        若 k 超出合法范围 [1, size()] 则抛出 IndexError。
        """
        if not (1 <= k <= self.size()):
            raise IndexError(f"kth index {k} out of range (size={self.size()})")
        u = self.root
        while u is not None:
            l_sz = self._size(u.l)
            if k <= l_sz:
                u = u.l
            elif k == l_sz + 1:
                return u.val
            else:
                k -= l_sz + 1
                u = u.r
        raise IndexError("kth not found")

    def pre(self, val: Any) -> Optional[Any]:
        """
        查询 val 的前驱（小于 val 的最大值）。
        若不存在严格小于 val 的值，返回 None。
        """
        u = self.root
        ans = None
        while u is not None:
            if u.val < val:
                ans = u.val
                u = u.r
            else:
                u = u.l
        return ans

    def succ(self, val: Any) -> Optional[Any]:
        """
        查询 val 的后继（大于 val 的最小值）。
        若不存在严格大于 val 的值，返回 None。
        """
        u = self.root
        ans = None
        while u is not None:
            if u.val > val:
                ans = u.val
                u = u.l
            else:
                u = u.r
        return ans

    def size(self) -> int:
        """返回集合中的节点总数"""
        return self._size(self.root)

    def __len__(self) -> int:
        return self.size()

    def empty(self) -> bool:
        """判断集合是否为空"""
        return self.root is None

    def clear(self) -> None:
        """清空平衡树"""
        self.root = None


def main() -> None:
    # 一次性读入全部输入并按空白切分，再惰性转成整数。
    # 用迭代器顺序取值，比循环里反复 input() / split() 快很多。
    data = iter(map(int, sys.stdin.buffer.read().split()))

    n = next(data)
    # 用系统熵做随机种子：如果固定种子，出题人可能针对性地构造让树退化的数据。
    tree = FHQTreap(random.getrandbits(64))

    answers = []
    for _ in range(n):
        opt = next(data)
        x = next(data)
        if opt == 1:  # 插入 x
            tree.insert(x)
        elif opt == 2:  # 删除一个 x
            tree.delete(x)
        elif opt == 3:  # x 的排名 = 小于 x 的个数 + 1
            answers.append(str(tree.rank(x)))
        elif opt == 4:  # 第 x 小
            answers.append(str(tree.kth(x)))
        elif opt == 5:  # 前驱：小于 x 的最大值
            answers.append(str(tree.pre(x)))
        else:  # opt == 6，后继：大于 x 的最小值
            answers.append(str(tree.succ(x)))

    # 结果统一收集后一次输出，避免大量 print() 的系统调用开销。
    print("\n".join(answers))


if __name__ == "__main__":
    main()

