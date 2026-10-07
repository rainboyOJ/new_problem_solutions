#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-10-08 02:12
# update_at: 2026-10-08 02:12

import sys

AND, XOR, OR = 1, 2, 3  # 题面的算子编号：1=与, 2=异或, 3=或（顺序与直觉不同）

type Values = list[int]  # 一组数据的序列，元素是 20 位以内的位掩码


def bit_class_mask(step: int, dom: int) -> int:
    """dom 位掩码：下标中第 step 位为 1 的那些位置全置 1（step 是 2^b，不是 b）。

    长度为 2*step 的一小段里，高半段（下标 ∈ [step, 2*step)）全是 1；把这段模式
    按周期翻倍原样拼下去即可，避免用大数除法构造周期性掩码。
    """
    pattern = ((1 << step) - 1) << step  # 一个周期 2*step 里的高半段
    width = step << 1
    while width < dom:
        pattern |= pattern << width  # 把已有模式原样再拼一份，周期翻倍
        width <<= 1
    return pattern & ((1 << dom) - 1)


def superset_flags(values: Values, dom: int) -> bytes:
    """返回 sup，第 m 位为 1 表示存在某个值 v 满足 m ⊆ v（v 补齐 m 缺的位）。

    高维后缀和（SOS）逐位做 F |= (F & 第 b 位为 1 的下标) >> 2^b：把“含第 b 位”
    的下标标记下放到“不含第 b 位”的下标。整张 dom 位的标记表由一个 Python 大整数
    承载，一轮只需数次大整数位运算，位并行的代价远低于逐下标循环。
    """
    bytes_len = (dom + 7) >> 3
    bits = bytearray(bytes_len)
    for v in values:
        bits[v >> 3] |= 1 << (v & 7)
    flags = int.from_bytes(bits, 'little')

    for b in range(dom.bit_length() - 1):  # dom 是 2 的幂，位数就是 bit_length()-1
        step = 1 << b
        flags |= (flags & bit_class_mask(step, dom)) >> step
    return flags.to_bytes(bytes_len, 'little')


def max_and(values: Values, hi: int) -> int:
    """与运算（c=1）：高位到低位贪心，每轮只留下包含候选掩码的元素。

    "至少两个元素都包含 cand" 对 cand 单调（cand 变小只会更易成立），所以从高位
    贪心得到的掩码就是最大的两数 AND；含 cand 者必然含上一轮的 cur，只需在 kept 里筛。
    """
    kept, cur = values, 0
    for b in range(hi, -1, -1):
        cand = cur | 1 << b
        nxt = [v for v in kept if (v & cand) == cand]  # 含 cand 者必然含 cur，可只筛 kept
        if len(nxt) >= 2:  # 这一位要得起：至少有 2 个元素盖住 cand
            kept, cur = nxt, cand
    return cur


def max_xor(values: Values, hi: int) -> int:
    """异或运算（c=2）：按前缀集合贪心，看候选答案能否由两个数的高位前缀拼出。

    第 b 轮保留每个数的高 (hi-b+1) 位前缀；若存在两个前缀 p、p^cand 同时出现，
    说明有一对元素在这段高位上的异或恰为 cand，这一位可以要。前缀集合的求交/判交
    都在 C 层完成，避免逐个前缀做 Python 循环。
    """
    best, mask = 0, 0
    for b in range(hi, -1, -1):
        mask |= 1 << b
        prefixes = {v & mask for v in values}
        cand = best | 1 << b
        # 存在两个前缀互为 cand 的异或，说明有一对元素拼得出 cand
        pairable = not prefixes.isdisjoint(p ^ cand for p in prefixes)
        if pairable:
            best = cand
    return best


def max_or(values: Values, hi: int) -> int:
    """或运算（c=3）：先做值域超集标记 sup，再逐位贪心。

    记 cand 为目标答案掩码、t = cand & ~v 是元素 v 缺的位。存在一对元素的 OR 包含
    cand，等价于存在某个 v 使"有元素包含 t"——t 与 v 的位不相交，所以那个元素不是 v
    自己；t 为 0 时 v 自己已覆盖 cand，题面 n>=2 保证还有别的下标可以配对。
    """
    dom = 1 << (hi + 1)
    sup = superset_flags(values, dom)
    gaps = [~v for v in values]  # ~v 是补集，cand & ~v 取 cand 中 v 缺的位

    cur = 0
    for b in range(hi, -1, -1):
        cand = cur | 1 << b
        # 缺位集合先去重（同一个缺位只需查一次），再逐位读 sup 表
        missing = {cand & g for g in gaps}
        covered = any(sup[m >> 3] >> (m & 7) & 1 for m in missing)
        if covered:
            cur = cand
    return cur


def solve() -> None:
    data = iter(map(int, sys.stdin.buffer.read().split()))
    out: list[str] = []
    T = next(data)

    for _ in range(T):
        n, c = next(data), next(data)
        values = [next(data) for _ in range(n)]
        hi = max(values).bit_length() - 1  # 值域最高位，答案不会超过它

        if c == AND:
            out.append(str(max_and(values, hi)))
        elif c == XOR:
            out.append(str(max_xor(values, hi)))
        else:
            out.append(str(max_or(values, hi)))

    print('\n'.join(out))


if __name__ == "__main__":
    solve()
