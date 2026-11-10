import sys
import random
import string
from cyaron import IO, randint

# 生成器无输入，stdout 就是这组数据
io = IO(input_file=sys.stdout, disable_output=True)

# 随机决定生成合法数据还是非法数据
is_valid = (random.random() < 0.6)

# n 在 3 到 9 之间，进制 B = n - 1
n = randint(3, 9)
base = n - 1

# 选取 B 个不同的大写英文字母
all_letters = list(string.ascii_uppercase)
random.shuffle(all_letters)
letters = all_letters[:base]

# 随机给每个字母分配一个 0 ~ B-1 的数值
perm = list(range(base))
random.shuffle(perm)
val_map = {letters[i]: perm[i] for i in range(base)}
# 反向查找数值到字母
inv_map = {perm[i]: letters[i] for i in range(base)}

def encode_num(x, b):
    """将数字 x 转为 b 进制下的字母字符串"""
    if x == 0:
        return inv_map[0]
    digits = []
    while x > 0:
        digits.append(inv_map[x % b])
        x //= b
    return "".join(reversed(digits))

# 构造表格
table = [["" for _ in range(n)] for _ in range(n)]
table[0][0] = "+"
for j in range(1, n):
    table[0][j] = letters[j - 1]
    table[j][0] = letters[j - 1]

for i in range(1, n):
    for j in range(1, n):
        r_val = val_map[letters[i - 1]]
        c_val = val_map[letters[j - 1]]
        total = r_val + c_val
        table[i][j] = encode_num(total, base)

if not is_valid:
    # 随机进行扰动破坏：改某个单元格的值、或者加入非法字符
    mutation = randint(1, 3)
    if mutation == 1:
        # 修改某个加法结果
        ri = randint(1, n - 1)
        cj = randint(1, n - 1)
        table[ri][cj] = random.choice(letters) + random.choice(letters)
    elif mutation == 2:
        # 换成单个不匹配的字符
        ri = randint(1, n - 1)
        cj = randint(1, n - 1)
        table[ri][cj] = random.choice(letters)
    else:
        # 混入未知大写字母
        unknown = all_letters[base] if len(all_letters) > base else 'Z'
        ri = randint(1, n - 1)
        cj = randint(1, n - 1)
        table[ri][cj] = unknown

io.input_writeln(n)
for row in table:
    io.input_writeln(" ".join(row))
