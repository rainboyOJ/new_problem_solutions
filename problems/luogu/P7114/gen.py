import sys
import random
import string
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 暴力对拍规模
t = randint(1, 3)
io.input_writeln(t)

for _ in range(t):
    n = randint(3, 40)
    # 限制字符集为 3~4 个，方便出现周期重复
    charset = "abc"
    s = "".join(random.choices(charset, k=n))
    io.input_writeln(s)
