import sys
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 对拍小规模：N <= 12
n = randint(1, 12)
io.input_writeln(n)

# 生成单调不减的 S_i
cur_s = randint(1, 5)
s_list = []
for _ in range(n):
    cur_s += randint(0, 5)
    s_list.append(cur_s)

a_list = [randint(1, 20) for _ in range(n)]

io.input_writeln(" ".join(map(str, s_list)))
io.input_writeln(" ".join(map(str, a_list)))
