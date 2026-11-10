import sys
import math
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 生成两个互质的正整数 a, b > 1
while True:
    a = randint(2, 500)
    b = randint(2, 500)
    if math.gcd(a, b) == 1:
        break

io.input_writeln(f"{a} {b}")
