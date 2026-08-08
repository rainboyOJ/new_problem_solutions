#!/usr/bin/env python3

from __future__ import annotations

import sys
from pathlib import Path


def read_input(path: Path) -> tuple[int, int, int, int]:
    data = path.read_text(encoding="utf-8").split()
    if len(data) != 4:
        raise ValueError("输入格式错误。")
    return tuple(map(int, data))  # type: ignore[return-value]


def check_output(path: Path, n: int, m: int, k: int, p: int) -> bool:
    data = path.read_text(encoding="utf-8").split()
    if not data:
        raise ValueError(f"{path} 输出为空。")

    if data[0] == "NO":
        if len(data) != 1:
            raise ValueError(f"{path} 输出 NO 时不应再有别的内容。")
        return False

    if data[0] != "YES":
        raise ValueError(f"{path} 第一项必须是 YES 或 NO。")

    if len(data) != 1 + 2 * n:
        raise ValueError(f"{path} 输出 YES 时应给出 {n} 组 x y。")

    nums = list(map(int, data[1:]))
    xs = []
    total = 0
    for i in range(n):
        x = nums[i * 2]
        y = nums[i * 2 + 1]
        if x < 0 or y < 0:
            raise ValueError(f"{path} 出现负数。")
        if x + y != m:
            raise ValueError(f"{path} 第 {i + 1} 个人不满足 x+y=m。")
        xs.append(x)
        total += x

    if total != k:
        raise ValueError(f"{path} 所有 x_i 之和不是 k。")

    mx = max(xs)
    cnt = 0
    for v in xs:
        if v == mx:
            cnt += 1
    if cnt != p:
        raise ValueError(f"{path} 抽到最多记号的人数不是 p。")

    return True


def main() -> int:
    if len(sys.argv) != 4:
        print("usage: checker.py input.txt user.out brute.out", file=sys.stderr)
        return 2

    input_path = Path(sys.argv[1])
    user_path = Path(sys.argv[2])
    brute_path = Path(sys.argv[3])

    try:
        n, m, k, p = read_input(input_path)
        user_ok = check_output(user_path, n, m, k, p)
        brute_ok = check_output(brute_path, n, m, k, p)
    except ValueError as exc:
        print(str(exc), file=sys.stderr)
        return 1

    if user_ok != brute_ok:
        print("user 与 brute 对可行性的判断不一致。", file=sys.stderr)
        return 1

    print("OK")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
