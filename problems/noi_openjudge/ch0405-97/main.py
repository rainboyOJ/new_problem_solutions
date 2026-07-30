catalan = [1]
for nodes in range(1, 20):
    catalan.append(sum(catalan[left] * catalan[nodes - 1 - left] for left in range(nodes)))


def build(nodes: int, rank: int) -> str:
    if nodes == 0:
        return ""
    for left_nodes in range(nodes):
        right_nodes = nodes - 1 - left_nodes
        block = catalan[left_nodes] * catalan[right_nodes]
        if rank >= block:
            rank -= block
            continue
        left_rank, right_rank = divmod(rank, catalan[right_nodes])
        left = build(left_nodes, left_rank)
        right = build(right_nodes, right_rank)
        return (f"({left})" if left else "") + "X" + (f"({right})" if right else "")
    raise ValueError("invalid rank")


prefix = 0
for value in iter(input, "0"):
    order = int(value)
    nodes = 1
    previous_total = 0
    while previous_total + catalan[nodes] < order:
        previous_total += catalan[nodes]
        nodes += 1
    print(build(nodes, order - previous_total - 1))
