exports.escapeHtml =  function escapeHtml (html) {
    return html.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/\u00a0/g, ' ')
}
