export const CONTENT_RELEASE = Symbol('contentRelease');

export function contentGuard(contentService, responseType = 'html') {
  return async function guard(request, reply) {
    const release = contentService.acquireRequest();
    if (release) {
      request[CONTENT_RELEASE] = release;
      return;
    }

    const message = contentService.state === 'unavailable'
      ? '内容更新失败，请稍后再试'
      : '内容暂时不可用';
    reply.header('Retry-After', '5');

    if (responseType === 'json') {
      return reply.code(503).send({
        error: 'CONTENT_UNAVAILABLE',
        message,
        state: contentService.state,
        statusCode: 503,
      });
    }

    return reply.code(503).view('content-unavailable.pug', {
      title: message,
      message,
    });
  };
}
