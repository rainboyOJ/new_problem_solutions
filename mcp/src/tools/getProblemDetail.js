import { AppError, ERROR_CODES } from "../errors.js";
import { z } from "zod";

export const GET_PROBLEM_DETAIL_TOOL = {
  name: "get_problem_detail",
  description: "Get a single problem detail by OJ and id",
  inputSchema: {
    type: "object",
    required: ["oj", "id"],
    properties: {
      oj: { type: "string" },
      id: { type: "string" }
    },
    additionalProperties: false
  }
};

export const GET_PROBLEM_DETAIL_ZOD_SCHEMA = z.object({
  oj: z.string(),
  id: z.string()
}).strict();

function requireString(value, fieldName) {
  if (typeof value !== "string" || value.trim() === "") {
    throw new AppError(`${fieldName} is required`, {
      code: ERROR_CODES.BAD_REQUEST,
      status: 400
    });
  }
  return value;
}

export function createGetProblemDetailHandler({ apiClient }) {
  return async function getProblemDetail(input = {}, context = {}) {
    const oj = requireString(input.oj, "oj");
    const id = requireString(input.id, "id");

    const upstream = await apiClient.getProblemDetail({ oj, id }, context);

    return {
      oj: upstream.oj,
      problem_id: upstream.problem_id || upstream.id,
      title: upstream.title,
      tags: Array.isArray(upstream.tags) ? upstream.tags : [],
      url: upstream.url || null,
      md_content: upstream.md_content || "",
      html_content: upstream.html_content || ""
    };
  };
}
