#!/usr/bin/env python3
# Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
# rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
# rainboy的学习导航网站: https://idx.roj.ac.cn
# create_at: 2026-09-29 13:31
# update_at: 2026-09-29 13:31

import ctypes

# ctypes 的类型与 C 的内存布局一一对应，sizeof 给出的就是 C 里 sizeof() 的字节数。
# Python 自身没有 bool/char 的存储大小可言（bool 是 int 子类、没有 char 类型），
# 所以要"测量"就必须借用与 C 同布局的 ctypes，而不是硬编码 1。
BOOL_SIZE = ctypes.sizeof(ctypes.c_bool)  # 对应 C++ 的 bool，1 字节
CHAR_SIZE = ctypes.sizeof(ctypes.c_char)  # 对应 C++ 的 char，1 字节


def solve() -> None:
    # 无输入；两个常量按题面顺序用一个空格隔开输出
    print(BOOL_SIZE, CHAR_SIZE)


if __name__ == "__main__":
    solve()
