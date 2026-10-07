#!/usr/bin/env python3
"""选择 C++ 编译器。

macOS 上系统 `/usr/bin/g++` 是 Apple Clang 的别名，**没有 `bits/stdc++.h`**，
所以仓库脚本里硬编码的 `g++` 在 macOS 上会直接编译失败（`'bits/stdc++.h' file not found`）。
Homebrew 的 `g++-16` 才是真正的 GCC。

选择顺序：

1. 环境变量 `CXX`（显式指定；支持带参数，用 `shlex.split` 切分）
2. PATH 上的 `g++-16`
3. `/opt/homebrew/bin/g++-16`（macOS Homebrew 默认路径）
4. `g++`（Linux 等系统 `g++` 本身就是 GCC 的场合）

用法：

    from compiler import find_cxx

    cmd = [*find_cxx(), "-std=c++17", "-O2", str(src), "-o", str(out)]

显式指定：

    CXX=/usr/local/bin/g++-14 python3 scripts/problem-analysis-tools/check_sample.py problems/roj/1183
"""

from __future__ import annotations

import os
import shlex
import shutil

HOMEBREW_GCC = "/opt/homebrew/bin/g++-16"


def find_cxx() -> list[str]:
    """返回编译命令的前缀（可能含参数），调用方在后面追加自己的编译选项。"""
    override = os.environ.get("CXX")
    if override:
        parts = shlex.split(override)
        if parts:
            return parts

    if shutil.which("g++-16"):
        return ["g++-16"]

    if os.path.isfile(HOMEBREW_GCC) and os.access(HOMEBREW_GCC, os.X_OK):
        return [HOMEBREW_GCC]

    return ["g++"]


def compiler_label() -> str:
    """人类可读的编译器描述，用于在报告里说明用的是哪一个。"""
    return " ".join(find_cxx())


if __name__ == "__main__":
    print(compiler_label())
