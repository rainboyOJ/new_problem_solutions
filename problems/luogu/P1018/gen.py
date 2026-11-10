import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：N <= 12, K <= 4
n = randint(3, 12)
k = randint(1, min(4, n - 1))
io.input_writeln(f"{n} {k}")

# 生成非零开头的数字串
first = str(randint(1, 9))
rest = "".join(str(randint(0, 9)) for _ in range(n - 1))
io.input_writeln(first + rest)
