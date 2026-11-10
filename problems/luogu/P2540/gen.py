import sys
import random
from cyaron import IO, randint

io = IO(input_file=sys.stdout, disable_output=True)

# 针对对拍生成 1 组数据，手牌张数 n 在 4 到 15 之间
T = 1
n = randint(4, 15)
io.input_writeln(f"{T} {n}")

# 构造一副牌的牌堆
deck = []
# 3~K (3~13), A (1), 2 (2)，每种4张花色(1~4)
for rank in range(1, 14):
    for suit in range(1, 5):
        deck.append((rank, suit))
# 大小王
deck.append((0, 1))
deck.append((0, 2))

random.shuffle(deck)
hand = deck[:n]

for card in hand:
    io.input_writeln(f"{card[0]} {card[1]}")
