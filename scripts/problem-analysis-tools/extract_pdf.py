#!/usr/bin/env python3
"""从 `new_ROJ/problems/<pid>/content.pdf` 提取题面文本。

## 为什么需要它

`new_ROJ` 里有些题的题面是 **PDF**（不是 `content.md`）——
主要集中在 **D 组**（`10005` `10012` … `10019`）。
PDF 无法被 `read` 直接读取，必须先转成文本。

## 用法

```bash
# 提取一道题
python3 scripts/problem-analysis-tools/extract_pdf.py 10012

# 提取多道
python3 scripts/problem-analysis-tools/extract_pdf.py 10012 10013 10014

# 指定输出目录（默认 /tmp/roj-d-pdf/）
python3 scripts/problem-analysis-tools/extract_pdf.py 10012 --out /tmp/mypdf
```

输出：`<out>/<pid>.txt`

## 依赖

`pypdf`（已验证 6.19.0 可用）：

```bash
python3 -c "import pypdf; print(pypdf.__version__)"
```

## 注意事项

1. **中文可正常提取**（实测 `10012` 228 个中文字）。
2. ★ **页码是「整场比赛文档」的页码**（如 `共 11页` / `第 2 页`）——
   因为 ROJ 的 PDF 是从比赛文档里**切出来的单题片段**，
   所以**一份 PDF 通常只含一道题**（可用 `grep -c '题目描述'` 核实）。
   ★ 例外：`10013` 的提取文本里「题目描述」出现 **2 次** ⇒ 可能含两道题或排版重复。
3. 提取结果**可能丢失公式排版**（LaTeX 变成 Unicode 符号）⇒
   ★ 关键约束建议**对照 `std.cpp` 交叉确认**（D 组大多有 `std.cpp`）。
"""

from __future__ import annotations

import argparse
import pathlib
import sys

# scripts/problem-analysis-tools/extract_pdf.py
#   parents[0]=problem-analysis-tools  [1]=scripts  [2]=pcs2-roj-py  [3]=RBOOK_series
ROOT = pathlib.Path(__file__).resolve().parents[3]      # → …/RBOOK_series
NEW_ROJ = ROOT / "new_ROJ" / "problems"                 # → …/RBOOK_series/new_ROJ/problems


def extract(pid: str, out_dir: pathlib.Path) -> tuple[bool, str]:
    pdf = NEW_ROJ / pid / "content.pdf"
    if not pdf.is_file():
        return False, f"无 content.pdf（{pdf}）"
    try:
        from pypdf import PdfReader
    except ImportError:
        return False, "缺 pypdf（pip install pypdf）"
    try:
        reader = PdfReader(str(pdf))
        text = "\n".join((pg.extract_text() or "") for pg in reader.pages)
    except Exception as exc:  # noqa: BLE001
        return False, f"提取失败：{exc}"
    out_dir.mkdir(parents=True, exist_ok=True)
    dst = out_dir / f"{pid}.txt"
    dst.write_text(text, encoding="utf-8")
    cn = sum(1 for c in text if "\u4e00" <= c <= "\u9fff")
    n_title = text.count("题目描述")
    note = f" · 题目描述×{n_title}" + ("（⚠ 可能含多题）" if n_title > 1 else "")
    return True, f"{len(reader.pages)} 页 · {len(text)} 字符 · 中文 {cn} 字{note} → {dst}"


def main() -> int:
    ap = argparse.ArgumentParser(description="提取 ROJ 题面 PDF 为文本")
    ap.add_argument("pids", nargs="+", help="题号，如 10012")
    ap.add_argument("--out", default="/tmp/roj-d-pdf", help="输出目录")
    args = ap.parse_args()

    out_dir = pathlib.Path(args.out)
    failed = 0
    for pid in args.pids:
        ok, msg = extract(pid, out_dir)
        print(f"  {'✅' if ok else '❌'} {pid}: {msg}")
        failed += 0 if ok else 1
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
