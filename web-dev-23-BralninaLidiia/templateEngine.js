class TemplateEngine {
    constructor() {
    }
    static compile(template, data) {
        let content = data.content;
        content = content.replace('%%Name%%', template.name)
        content = content.replace('%%Comment%%', template.comment);
        content = content.replace('%%Date%%', template.date);
        escapeHtml(content);
        const length = Buffer.byteLength(content, 'utf8');
        return {
            html: content,
            contentLength: length
        };
        //функция санитизация HTML
        function escapeHtml(unsafe) {
            return unsafe
              .replace(/&/g, "&amp;")
              .replace(/</g, "&lt;")
              .replace(/>/g, "&gt;")
              .replace(/"/g, "&quot;")
              .replace(/'/g, "&#039;");
        }
    }
}
module.exports = TemplateEngine;