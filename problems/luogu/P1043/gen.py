import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：n <= 8, m <= 4
n = randint(3, 8)
m = randint(1, min(4, n))
io.input_writeln(f"{n} {m}")

for _ in range(n):
    io.input_writeln(randint(-50, 50))
