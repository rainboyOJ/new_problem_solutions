#!/usr/bin/env python3
import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成位数在 1 到 8 位的数字，方便暴力全排列验证
len_a = randint(1, 8)
# 为了测试两种情况：len_a < len_b 和 len_a == len_b
if randint(1, 4) == 1:
    len_b = randint(len_a + 1, 9)
else:
    len_b = len_a

# 生成 a
digits = [randint(1, 9)] + [randint(0, 9) for _ in range(len_a - 1)]
a = int("".join(map(str, digits)))

# 如果 len_a == len_b，为了保证存在解，b 应该 >= a 的最小值
if len_a == len_b:
    min_a = int("".join(sorted(str(a))))
    # 生成一个 >= min_a 的同位数 b
    b = randint(min_a, 10**len_b - 1)
else:
    b = randint(10 ** (len_b - 1), 10**len_b - 1)

io.input_writeln(a)
io.input_writeln(b)
