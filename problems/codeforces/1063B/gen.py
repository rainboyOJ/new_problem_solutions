import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)
n = randint(2, 8)
m = randint(2, 8)
r = randint(1, n)
c = randint(1, m)
x = randint(0, 10)
y = randint(0, 10)

io.input_writeln(n, m)
io.input_writeln(r, c)
io.input_writeln(x, y)

for i in range(1, n + 1):
    row = []
    for j in range(1, m + 1):
        if i == r and j == c:
            row.append(".")
        else:
            row.append("." if randint(1, 10) > 3 else "*")
    io.input_writeln("".join(row))
