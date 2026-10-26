#!/usr/bin/env python3
# spj.py: 本题是多解 SPJ. check(inp, got, want) 校验:
# 1. got 第一行与 want 第一行(最大美学值)相同;
# 2. got 第二行是 F 个严格递增的花瓶编号, 且都在 [1, V] 内;
# 3. 用输入的 a 矩阵独立重算该方案美学值, 必须等于第一行.
# duipai 约定: checker input.txt user.out brute.out
import sys


def parse_ints(s: str) -> list[int]:
    return [int(x) for x in s.split()]


def check(inp: str, got: str, want: str):
    try:
        a_in = parse_ints(inp)
        a_got = parse_ints(got)
        a_want = parse_ints(want)
    except Exception as e:
        return False, f"解析失败: {e}"

    if len(a_in) < 2:
        return False, "输入缺少 F 和 V"
    f, v = a_in[0], a_in[1]
    if len(a_in) != 2 + f * v:
        return False, f"输入长度错误: 期望 {2 + f * v}, 实际 {len(a_in)}"

    if not a_want:
        return False, "want 输出为空"
    if len(a_got) < f + 1:
        return False, f"got 输出不足: 至少需要 {f + 1} 个数, 实际 {len(a_got)}"

    val_got, plan = a_got[0], a_got[1:1 + f]
    val_want = a_want[0]
    if val_got != val_want:
        return False, f"第一行最大值不同: got={val_got} want={val_want}"

    if len(plan) != f:
        return False, f"方案长度错误: {len(plan)} != {f}"
    for p in plan:
        if not (1 <= p <= v):
            return False, f"花瓶编号越界: {p}"
    for i in range(1, f):
        if not (plan[i - 1] < plan[i]):
            return False, "花瓶编号不严格递增"

    total = 0
    for i in range(f):
        total += a_in[2 + i * v + (plan[i] - 1)]
    if total != val_got:
        return False, f"方案重算美学值 {total} != 输出 {val_got}"

    return True, "ok"


if __name__ == "__main__":
    inp = open(sys.argv[1], encoding="utf-8").read()
    got = open(sys.argv[2], encoding="utf-8").read()
    want = open(sys.argv[3], encoding="utf-8").read()
    ok, msg = check(inp, got, want)
    print(msg)
    sys.exit(0 if ok else 1)
