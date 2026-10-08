#!/usr/bin/env python3
"""字节级独立检查器：`main.cpp` / `main.py` 的输出与 `.out` 是否**逐字节**相同。

## 为什么需要它

`check_new_analysis.py` 的判定用的是 `got.split() == want.split()`
（token 级比较），它对**一切空白差异免疫**：

| 差异 | token 级比较 | 本脚本 |
|---|---|---|
| 空输出 **0 字节** vs **一个空行** | 相同（都 `[]`） | **不同** |
| 行尾多余空格 | 相同 | **不同** |
| token 之间多个空格 | 相同 | **不同** |
| `\\r\\n` vs `\\n` | 相同 | **不同** |

`5044` 实测：把「全 0 矩阵输出 0 字节」改成「输出一个空行」，
`check_sample.py` 仍报 `PASS=10, FAIL=0` —— **假绿灯**。

⇒ 本脚本是**独立**的第二把尺子。凡题面/数据对**格式**有要求
（空输出、行尾空格、分隔符宽度）的题，都应跑一次。

## 用法

    python3 check_bytes.py <pid> [<pid> ...]
    python3 check_bytes.py --quiet <pid>       # 只报不一致的点

退出码：0 = 全部逐字节一致；1 = 有不一致或运行失败。
"""
from __future__ import annotations

import argparse
import pathlib
import subprocess
import sys

REPO_ROOT = pathlib.Path(__file__).resolve().parents[2]
NEW_ROJ = REPO_ROOT.parent / "new_ROJ"
DATA_DIR = NEW_ROJ / "problems"


def gpp() -> str:
    for cand in ("/opt/homebrew/bin/g++-16", "/opt/homebrew/bin/g++-15",
                 "/opt/homebrew/bin/g++-14", "g++-16", "g++"):
        try:
            r = subprocess.run([cand, "--version"], capture_output=True, timeout=20)
            if r.returncode == 0:
                return cand
        except Exception:
            continue
    raise SystemExit("⛔ 找不到可用的 g++")


def py_interpreter() -> str:
    for cand in ("/opt/homebrew/bin/python3.14", "/opt/homebrew/bin/python3.13",
                 "/opt/homebrew/bin/python3.12", sys.executable):
        try:
            r = subprocess.run([cand, "-c", "import sys; print(*sys.version_info[:2])"],
                               capture_output=True, text=True, timeout=15)
            if r.returncode == 0 and r.stdout.split()[0] == "3" and int(r.stdout.split()[1]) >= 12:
                return cand
        except Exception:
            continue
    return sys.executable


def find_points(pid: str, problems_dir: pathlib.Path) -> list[tuple[pathlib.Path, pathlib.Path]]:
    """返回 [(in_file, out_file), ...]，大小写不敏感地配对 .in/.out。"""
    d = DATA_DIR / pid / "data"
    if not d.is_dir():
        return []
    by_stem: dict[str, dict[str, pathlib.Path]] = {}
    for f in d.iterdir():
        if not f.is_file():
            continue
        suf = f.suffix.lower()
        if suf in (".in", ".out"):
            by_stem.setdefault(f.stem.lower(), {})[suf] = f
    return [(v[".in"], v[".out"]) for _, v in sorted(by_stem.items())
            if ".in" in v and ".out" in v]


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("pids", nargs="+")
    ap.add_argument("--quiet", action="store_true", help="只打印不一致的点")
    ap.add_argument("--timeout", type=float, default=20.0, help="单点超时秒数")
    args = ap.parse_args()

    compiler = gpp()
    pyi = py_interpreter()
    bad_total = 0

    for pid in args.pids:
        pdir = REPO_ROOT / "problems" / "roj" / pid
        cpp, pyf = pdir / "main.cpp", pdir / "main.py"
        if not cpp.is_file():
            print(f"⛔ {pid}：缺 main.cpp")
            bad_total += 1
            continue
        pts = find_points(pid, pdir)
        if not pts:
            print(f"⛔ {pid}：data/ 里没有 .in/.out 配对")
            bad_total += 1
            continue

        exe = pathlib.Path("/tmp") / f"_cbytes_{pid}"
        r = subprocess.run([compiler, "-O2", "-std=c++17", "-o", str(exe), str(cpp)],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(f"⛔ {pid}：main.cpp 编译失败\n{r.stderr[:400]}")
            bad_total += 1
            continue

        rows = []
        for in_f, out_f in pts:
            want = out_f.read_bytes()
            got_c = _run([str(exe)], in_f, args.timeout)
            got_p = _run([pyi, str(pyf)], in_f, args.timeout) if pyf.is_file() else None
            rows.append((in_f.name, want,
                         "ok" if got_c == want else _why(got_c, want),
                         "ok" if got_p == want else (_why(got_p, want) if got_p is not None else "n/a"),
                         got_c, got_p, want))

        nbad_c = sum(1 for r_ in rows if r_[2] != "ok")
        nbad_p = sum(1 for r_ in rows if r_[3] not in ("ok", "n/a"))
        flag = "✅" if (nbad_c == 0 and nbad_p == 0) else "❌"
        if not args.quiet or flag == "❌":
            print(f"{flag} {pid}  {len(rows)} 点："
                  f"main.cpp 逐字节 {len(rows) - nbad_c}/{len(rows)} · "
                  f"main.py 逐字节 {len(rows) - nbad_p}/{len(rows)}")
        for name, want, wc, wp, gc, gp, _ in rows:
            if wc != "ok" or wp != "ok":
                bad_total += 1
                print(f"    {name}: cpp={wc}  py={wp}")
                if gc is not None and wc != "ok":
                    print(f"      got ={_show(gc)}\n      want={_show(want)}")
    if bad_total:
        raise SystemExit(1)


def _run(cmd: list[str], in_f: pathlib.Path, timeout: float) -> bytes | None:
    try:
        with open(in_f, "rb") as fh:
            r = subprocess.run(cmd, stdin=fh, capture_output=True, timeout=timeout)
        return r.stdout
    except subprocess.TimeoutExpired:
        return b"<TIMEOUT>"
    except Exception as e:  # pragma: no cover
        return f"<ERROR {e}>".encode()


def _show(b: bytes, limit: int = 60) -> str:
    s = repr(b)
    return s if len(s) <= limit else s[:limit] + f"…({len(b)}B)"


def _why(got: bytes | None, want: bytes) -> str:
    """给出人类可读的差异分类。"""
    if got is None:
        return "n/a"
    if got == b"<TIMEOUT>":
        return "TLE"
    if got.strip() == want.strip():
        if len(got) != len(want):
            return f"字节数不同({len(got)}B vs {len(want)}B)"
        return "空白差异"
    return "内容不同"


if __name__ == "__main__":
    main()
