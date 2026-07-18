from itertools import pairwise

preorder = input().strip()
postorder = input().strip()
position = {node: index for index, node in enumerate(postorder)}
ambiguous = sum(
    position[parent] == position[child] + 1
    for parent, child in pairwise(preorder)
)

print(1 << ambiguous)
