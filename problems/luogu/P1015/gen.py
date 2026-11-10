import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

bases = [2, 3, 4, 8, 10, 16]
base = bases[randint(0, len(bases) - 1)]
io.input_writeln(base)

length = randint(1, 15)
digits = "0123456789ABCDEF"
# 第一位不能为 0
first_digit = digits[randint(1, base - 1)]
rest_digits = "".join(digits[randint(0, base - 1)] for _ in range(length - 1))
io.input_writeln(first_digit + rest_digits)
