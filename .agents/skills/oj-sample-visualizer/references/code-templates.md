# 可视化脚本与文件模板

`oj-sample-visualizer` 的代码/文件模板。使用规则见 [SKILL.md](../SKILL.md)。

## `viz_render.py` 推荐骨架

```python
#!/usr/bin/env python3
"""当前题目专用的样例可视化脚本。"""

from __future__ import annotations

import argparse
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="生成当前题目的样例可视化素材。")
    parser.add_argument("--input", default="in1", help="样例输入文件，默认 in1。")
    parser.add_argument("--out-dir", default=".", help="输出目录，默认题目根目录。")
    args = parser.parse_args()

    problem_dir = Path.cwd()
    out_dir = (problem_dir / args.out_dir).resolve()
    out_dir.mkdir(parents=True, exist_ok=True)

    text = (problem_dir / args.input).read_text(encoding="utf-8")
    # TODO: 按当前题目的输入语义解析 text。
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
```

## `final-visualization.md` 文件模板

文件应只包含可直接移入 `index.md` 的内容：

````markdown
## 图示解析

这张图串起本题从建模到得到答案的主线：

```text
输入对象
`- 关键观察
   `- 选择算法
      `- 得到答案
````

先看每个节点代表的推理结论，再顺着分支检查它如何导向下一步。
图中只保留正文已经证明过的关键关系，不替代正文中的样例推演和正确性说明。
````
