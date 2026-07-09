"""Fetcher providers used by fetch_problem.py."""

from .base import FetchError, FetchResult, ProblemData, Sample
from .atcoder import AtCoderFetcher
from .codeforces import CodeforcesFetcher
from .luogu import LuoguFetcher
from .vjudge import VJudgeFetcher


FETCHERS = [
    LuoguFetcher(),
    AtCoderFetcher(),
    CodeforcesFetcher(),
    VJudgeFetcher(),
]


__all__ = [
    "AtCoderFetcher",
    "CodeforcesFetcher",
    "FETCHERS",
    "FetchError",
    "FetchResult",
    "LuoguFetcher",
    "ProblemData",
    "Sample",
    "VJudgeFetcher",
]
