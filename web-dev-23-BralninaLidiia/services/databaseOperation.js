const { promisify } = require('util');
//функция для генерации html с ошибкой бд
function error404(err) {
    const html = `
        <!DOCTYPE html>
        <html lang="ru">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Ошибка базы данных</title>
        </head>
        <body>
            <h1 style="text-align: center;">Error 404 - ошибка базы данных. ${err.message}</h1>
            <p style="text-align: center;">Извините, произошла ошибка. Вернитесь на <a href="/">главную страницу</a>.</p>
        </body>
        </html>
    `
    const contentLength = Buffer.byteLength(html, 'utf8');
    const contentType = 'text/html';
    return {
        content: html,
        length: contentLength,
        contentType: contentType
    }
}
//функция, которая принимает экземпляр базы данных объект с данными
async function setQuery(db, data) {
    const TemplateEngine = require('../templateEngine.js');
    const FILES = require('../main.js');
    const runAsync = promisify(db.run.bind(db));
    const getAsync = promisify(db.get.bind(db));
    try {
        let queryID = `SELECT id FROM comments ORDER BY id DESC LIMIT 1`;
        let row = await getAsync(queryID);
        const idcomments = row.id + 1;
        queryID = `SELECT id FROM names ORDER BY id DESC LIMIT 1`;
        row = await getAsync(queryID);
        const idNames = row.id + 1;
        const queryNamesTable = `INSERT INTO names (id, name) VALUES (${idNames}, '${data.name}');`;
        await runAsync(queryNamesTable);
        const currentTime = new Date();
        //форматирование даты в нужный формат (YYYY-MM-DD)
        const formattedDate = currentTime.toISOString().slice(0, 10);
        const hours = currentTime.getHours().toString().padStart(2, '0');
        const minutes = currentTime.getMinutes().toString().padStart(2, '0');
        const seconds = currentTime.getSeconds().toString().padStart(2, '0');
        const formattedTime = `${hours}:${minutes}:${seconds}`;
        //создание строки в нужном формате (YYYY-MM-DD HH:MM:SS)
        const formattedDateTime = `${formattedDate} ${formattedTime}`;
        const queryCommentsTable = `INSERT INTO comments (id, comment_text, created_at, user_id) VALUES (${idcomments}, '${data.comment}', '${formattedDateTime}', ${idNames});`
        await runAsync(queryCommentsTable);
        //объект с данными для шаблона
        const comments = {
            name: data.name,
            comment: data.comment,
            date: formattedDateTime
        };
        const sanitizedHtml = TemplateEngine.compile(comments, FILES['/lastcomment']);
        FILES['/comments'] = {
            content: sanitizedHtml.html,
            length: sanitizedHtml.contentLength,
            contentType: 'text/html'
        };
    } 
    catch (err) {
        FILES['/comments'] = error404(err);
    }
}
//функция, которая возращает данные из базы данных для шаблонизации
async function getQuery(db){
    //импортируем класс
    const TemplateEngine = require('../templateEngine.js');
    const FILES = require('../main.js');
    const query = `SELECT comments.comment_text, comments.created_at, names.name FROM comments JOIN names ON comments.user_id = names.id ORDER BY comments.created_at DESC LIMIT 1;`;
    const getAsync = promisify(db.get.bind(db));
    try {
        const row = await getAsync(query);
        //если в таблице пусто
        if (!row) {
            FILES['/lastcomment'] =  error404(new Error("Нет доступных комментариев"));
        }
        //извлечение данных из результата запроса
        const commentText = row.comment_text;
        const commentTime = new Date(row.created_at).toLocaleString();
        const commenterName = row.name;
        //объект с данными для шаблона
        const comments = {
            name: commenterName,
            comment: commentText,
            date: commentTime
        };
        const sanitizedHtml = TemplateEngine.compile(comments, FILES['/lastcomment']);
        FILES['/lastcomment'] = {
            content: sanitizedHtml.html,
            length: sanitizedHtml.contentLength,
            contentType: 'text/html'
        };
    } 
    catch (err) {
        FILES['/lastcomment'] = error404(err);
    }
}
//функция которая возращает данные из бд
async function allQuery(db, queryParams){
    const allAsync = promisify(db.all.bind(db));
    try {
        //вычисляем смещение для LIMIT
        const offset = (queryParams.page - 1) * queryParams.limit;
        const query = `SELECT * FROM comments LIMIT ${queryParams.limit} OFFSET ${offset};`;
        const row = await allAsync(query);
        //если в таблице пусто
        if (!row) {
            return new Error("Нет доступных комментариев");
        }
        return row;
    }
    catch (err) {
        return err;
    }
} 
exports.setQuery = setQuery;
exports.getQuery = getQuery;
exports.allQuery = allQuery;
exports.error404 = error404;