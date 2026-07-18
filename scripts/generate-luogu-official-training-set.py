#!/usr/bin/env python3
"""Generate repository problem sets for Luogu's official training collections."""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from http.cookiejar import CookieJar
import json
import math
import os
from pathlib import Path
import re
import sys
import tempfile
import time
from typing import Any
from urllib.error import HTTPError, URLError
from urllib.parse import urljoin
from urllib.request import HTTPCookieProcessor, Request, build_opener


REPO_ROOT = Path(__file__).resolve().parents[1]
LUOGU_ORIGIN = "https://www.luogu.com.cn"
MAX_ATTEMPTS = 3
PID_PATTERN = re.compile(r"^[A-Za-z0-9][A-Za-z0-9_-]*$")


class GenerationError(RuntimeError):
    pass


@dataclass(frozen=True)
class CollectionConfig:
    key: str
    training_type: str
    output: Path
    title: str
    description: str
    default_order: float
    require_official_provider: bool = True

    @property
    def source_url(self) -> str:
        return f"{LUOGU_ORIGIN}/training/list?type={self.training_type}"


COLLECTIONS = {
    "basic": CollectionConfig(
        key="basic",
        training_type="srqc-jc",
        output=REPO_ROOT / "problem-sets" / "luogu-official-basic-training.md",
        title="洛谷官方入门与基础算法题单",
        description="按洛谷官方入门与基础算法训练题单整理的完整练习路径。",
        default_order=35.0,
    ),
    "advanced": CollectionConfig(
        key="advanced",
        training_type="srqc-jj",
        output=REPO_ROOT / "problem-sets" / "luogu-official-advanced-training.md",
        title="洛谷官方深入浅出进阶篇题单",
        description="按洛谷官方深入浅出进阶篇训练题单整理的完整练习路径。",
        default_order=36.0,
    ),
    "luoyongjun": CollectionConfig(
        key="luoyongjun",
        training_type="book.luoyongjun",
        output=REPO_ROOT / "problem-sets" / "luogu-luoyongjun.md",
        title="罗勇军《算法竞赛》题单",
        description="按洛谷罗勇军《算法竞赛》书籍题单整理的完整练习路径。",
        default_order=37.0,
        require_official_provider=False,
    ),
    "jinjiezhinan": CollectionConfig(
        key="jinjiezhinan",
        training_type="book.jinjiezhinan",
        output=REPO_ROOT / "problem-sets" / "luogu-jinjiezhinan.md",
        title="李煜东《算法竞赛进阶指南》题单",
        description="按洛谷李煜东《算法竞赛进阶指南》题单整理的完整练习路径。",
        default_order=38.0,
        require_official_provider=False,
    ),
}


@dataclass(frozen=True)
class Problem:
    pid: str
    name: str


@dataclass(frozen=True)
class Training:
    training_id: int
    name: str
    problems: tuple[Problem, ...]


class LuoguClient:
    def __init__(
        self,
        base_url: str = LUOGU_ORIGIN,
        *,
        timeout: int = 20,
        max_attempts: int = MAX_ATTEMPTS,
    ) -> None:
        self.base_url = base_url.rstrip("/") + "/"
        self.timeout = timeout
        self.max_attempts = max_attempts
        self.opener = build_opener(HTTPCookieProcessor(CookieJar()))

    def get_json(self, path: str) -> dict[str, Any]:
        url = urljoin(self.base_url, path.lstrip("/"))
        last_error: Exception | None = None
        for attempt in range(1, self.max_attempts + 1):
            try:
                request = Request(
                    url,
                    headers={
                        "User-Agent": (
                            "Mozilla/5.0 (X11; Linux x86_64) "
                            "AppleWebKit/537.36 (KHTML, like Gecko) "
                            "Chrome/120.0 Safari/537.36"
                        ),
                        "Accept": "application/json,text/plain,*/*",
                        "x-lentille-request": "content-only",
                    },
                )
                with self.opener.open(request, timeout=self.timeout) as response:
                    charset = response.headers.get_content_charset() or "utf-8"
                    body = response.read().decode(charset, errors="strict")
                try:
                    payload = json.loads(body)
                except json.JSONDecodeError as exc:
                    raise GenerationError(f"洛谷响应不是有效 JSON：{url}: {exc}") from exc
                if not isinstance(payload, dict):
                    raise GenerationError(f"洛谷响应根节点不是对象：{url}")
                if payload.get("status") != 200:
                    raise GenerationError(
                        f"洛谷响应状态异常：{url}: {payload.get('status')!r}"
                    )
                return payload
            except GenerationError:
                raise
            except (HTTPError, URLError, TimeoutError, UnicodeError) as exc:
                last_error = exc
                if attempt < self.max_attempts:
                    time.sleep(0.5 * (2 ** (attempt - 1)))
        raise GenerationError(
            f"请求洛谷失败，重试 {self.max_attempts} 次后仍不可用：{url}: {last_error}"
        )


def require_official_provider(provider: Any, context: str) -> None:
    if not isinstance(provider, dict):
        raise GenerationError(f"{context} 缺少 provider。")
    if provider.get("uid") != 3 or provider.get("name") != "洛谷":
        raise GenerationError(f"{context} 不是洛谷官方题单。")


def parse_training_list(
    payload: dict[str, Any],
    *,
    check_official_provider: bool = True,
) -> list[dict[str, Any]]:
    if payload.get("template") != "training.list":
        raise GenerationError("列表响应 template 不是 training.list。")
    trainings = payload.get("data", {}).get("trainings", {})
    raw_items = trainings.get("result") if isinstance(trainings, dict) else None
    if not isinstance(raw_items, list) or not raw_items:
        raise GenerationError("列表响应中没有子题单。")
    total_count = trainings.get("count")
    per_page = trainings.get("perPage")
    if not isinstance(total_count, int) or total_count < len(raw_items):
        raise GenerationError("列表响应 count 与当前页数据不一致。")
    if not isinstance(per_page, int) or per_page <= 0 or len(raw_items) > per_page:
        raise GenerationError("列表响应 perPage 与当前页数据不一致。")

    summaries: list[dict[str, Any]] = []
    seen_ids: set[int] = set()
    for raw in raw_items:
        if not isinstance(raw, dict):
            raise GenerationError("子题单摘要不是对象。")
        training_id = raw.get("id")
        name = raw.get("name")
        problem_count = raw.get("problemCount")
        if not isinstance(training_id, int) or training_id <= 0:
            raise GenerationError(f"子题单 ID 无效：{training_id!r}")
        if training_id in seen_ids:
            raise GenerationError(f"子题单 ID 重复：{training_id}")
        if not isinstance(name, str) or not name.strip():
            raise GenerationError(f"子题单 {training_id} 名称为空。")
        if not isinstance(problem_count, int) or problem_count < 0:
            raise GenerationError(f"子题单 {training_id} problemCount 无效。")
        if check_official_provider:
            require_official_provider(raw.get("provider"), f"子题单 {training_id}")
        seen_ids.add(training_id)
        summaries.append(
            {
                "id": training_id,
                "name": name.strip(),
                "problemCount": problem_count,
            }
        )
    return summaries


def training_list_total(payload: dict[str, Any]) -> int:
    trainings = payload.get("data", {}).get("trainings", {})
    total_count = trainings.get("count") if isinstance(trainings, dict) else None
    if not isinstance(total_count, int) or total_count <= 0:
        raise GenerationError("列表响应 count 无效。")
    return total_count


def parse_training_detail(
    payload: dict[str, Any],
    summary: dict[str, Any],
    *,
    check_official_provider: bool = True,
) -> Training:
    if payload.get("template") != "training.show":
        raise GenerationError(f"子题单 {summary['id']} 响应 template 不是 training.show。")
    raw = payload.get("data", {}).get("training")
    if not isinstance(raw, dict):
        raise GenerationError(f"子题单 {summary['id']} 缺少 training 对象。")

    training_id = raw.get("id")
    name = raw.get("name")
    if training_id != summary["id"]:
        raise GenerationError(
            f"子题单 ID 不一致：列表为 {summary['id']}，详情为 {training_id!r}。"
        )
    if not isinstance(name, str) or not name.strip():
        raise GenerationError(f"子题单 {training_id} 名称为空。")
    if name.strip() != summary["name"]:
        raise GenerationError(f"子题单 {training_id} 列表与详情名称不一致。")
    if check_official_provider:
        require_official_provider(raw.get("provider"), f"子题单 {training_id}")

    raw_problems = raw.get("problems")
    if not isinstance(raw_problems, list):
        raise GenerationError(f"子题单 {training_id} problems 不是数组。")
    declared_count = raw.get("problemCount")
    if declared_count != summary["problemCount"] or declared_count != len(raw_problems):
        raise GenerationError(
            f"子题单 {training_id} 题目数不一致："
            f"列表 {summary['problemCount']}，详情 {declared_count!r}，实际 {len(raw_problems)}。"
        )

    problems: list[Problem] = []
    seen_pids: set[str] = set()
    for raw_problem in raw_problems:
        if not isinstance(raw_problem, dict):
            raise GenerationError(f"子题单 {training_id} 包含非对象题目。")
        pid = raw_problem.get("pid")
        problem_name = raw_problem.get("name")
        if not isinstance(pid, str) or not PID_PATTERN.fullmatch(pid):
            raise GenerationError(f"子题单 {training_id} 包含无效题号：{pid!r}")
        if pid in seen_pids:
            raise GenerationError(f"子题单 {training_id} 内题号重复：{pid}")
        if not isinstance(problem_name, str) or not problem_name.strip():
            raise GenerationError(f"子题单 {training_id} 的 {pid} 标题为空。")
        seen_pids.add(pid)
        problems.append(Problem(pid=pid, name=problem_name.strip()))

    return Training(training_id=training_id, name=name.strip(), problems=tuple(problems))


def load_trainings(client: LuoguClient, collection: CollectionConfig) -> list[Training]:
    summaries: list[dict[str, Any]] = []
    seen_ids: set[int] = set()
    page = 1
    total_count: int | None = None
    while total_count is None or len(summaries) < total_count:
        list_payload = client.get_json(
            f"/training/list?type={collection.training_type}&page={page}&_contentOnly=1"
        )
        page_summaries = parse_training_list(
            list_payload,
            check_official_provider=collection.require_official_provider,
        )
        page_total = training_list_total(list_payload)
        if total_count is None:
            total_count = page_total
        elif total_count != page_total:
            raise GenerationError("列表分页之间的 count 不一致。")
        for summary in page_summaries:
            if summary["id"] in seen_ids:
                raise GenerationError(f"列表分页之间子题单 ID 重复：{summary['id']}")
            seen_ids.add(summary["id"])
            summaries.append(summary)
        if len(summaries) > total_count:
            raise GenerationError("列表分页返回的子题单数量超过 count。")
        page += 1

    trainings: list[Training] = []
    for index, summary in enumerate(summaries, start=1):
        print(
            f"\rFetching Luogu {collection.key} trainings: {index}/{len(summaries)}",
            end="",
            flush=True,
        )
        detail = client.get_json(f"/training/{summary['id']}?_contentOnly=1")
        trainings.append(
            parse_training_detail(
                detail,
                summary,
                check_official_provider=collection.require_official_provider,
            )
        )
    print()
    return trainings


def problem_stats(trainings: list[Training]) -> dict[str, int]:
    counts: dict[str, int] = {}
    entries = 0
    for training in trainings:
        for problem in training.problems:
            entries += 1
            counts[problem.pid] = counts.get(problem.pid, 0) + 1
    repeated_ids = sum(1 for count in counts.values() if count > 1)
    extra_occurrences = sum(count - 1 for count in counts.values() if count > 1)
    return {
        "training_count": len(trainings),
        "entry_count": entries,
        "distinct_count": len(counts),
        "repeated_id_count": repeated_ids,
        "extra_occurrence_count": extra_occurrences,
    }


def markdown_text(value: str) -> str:
    return re.sub(r"([\\`*_[\]<>#])", r"\\\1", value)


def format_order(order: float) -> str:
    numeric_order = float(order)
    return str(int(numeric_order)) if numeric_order.is_integer() else str(numeric_order)


def existing_order(path: Path) -> float | None:
    if not path.exists():
        return None
    text = path.read_text(encoding="utf-8")
    match = re.search(
        r"^order:\s*([-+]?(?:\d+(?:\.\d*)?|\.\d+))\s*$",
        text,
        flags=re.M,
    )
    if not match:
        return None
    value = float(match.group(1))
    return value if math.isfinite(value) else None


def render_markdown(
    trainings: list[Training], collection: CollectionConfig, order: float
) -> str:
    stats = problem_stats(trainings)
    lines = [
        "---",
        f'title: "{collection.title}"',
        f'description: "{collection.description}"',
        f"order: {format_order(order)}",
        f'source: "{collection.source_url}"',
        "---",
        "",
        f"# {collection.title}",
        "",
        f"[洛谷官方题单列表]({collection.source_url})",
        "",
        (
            f"本题单共收录 **{stats['training_count']}** 个官方子题单、"
            f"**{stats['entry_count']}** 个题目条目、"
            f"**{stats['distinct_count']}** 道不同题目。"
        ),
        "",
        (
            f"其中有 **{stats['repeated_id_count']}** 道题出现在多个学习阶段，"
            f"形成 **{stats['extra_occurrence_count']}** 个重复条目。"
            "这些条目按洛谷官方分组原样保留，并共享完成进度。"
        ),
    ]

    for training in trainings:
        lines.extend(
            [
                "",
                f"## {markdown_text(training.name)}",
                "",
                (
                    f"[洛谷官方子题单]({LUOGU_ORIGIN}/training/{training.training_id})"
                    f" · {len(training.problems)} 题"
                ),
                "",
            ]
        )
        for problem in training.problems:
            label = f"{problem.pid} {problem.name}"
            lines.append(
                f"- [ ] [[problem: luogu,{problem.pid}]] · "
                f"[{markdown_text(label)}]({LUOGU_ORIGIN}/problem/{problem.pid})"
            )
    return "\n".join(lines) + "\n"


def atomic_write(path: Path, content: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    file_descriptor, temporary_name = tempfile.mkstemp(
        prefix=f".{path.name}.",
        suffix=".tmp",
        dir=path.parent,
        text=True,
    )
    try:
        with os.fdopen(file_descriptor, "w", encoding="utf-8", newline="\n") as handle:
            handle.write(content)
        os.replace(temporary_name, path)
    except Exception:
        try:
            os.unlink(temporary_name)
        except FileNotFoundError:
            pass
        raise


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate Luogu official training problem sets."
    )
    parser.add_argument(
        "--collection",
        choices=("all", *COLLECTIONS.keys()),
        default="all",
        help="collection to generate (default: all)",
    )
    return parser.parse_args()


def selected_collection_configs(key: str) -> list[CollectionConfig]:
    if key == "all":
        return list(COLLECTIONS.values())
    collection = COLLECTIONS.get(key)
    if collection is None:
        raise GenerationError(f"未知 collection：{key}")
    return [collection]


def main() -> int:
    args = parse_args()
    try:
        client = LuoguClient()
        prepared: list[tuple[CollectionConfig, list[Training], str]] = []
        for collection in selected_collection_configs(args.collection):
            trainings = load_trainings(client, collection)
            order = existing_order(collection.output)
            if order is None:
                order = collection.default_order
            content = render_markdown(trainings, collection, order)
            prepared.append((collection, trainings, content))

        for collection, _trainings, content in prepared:
            atomic_write(collection.output, content)
    except (GenerationError, OSError) as exc:
        print(f"Generation failed: {exc}", file=sys.stderr)
        return 1

    for collection, trainings, _content in prepared:
        stats = problem_stats(trainings)
        print(
            f"Generated {collection.output}: {stats['training_count']} trainings, "
            f"{stats['entry_count']} entries, {stats['distinct_count']} distinct problems, "
            f"{stats['repeated_id_count']} repeated IDs, "
            f"{stats['extra_occurrence_count']} extra occurrences."
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
