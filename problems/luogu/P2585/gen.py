#!/usr/bin/env python3
import random
import sys

# 控制生成树的节点数不超过 max_nodes (例如 10)
def gen_tree(remaining_nodes):
    if remaining_nodes <= 1:
        return '0', 1
    # 随机选择当前节点的子节点数: 0, 1, 或 2
    # 为了保证不超过 remaining_nodes，如果 remaining_nodes < 3，不能选 2
    choices = [0, 1]
    if remaining_nodes >= 3:
        choices.append(2)
    
    choice = random.choice(choices)
    if choice == 0:
        return '0', 1
    elif choice == 1:
        sub_str, used = gen_tree(remaining_nodes - 1)
        return '1' + sub_str, used + 1
    else:
        # 分配给左右子树
        left_limit = remaining_nodes - 2
        # 左子树至少占 1 个节点，右子树至少占 1 个节点
        left_alloc = random.randint(1, left_limit)
        left_str, left_used = gen_tree(left_alloc)
        right_alloc = remaining_nodes - 1 - left_used
        right_str, right_used = gen_tree(right_alloc)
        return '2' + left_str + right_str, 1 + left_used + right_used

def main():
    max_nodes = 10
    tree_str, _ = gen_tree(max_nodes)
    print(tree_str)

if __name__ == '__main__':
    main()
