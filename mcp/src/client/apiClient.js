import { AppError, ERROR_CODES, mapHttpStatusToCode } from "../errors.js";

function encodePathSegment(value) {
  return encodeURIComponent(String(value));
}

export class ApiClient {
  constructor({ baseUrl, timeoutMs = 5000, fetchImpl = fetch }) {
    this.baseUrl = new URL(baseUrl);
    this.timeoutMs = timeoutMs;
    this.fetchImpl = fetchImpl;
  }

  async searchProblems({ query, oj, tag, page, limit } = {}, context = {}) {
    const searchParams = new URLSearchParams();
    if (query) {
      searchParams.set("search", String(query));
    }
    if (oj) {
      searchParams.set("oj", String(oj));
    }
    if (tag) {
      searchParams.set("tag", String(tag));
    }
    if (page !== undefined) {
      searchParams.set("page", String(page));
    }
    if (limit !== undefined) {
      searchParams.set("limit", String(limit));
    }

    return this.#requestJson("/api/problems", searchParams, context);
  }

  async getProblemDetail({ oj, id } = {}, context = {}) {
    if (!oj || !id) {
      throw new AppError("oj and id are required", {
        code: ERROR_CODES.BAD_REQUEST,
        status: 400
      });
    }

    const path = `/api/problems/${encodePathSegment(oj)}/${encodePathSegment(id)}`;
    return this.#requestJson(path, undefined, context);
  }

  async #requestJson(pathname, searchParams, context = {}) {
    const requestUrl = new URL(pathname, this.baseUrl);
    if (searchParams) {
      requestUrl.search = searchParams.toString();
    }

    const controller = new AbortController();
    const timeoutId = setTimeout(() => controller.abort(), this.timeoutMs);

    try {
      const response = await this.fetchImpl(requestUrl.toString(), {
        method: "GET",
        headers: { accept: "application/json" },
        signal: controller.signal
      });

      let payload;
      try {
        payload = await response.json();
      } catch {
        payload = undefined;
      }

      if (!response.ok) {
        throw new AppError(`Upstream request failed with status ${response.status}`, {
          code: mapHttpStatusToCode(response.status),
          status: response.status,
          details: {
            trace_id: context.traceId,
            upstream_path: requestUrl.pathname,
            upstream: payload
          }
        });
      }

      return payload;
    } catch (error) {
      if (error instanceof AppError) {
        throw error;
      }

      if (error?.name === "AbortError" || error instanceof TypeError) {
        throw new AppError("Upstream API unavailable", {
          code: ERROR_CODES.UPSTREAM_UNAVAILABLE,
          status: 503,
          details: {
            trace_id: context.traceId,
            upstream_path: requestUrl.pathname
          }
        });
      }

      throw new AppError(error?.message || "Upstream request failed", {
        code: ERROR_CODES.INTERNAL_ERROR,
        status: 500
      });
    } finally {
      clearTimeout(timeoutId);
    }
  }
}
