#!/usr/bin/env python3
"""验收「新建题解」批次的产出契约（配套 docs/plans/roj-missing-analysis-283-batch.md）。

对每个题目目录检查：
  1. 恰好 4 个必需文件：problem.md / main.cpp / main.py / index.md
  2. problem.md 与素材源 new_ROJ/problems/<id>/content.md 逐字节一致
  3. index.md frontmatter 字段齐全、date/updated 格式合法、description 非空
  4. index.md 同时引用 main.py 与 main.cpp（本仓库「两种都展示」规范）
  5. index.md 有 [[TOC]] 与 ## 总结
  6. 题目目录里没有混进测试数据（*.in / *.out）
  7. include-code 指向的文件真实存在

用法：
    python3 scripts/problem-analysis-tools/check_new_analysis.py 1125 1222
    python3 scripts/problem-analysis-tools/check_new_analysis.py --manifest .tmp/roj283-manifest.json
    python3 scripts/problem-analysis-tools/check_new_analysis.py --manifest .tmp/roj283-manifest.json --json
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import pathlib
import re
import shutil
import subprocess
import sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
from datafiles import find_inputs, find_output_for  # noqa: E402
import spj_registry  # noqa: E402


def _spj_ok(pid: str, in_file: pathlib.Path, got: bytes, want: bytes) -> bool:
    """多解题：首次逐 token 比对失败时，用该题自己的判定器验合法性。

    ⚠ 不是「放水」：判定器必须独立验证 got 的合法性
      （如 3072 是「模拟操作序列看是否到达目标态」），而不是变相比较 got 与 want。
    """
    if not spj_registry.available(pid):
        return False
    inp = in_file.read_text(encoding="utf-8", errors="replace")
    verdict = spj_registry.check(pid, inp, got.decode("utf-8", "replace"),
                                 want.decode("utf-8", "replace"))
    return bool(verdict and verdict[0])

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
SOURCE_ROOT = REPO_ROOT.parent / "new_ROJ" / "problems"

REQUIRED_FILES = ("problem.md", "main.cpp", "main.py", "index.md")
REQUIRED_FM = (
    "oj", "problem_id", "title", "description", "difficulty", "date", "updated",
    "toc", "tags", "favorite", "favorite_reason", "categories", "showAtRbook",
    "pre", "common", "recommend", "source",
)
STAMP_RE = re.compile(r"^\d{4}-\d{2}-\d{2} \d{2}:\d{2}$")
DIFFICULTIES = {
    "入门", "普及-", "普及", "普及+/提高-", "提高", "提高+/省选-", "省选/NOI-", "未知",
}


def frontmatter_field(text: str, name: str) -> str | None:
    block = re.match(r"^---\n(.*?)\n---\n", text, re.S)
    if not block:
        return None
    match = re.search(rf"^{name}:[ \t]*(.*)$", block.group(1), re.M)
    return match.group(1).strip() if match else None


def md5(path: pathlib.Path) -> str:
    return hashlib.md5(path.read_bytes()).hexdigest()


def check_one(pid: str) -> dict:
    problems: list[str] = []
    d = REPO_ROOT / "problems" / "roj" / pid

    if not d.is_dir():
        return {"pid": pid, "ok": False, "problems": ["题目目录不存在"]}

    present = {f for f in REQUIRED_FILES if (d / f).is_file()}
    for f in REQUIRED_FILES:
        if f not in present:
            problems.append(f"缺文件 {f}")
    if not present:
        return {"pid": pid, "ok": False, "problems": problems}

    # 1. problem.md 与素材源一致
    src = SOURCE_ROOT / pid / "content.md"
    if (d / "problem.md").is_file():
        if not src.is_file():
            problems.append(f"素材源缺 content.md，problem.md 无法比对（{src}）")
        elif md5(d / "problem.md") != md5(src):
            problems.append("problem.md 与 new_ROJ/problems/%s/content.md 不一致" % pid)

    # 2. 没有混进测试数据（大小写不敏感：*.in / *.IN / *.out / *.OUT）
    strays = sorted(p.name for p in d.iterdir()
                    if p.is_file() and p.suffix.lower() in (".in", ".out"))
    if strays:
        problems.append(f"题目目录混进测试数据: {strays[:5]}")
    if (d / "data").is_dir():
        problems.append("题目目录不该有 data/ 子目录")

    index = d / "index.md"
    if index.is_file():
        text = index.read_text(encoding="utf-8")

        # 3. frontmatter
        block = re.match(r"^---\n(.*?)\n---\n", text, re.S)
        if not block:
            problems.append("index.md 缺 frontmatter")
        else:
            for name in REQUIRED_FM:
                if frontmatter_field(text, name) is None:
                    problems.append(f"frontmatter 缺字段 {name}")
            for name in ("date", "updated"):
                value = frontmatter_field(text, name)
                if value is not None and not STAMP_RE.match(value.strip('"\'')):
                    problems.append(f"{name} 格式不是 YYYY-MM-DD HH:MM: {value!r}")
            if frontmatter_field(text, "date") and frontmatter_field(text, "date") != frontmatter_field(text, "updated"):
                problems.append("date 与 updated 不相等（新建题解应相等）")
            desc = (frontmatter_field(text, "description") or "").strip('"\'')
            if not desc:
                problems.append("description 为空")
            diff = (frontmatter_field(text, "difficulty") or "").strip('"\'')
            if diff and diff not in DIFFICULTIES:
                problems.append(f"difficulty 取值非法: {diff!r}")
            if frontmatter_field(text, "toc") not in ("true", "True"):
                problems.append("toc 不是 true")

        # 4. 两种代码都引用
        if "include-code(./main.py" not in text:
            problems.append("index.md 没有引用 main.py")
        if "include-code(./main.cpp" not in text:
            problems.append("index.md 没有引用 main.cpp")

        # 5. 骨架
        if "[[TOC]]" not in text:
            problems.append("index.md 缺 [[TOC]]")
        if not re.search(r"^## 总结", text, re.M):
            problems.append("index.md 缺 ## 总结")
        if not re.search(r"^## (形式化题目|题目描述)", text, re.M):
            problems.append("index.md 缺 ## 形式化题目 / ## 题目描述")

        # 6. include-code 目标存在
        for target in re.findall(r"@include-code\(([^,)]+)", text):
            target = target.strip()
            if not (d / target).is_file():
                problems.append(f"include-code 指向不存在的文件: {target}")

    return {"pid": pid, "ok": not problems, "problems": problems}


def main() -> int:
    parser = argparse.ArgumentParser(description="验收新建题解的产出契约")
    parser.add_argument("pids", nargs="*")
    parser.add_argument("--manifest", help="manifest JSON，取其中所有 pid")
    parser.add_argument("--json", action="store_true")
    parser.add_argument("--quiet-ok", action="store_true", help="只打印失败的题")
    parser.add_argument("--realdata", action="store_true",
                        help="契约通过后再拿随仓 data/ 实跑 main.cpp 与 main.py")
    parser.add_argument("--timeout", type=int, default=15, help="单点运行超时秒数（--realdata）")
    parser.add_argument("--strict-py", action="store_true",
                        help="main.py 超时即失败（默认豁免，见 _run_realdata 注释）")
    args = parser.parse_args()

    pids = list(args.pids)
    if args.manifest:
        payload = json.loads((REPO_ROOT / args.manifest).read_text(encoding="utf-8"))
        pids += [str(r["pid"]) for r in payload]
    if not pids:
        parser.error("需要 pid 或 --manifest")

    results = [check_one(pid) for pid in dict.fromkeys(pids)]

    if args.realdata:
        for r in results:
            if not r["ok"]:
                r["realdata"] = "跳过（契约未过）"
                continue
            try:
                ok, detail = _run_realdata(r["pid"], args.timeout, not args.quiet_ok,
                                           strict_py=args.strict_py)
            except Exception as error:  # 验证本身出错也要算失败，不能静默放行
                ok, detail = False, f"验证异常: {error}"
            r["realdata"] = detail
            if not ok:
                r["ok"] = False
                r["problems"].append(f"真实数据: {detail}")

    failed = [r for r in results if not r["ok"]]

    if args.json:
        print(json.dumps({"total": len(results), "failed": len(failed), "results": results},
                         ensure_ascii=False, indent=1))
        return 1 if failed else 0

    for r in results:
        if r["ok"] and args.quiet_ok:
            continue
        mark = "✅" if r["ok"] else "❌"
        extra = f"   [{r['realdata']}]" if r.get("realdata") else ""
        print(f"{mark} {r['pid']}{extra}")
        for p in r["problems"]:
            print(f"     - {p}")
    print(f"\n合计 {len(results)} 道：通过 {len(results) - len(failed)}，失败 {len(failed)}")
    return 1 if failed else 0


# ── 真实数据验证（--realdata）────────────────────────────────────────────────
# 契约检查只看文件长相，看不出代码对不对。这里在契约通过后再拿随仓数据实跑：
#   main.cpp 走 check_sample.py（它会自动选 g++-16）
#   main.py  逐点跑并与 .out 逐字节比对
# 题目目录按约定不放测试数据，所以一切都在 /tmp/pv-<pid>/ 里进行。

# 【Python 解释器】
# main.py 按项目约定使用 `type X = ...` 别名（python-oj-short），这需要 **Python 3.12+**。
# 而 macOS 自带的 `/usr/bin/python3` 是 **3.9**，拿它跑会把好代码误判成错。
# 所以不直接信任 `sys.executable`，而是**优先挑一个够新的解释器**。

_PY_MIN = (3, 12)
_PY_CANDIDATES = (
    "/opt/homebrew/bin/python3.14", "/opt/homebrew/bin/python3.13",
    "/opt/homebrew/bin/python3.12", "/opt/homebrew/bin/python3",
    "python3.14", "python3.13", "python3.12", "python3",
)
_py_cache: str | None = None


def py_interpreter() -> str:
    """返回一个 >= 3.12 的 Python 解释器路径（找不到就退回 sys.executable）。

    做法很笨但可靠：**逐个候选真跑一次**，谁够新就用谁。不靠路径判断
    （macOS 上多个 `python3` 同名不同版，用 `os.path.exists` 容易踩坑）。
    python-oj-short 约定用 `type X = ...`，需要 3.12+。
    """
    global _py_cache
    if _py_cache:
        return _py_cache

    def usable(path: str) -> bool:
        try:
            r = subprocess.run([path, "-c", "import sys; print(*sys.version_info[:2])"],
                               capture_output=True, text=True, timeout=15)
        except Exception:
            return False
        parts = r.stdout.split()
        return (r.returncode == 0 and len(parts) == 2
                and (int(parts[0]), int(parts[1])) >= _PY_MIN)

    cands = list(_PY_CANDIDATES)
    if sys.version_info >= _PY_MIN:
        cands.insert(0, sys.executable)     # 当前解释器就够新，优先用自己
    for cand in cands:
        path = cand if os.path.isabs(cand) else (shutil.which(cand) or "")
        if path and usable(path):
            _py_cache = path
            return _py_cache

    print(f"⚠️ 找不到 >= {_PY_MIN[0]}.{_PY_MIN[1]} 的 Python，"
          f"只好用 {sys.executable}（{sys.version.split()[0]}）—— main.py 可能误判",
          file=sys.stderr)
    _py_cache = sys.executable
    return _py_cache
#
# 【main.py 的 Python TLE 豁免】
# 项目 skill `python-oj-short` 明确写着「允许 Python TLE/MLE，但绝不能因此把算法
# 换成暴力枚举」。而很多题目的算法原语（线段树、堆操作、逐元素循环）在 CPython
# 里根本进不了 15 秒 —— 这不是解法错，是语言开销。
#
# 所以默认策略是：
#   - **main.cpp 每个点都必须 PASS**（它才是真解法，硬指标）
#   - main.py 在超时内跑完的点，输出必须**完全正确**
#   - main.py 超时的点记为 TLE，**不算失败**，但会写进报表
#   - **至少要有 1 个点真正跑通** —— 否则无法证明 main.py 能跑
#
# ⚠ 这个豁免放宽了“整体正确性”的保证：如果 main.py 算法错，却恰好在大点上超时、
#   只在小点上蒙对，闸门拦不住。**补救手段是 worker 的小数据对拍**
#   （与 main.cpp 在 n 很小、能真正跑完的随机数据上对拍），那才是强证据。
#   需要严格把关时用 --strict-py。


def _run_realdata(pid: str, timeout: int, verbose: bool,
                  strict_py: bool = False) -> tuple[bool, str]:
    import shutil
    import subprocess
    import tempfile

    src_dir = SOURCE_ROOT / pid / "data"
    if not src_dir.is_dir():
        return True, "无 data/（跳过）"
    ins = find_inputs(src_dir)
    if not ins:
        return True, "data/ 为空（跳过）"

    prob = REPO_ROOT / "problems" / "roj" / pid
    work = pathlib.Path(tempfile.gettempdir()) / f"pv-{pid}"
    if work.exists():
        shutil.rmtree(work)
    (work / "data").mkdir(parents=True)
    for f in src_dir.iterdir():
        shutil.copy2(f, work / "data" / f.name)
    shutil.copy2(prob / "main.cpp", work / "main.cpp")

    checker = REPO_ROOT / "scripts" / "problem-analysis-tools" / "check_sample.py"
    # ⚠ 临时目录名是 pv-<pid>，而 spj_registry 是按**题号**找 <pid>.py 的，
    #   所以必须把真实 pid 显式传给 check_sample（否则 spj 永远不生效）。
    proc = subprocess.run([py_interpreter(), str(checker), str(work), "--pid", pid],
                          capture_output=True, text=True, timeout=timeout * (len(ins) + 2))
    tail = proc.stdout.strip().splitlines()[-1] if proc.stdout.strip() else proc.stderr.strip()[-200:]
    cpp_ok = "FAIL=0" in proc.stdout and "NO_ANSWER=0" in proc.stdout

    py_path = prob / "main.py"
    py_pass = py_fail = py_tle = 0
    py_failures: list[str] = []
    py_tles: list[str] = []
    for in_file in ins:
        # ⚠ 不能用 in_file.with_suffix(".out")：对 SNOW1.IN 会去找 SNOW1.out，
        # 而实际文件名是 SNOW1.OUT。必须按 stem 大小写不敏感地配对。
        out_file = find_output_for(in_file)
        if out_file is None:
            continue
        try:
            r = subprocess.run([py_interpreter(), str(py_path)], stdin=open(in_file, "rb"),
                               capture_output=True, timeout=timeout)
            got = r.stdout
        except subprocess.TimeoutExpired:
            py_tle += 1
            py_tles.append(in_file.name)
            continue
        want = out_file.read_bytes()
        if got.split() == want.split() or _spj_ok(pid, in_file, got, want):
            py_pass += 1
        else:
            py_fail += 1
            py_failures.append(in_file.name)

    # main.py 的判定：写错的点不容忍；超时的点默认豁免；但必须至少跑通一个点
    py_ok = py_fail == 0 and (py_pass >= 1 or not ins)
    if strict_py and py_tle:
        py_ok = False
    ok = cpp_ok and py_ok

    detail = f"main.cpp {'✅' if cpp_ok else '❌'} ({tail}) · main.py {py_pass}/{py_pass + py_fail} 通过"
    if py_tles:
        shown = ",".join(py_tles[:3]) + ("…" if len(py_tles) > 3 else "")
        detail += f"，{py_tle} 点 TLE({shown})" + (" [--strict-py 下判失败]" if strict_py else " [豁免]")
    if py_failures:
        detail += f" 失败点 {','.join(py_failures[:3])}"
    if py_pass == 0 and ins:
        detail += " ⚠ main.py 一个点都没跑通"
    return ok, detail


if __name__ == "__main__":
    sys.exit(main())
