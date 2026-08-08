# duipai-human.py

位置：

```text
scripts/problem-analysis-tools/duipai-human.py
```

作用：给人手动使用的交互式对拍 wrapper。它只负责询问参数，最终调用 `duipai.py`。

## 基本用法

在题目目录中运行：

```bash
cd problems/luogu/P1001
python3 ../../../scripts/problem-analysis-tools/duipai-human.py
```

默认会优先使用当前目录中的：

```text
gen.py
main.cpp
brute.cpp
```

如果默认文件不存在，可以在交互提示中手动输入文件名。

## 适用场景

- 手动写题时快速启动对拍。
- 不想每次输入完整 `duipai.py --gen ... --user ... --brute ...` 命令。
- 不适合 Agent 自动调用；Agent 应该直接使用 `duipai.py`。
