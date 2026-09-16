#!/usr/bin/env python3
"""
Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
rainboy 的学习导航网站: https://idx.roj.ac.cn
create_at: 2026-09-15 22:15
update_at: 2026-09-15 22:15

P1503 鬼子进村
解法：把被摧毁的房子看作“断点”，用 FHQ-Treap 维护断点集合。
      查询 x 时，找到左侧最近的断点 L 和右侧最近的断点 R，
      能到达的房子数就是 R - L - 1。
"""
import sys
from typing import Any, Optional, Tuple

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
    """FHQ-Treap（无旋平衡树），当作有序集合 set 来用。"""

    def __init__(self, seed: int = 233):
        self.root: Optional[Node] = None
        self._seed = seed
        self._rnd_state = seed

    def _rnd(self) -> int:
        # 用线性同余代替 random 模块，速度更快且结果可复现
        self._rnd_state = (self._rnd_state * 1103515245 + 12345) & 0x7FFFFFFF
        return self._rnd_state

    def _size(self, u: Optional[Node]) -> int:
        return u.size if u is not None else 0

    def _push_up(self, u: Node) -> None:
        u.size = self._size(u.l) + self._size(u.r) + 1

    def _new_node(self, val: Any) -> Node:
        return Node(val, self._rnd() | 1)

    def split(self, u: Optional[Node], val: Any) -> Tuple[Optional[Node], Optional[Node]]:
        """左树 x：值 <= val；右树 y：值 > val。"""
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
        """前提：x 中所有值 <= y 中所有值。"""
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

    def contains(self, val: Any) -> bool:
        """判断集合中是否存在值为 val 的节点。"""
        u = self.root
        while u is not None:
            if u.val == val:
                return True
            u = u.l if val < u.val else u.r
        return False

    def insert(self, val: Any) -> None:
        """插入 val；若已存在则不再重复插入（与 std::set 语义一致）。"""
        if self.contains(val):
            return
        x, y = self.split(self.root, val)
        self.root = self.merge(self.merge(x, self._new_node(val)), y)

    def delete(self, val: Any) -> None:
        """删除所有值为 val 的节点（与 std::set::erase 语义一致）。"""
        x, z = self.split(self.root, val)
        x, _ = self.split(x, val - 1)  # 中间那棵树整体丢弃
        self.root = self.merge(x, z)

    def succ(self, val: Any) -> Optional[Any]:
        """第一个严格大于 val 的值（后继）。"""
        u = self.root
        ans = None
        while u is not None:
            if u.val > val:
                ans = u.val
                u = u.l
            else:
                u = u.r
        return ans

    def pre(self, val: Any) -> Optional[Any]:
        """第一个严格小于 val 的值（前驱）。"""
        u = self.root
        ans = None
        while u is not None:
            if u.val < val:
                ans = u.val
                u = u.r
            else:
                u = u.l
        return ans


def main() -> None:
    data = sys.stdin.buffer.read().split()
    n = int(data[0])
    m = int(data[1])

    destroyed = bytearray(n + 2)  # destroyed[i] 表示 i 号房子当前是否被摧毁
    stk = []                      # 摧毁历史，R 操作按后进先出恢复

    fhq = FHQTreap()
    fhq.insert(0)      # 虚拟左边界
    fhq.insert(n + 1)  # 虚拟右边界

    out = []
    idx = 2
    for _ in range(m):
        op = data[idx]
        idx += 1
        if op == b"D":
            x = int(data[idx])
            idx += 1
            destroyed[x] = 1
            fhq.insert(x)
            stk.append(x)
        elif op == b"R":
            x = stk.pop()
            destroyed[x] = 0
            fhq.delete(x)
        else:  # Q
            x = int(data[idx])
            idx += 1
            if destroyed[x]:
                out.append("0")
            else:
                r = fhq.succ(x)
                l = fhq.pre(x)
                out.append(str(r - l - 1))

    sys.stdout.write("\n".join(out) + ("\n" if out else ""))


if __name__ == "__main__":
    main()
