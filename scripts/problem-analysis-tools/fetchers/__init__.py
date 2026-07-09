"""Fetcher providers used by fetch_problem.py."""

from .base import FetchError, FetchResult, ProblemData, Sample
from .atcoder import AtCoderFetcher
from .codeforces import CodeforcesFetcher
from .kattis import KattisFetcher
from .luogu import LuoguFetcher
from .vjudge import VJudgeFetcher


FETCHERS = [
    LuoguFetcher(),
    AtCoderFetcher(),
    KattisFetcher(),
    CodeforcesFetcher(),
    VJudgeFetcher(),
]


__all__ = [
    "AtCoderFetcher",
    "CodeforcesFetcher",
    "FETCHERS",
    "FetchError",
    "FetchResult",
    "KattisFetcher",
    "LuoguFetcher",
    "ProblemData",
    "Sample",
    "VJudgeFetcher",
]
