import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 随机生成长度 26 到 50 的全大写字母串
alphabet = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
perm = list("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
random.shuffle(perm)

# 构造一个基本映射
mapping = {alphabet[i]: perm[i] for i in range(26)}

length = randint(26, 60)
plain_chars = [random.choice(alphabet) for _ in range(length)]

# 偶尔故意引入冲突
introduce_error = randint(0, 3) == 0

cipher_chars = []
for ch in plain_chars:
    cipher_chars.append(mapping[ch])

if introduce_error and len(cipher_chars) > 2:
    idx = randint(0, len(cipher_chars) - 1)
    cipher_chars[idx] = random.choice(alphabet)

cipher_str = "".join(cipher_chars)
plain_str = "".join(plain_chars)
query_str = "".join(random.choice(alphabet) for _ in range(randint(5, 20)))

io.input_writeln(cipher_str)
io.input_writeln(plain_str)
io.input_writeln(query_str)
