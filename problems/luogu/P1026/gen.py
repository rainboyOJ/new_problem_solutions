import sys
import random
import string
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模控制在 p=1 (20字符)，k=2~4
p = 1
k = randint(2, 4)
io.input_writeln(f"{p} {k}")

# 生成 20 个字符的单行字符串
line = "".join(random.choices("abcde", k=20))
io.input_writeln(line)

# 生成 1~4 个词，长度 1~4
s = randint(1, 4)
io.input_writeln(s)

words = set()
for _ in range(s):
    w_len = randint(1, 3)
    w = "".join(random.choices("abcde", k=w_len))
    words.add(w)

for w in words:
    io.input_writeln(w)
