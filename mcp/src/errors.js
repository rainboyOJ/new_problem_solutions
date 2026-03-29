export const ERROR_CODES = Object.freeze({
  BAD_REQUEST: "BAD_REQUEST",
  NOT_FOUND: "NOT_FOUND",
  UPSTREAM_UNAVAILABLE: "UPSTREAM_UNAVAILABLE",
  UPSTREAM_ERROR: "UPSTREAM_ERROR",
  INTERNAL_ERROR: "INTERNAL_ERROR"
});

// 业务统一错误类型：同时携带机器可读 code 与 HTTP status。
export class AppError extends Error {
  constructor(message, { code = ERROR_CODES.INTERNAL_ERROR, status = 500, details } = {}) {
    super(message);
    this.name = "AppError";
    this.code = code;
    this.status = status;
    this.details = details;
  }
}

// 配置错误归类为 BAD_REQUEST，便于启动阶段快速定位。
export class ConfigError extends AppError {
  constructor(message, details) {
    super(message, {
      code: ERROR_CODES.BAD_REQUEST,
      status: 400,
      details
    });
    this.name = "ConfigError";
  }
}

// 将上游 HTTP 状态码映射到本服务标准错误码。
export function mapHttpStatusToCode(status) {
  if (status === 400) {
    return ERROR_CODES.BAD_REQUEST;
  }
  if (status === 404) {
    return ERROR_CODES.NOT_FOUND;
  }
  if (status >= 500 && status < 600) {
    return ERROR_CODES.UPSTREAM_ERROR;
  }
  if (status >= 400 && status < 600) {
    return ERROR_CODES.UPSTREAM_ERROR;
  }
  return ERROR_CODES.INTERNAL_ERROR;
}

// 兜底归一化，确保外部只接收到 AppError 结构。
export function normalizeError(error) {
  if (error instanceof AppError) {
    return error;
  }

  return new AppError(error?.message || "Unexpected internal error", {
    code: ERROR_CODES.INTERNAL_ERROR,
    status: 500
  });
}
