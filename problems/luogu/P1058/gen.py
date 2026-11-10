import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：m <= 4, n <= 4, h <= 5
m = randint(1, 4)
n = randint(1, 4)
io.input_writeln(f"{m} {n}")

for _ in range(m):
    row = [randint(1, 5) for _ in range(n)]
    io.input_writeln(" ".join(map(str, row)))
