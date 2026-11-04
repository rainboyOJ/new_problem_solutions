#!/usr/bin/env python3
"""1295C 造数据：无输入，stdout 就是一组数据。

用法：gen.py [len_s] [len_t]
不给参数就随机小规模，方便对拍。
"""
import sys

from cyaron import randint, String

len_s = int(sys.argv[1]) if len(sys.argv) > 1 else randint(1, 10)
len_t = int(sys.argv[2]) if len(sys.argv) > 2 else randint(1, 12)

kind = randint(0, 4)
if kind == 0:
    s = String.random(len_s, charset="ab")
    t = String.random(len_t, charset="ab")
elif kind == 1:                          # t 里混进 s 没有的字符：测 -1
    s = String.random(len_s, charset="ab")
    t = String.random(len_t, charset="abz")
elif kind == 2:                          # s 只有一个字符：测答案很大
    s = "a" * len_s
    t = "a" * len_t
elif kind == 3:                          # s 极短，t 很长
    s = String.random(min(len_s, 3), charset="abc")
    t = String.random(len_t, charset="abc")
else:                                    # 一堆用例，检验多组之间有没有串味
    cases = [(String.random(len_s, charset="ab"), String.random(len_t, charset="ab"))
             for _ in range(randint(2, 5))]
    print(len(cases))
    for a, b in cases:
        print(a)
        print(b)
    sys.exit(0)

print(1)
print(s)
print(t)
