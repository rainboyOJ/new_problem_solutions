import sys
import random
import string
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 保证字符集大小大于等于 n，避免 m=1 时死循环
m = randint(1, 15)
max_n = min(15, 26**m)
n = randint(1, max_n)
io.input_writeln(n, m)

seen = set()
for _ in range(n):
    while True:
        s = "".join(random.choices(string.ascii_lowercase, k=m))
        if s not in seen:
            seen.add(s)
            break
    io.input_writeln(s)
