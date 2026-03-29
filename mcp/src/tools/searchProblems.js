import { AppError, ERROR_CODES } from "../errors.js";
import { z } from "zod";

export const SEARCH_PROBLEMS_TOOL = {
  name: "search_problems",
  description: "Search problems by text, OJ, and tag",
  inputSchema: {
    type: "object",
    properties: {
      query: { type: "string" },
      oj: { type: "string" },
      tag: { type: "string" },
      page: { type: "integer", minimum: 1 },
      limit: { type: "integer", minimum: 1, maximum: 100 }
    },
    additionalProperties: false
  }
};

export const SEARCH_PROBLEMS_ZOD_SCHEMA = z.object({
  query: z.string().optional(),
  oj: z.string().optional(),
  tag: z.string().optional(),
  page: z.number().int().min(1).optional(),
  limit: z.number().int().min(1).max(100).optional()
}).strict();

function parsePositiveInteger(value, { fieldName, fallback, max }) {
  if (value === undefined || value === null || value === "") {
    return fallback;
  }

  const parsed = Number(value);
  if (!Number.isInteger(parsed) || parsed <= 0) {
    throw new AppError(`${fieldName} must be a positive integer`, {
      code: ERROR_CODES.BAD_REQUEST,
      status: 400
    });
  }

  if (max && parsed > max) {
    throw new AppError(`${fieldName} must be <= ${max}`, {
      code: ERROR_CODES.BAD_REQUEST,
      status: 400
    });
  }

  return parsed;
}

function normalizeItem(item) {
  const normalized = {
    oj: item.oj,
    problem_id: item.problem_id || item.id,
    title: item.title,
    tags: Array.isArray(item.tags) ? item.tags : [],
    url: item.url || null
  };

  if (item.source) {
    normalized.source = item.source;
  }

  return normalized;
}

export function createSearchProblemsHandler({ apiClient }) {
  return async function searchProblems(input = {}, context = {}) {
    const limit = parsePositiveInteger(input.limit, {
      fieldName: "limit",
      fallback: 20,
      max: 100
    });
    const page = parsePositiveInteger(input.page, {
      fieldName: "page",
      fallback: 1
    });

    const upstream = await apiClient.searchProblems(
      {
        query: input.query,
        oj: input.oj,
        tag: input.tag,
        page,
        limit
      },
      context
    );

    const items = Array.isArray(upstream?.data) ? upstream.data.map(normalizeItem) : [];
    const pagination = upstream?.pagination || {};

    return {
      items,
      pagination: {
        total: Number(pagination.total || 0),
        page: Number(pagination.page || page),
        limit: Number(pagination.limit || limit),
        totalPages: Number(pagination.totalPages || 0)
      }
    };
  };
}
