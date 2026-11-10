import sys
import random
import string
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 密钥长度 1~20，密文长度 1~100
k_len = randint(1, 20)
c_len = randint(1, 100)

alphabet = string.ascii_letters

k_str = "".join(random.choices(alphabet, k=k_len))
c_str = "".join(random.choices(alphabet, k=c_len))

io.input_writeln(k_str)
io.input_writeln(c_str)
