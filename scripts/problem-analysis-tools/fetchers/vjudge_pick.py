"""VJudge 题面选版与样例补全。

VJudge 上一道题往往有多个题面版本（官方英文、LLM 中文翻译、用户 fork 等）。
这里的策略对 AtCoder 和 Codeforces 通用：

1. 中文优先，并且尽量选 ``trustable`` 的版本；
2. 没有中文就退到英文/日文；
3. 选中的版本没有样例表时，从别的版本借样例。
"""

from __future__ import annotations

from .base import FetchError, Sample
from .vjudge_client import DescBrief, VJudgeClient
from .vjudge_statement import build_statement

# 选版优先级：中文 → 英文 → 日文。
LANG_PRIORITY = ("zh", "en", "ja")


def pick_brief(client: VJudgeClient, briefs: list[DescBrief]) -> tuple[DescBrief, str]:
    """按 zh(trustable) → zh → en → ja 选版，返回 (brief, 说明文字)。

    trustable 不在 descBriefs 里，只在正文 JSON 里，所以要逐个取正文才能排序。
    正文有进程内缓存，同一版本不会被重复拉取。
    """

    by_lang: dict[str, list[DescBrief]] = {}
    for brief in briefs:
        by_lang.setdefault(brief.lang, []).append(brief)

    zh_briefs = by_lang.get("zh") or []
    if zh_briefs:
        for brief in zh_briefs:
            if client.description(brief.key).trustable:
                others = len(zh_briefs) - 1
                note = f"使用 VJudge 中文题面（{brief.author}，trustable，版本 {brief.key}）"
                if others:
                    note += f"；该题另有 {others} 个中文版本"
                return brief, note
        return zh_briefs[0], (
            f"使用 VJudge 中文题面（{zh_briefs[0].author}，"
            f"版本 {zh_briefs[0].key}），未找到标记为 trustable 的中文版本"
        )

    for lang in LANG_PRIORITY[1:]:
        candidates = by_lang.get(lang) or []
        if candidates:
            main = next((b for b in candidates if b.main_official), candidates[0])
            return main, f"该题在 VJudge 上没有中文题面，已回退到 {lang} 版本（{main.author}）"

    brief = briefs[0]
    return brief, f"该题在 VJudge 上只有 {brief.lang} 版本，已使用（{brief.author}）"


def samples_from_fallback(
    client: VJudgeClient, briefs: list[DescBrief], chosen: DescBrief
) -> tuple[list[Sample], str]:
    """选中版本没有样例表时，从其它版本（优先 en main）补样例。"""

    others = [b for b in briefs if b.key != chosen.key]
    others.sort(key=lambda b: (b.lang != "en", not b.main_official))
    for brief in others:
        try:
            fallback = client.description(brief.key)
        except FetchError:
            continue
        statement = build_statement("# fallback", fallback.sections)
        if statement.samples:
            return statement.samples, (
                f"所选题面版本（{chosen.lang}/{chosen.author}，{chosen.key}）没有样例，"
                f"样例取自 {brief.lang}/{brief.author} 版本（{brief.key}）"
            )
    return [], "所选题面及所有备用版本都没有抓到样例。"
