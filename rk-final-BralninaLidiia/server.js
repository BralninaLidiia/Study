const http = require('http');
const fs = require('fs');
const { promisify } = require('util');
const sqlite3 = require('sqlite3').verbose();

const objectHTML = readhtml("index.html");

const server = http.createServer((req, res) => {
    const method = req.method;
    const url = req.url;
    if (method === 'GET' && url === '/') {
        res.writeHead(200, {
            'Content-Type': objectHTML.contentType,
            'Content-Length': objectHTML.length
        });
        res.end(objectHTML.content);
    }
    else if (method === 'POST' && url === '/inputDB') {
        let body = '';
        req.on('data', (chunk) => {
            body += chunk.toString();
        });
        req.on('end', async () => {
            try{
                const data = JSON.parse(body);
                if (data && data.pageNumber && data.surname && Number.isInteger(data.pageNumber) && data.pageNumber > 0) {
                    const db = new sqlite3.Database("Pages.db", (err) => {
                        if (err) {
                            console.error('Ошибка при подключении к базе данных:', err.message);
                            res.statusCode = 500;
                            res.setHeader('Content-Type', 'application/json');
                            res.end(JSON.stringify({ error: `Ошибка при подключении к базе данных: ${err.message}` }));
                        } 
                        else {
                            console.log('Подключение к базе данных успешно установлено');
                        }
                    });
                    await insertintodb(db, data.pageNumber);
              
                    const Data = await getfromdb(db);
                    const comments = [];
                    for (const key in Data){
                        comments.push(Data[key]);
                    }
                    comments.sort((a, b) => b.num_page - a.num_page);
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(JSON.stringify(comments));
                } 
                else {
                    res.statusCode = 400;
                    res.setHeader('Content-Type', 'application/json');
                    res.end(JSON.stringify({ error: 'Неверный формат данных' }));
                }
            } 
            catch (err) {
                res.statusCode = 400;
                res.setHeader('Content-Type', 'application/json');
                res.end(JSON.stringify({ error: err.message }));
            }
        });
    }
    else {
        res.statusCode = 404; 
        res.end('Not Found');
    }
})

const PORT = 4000;
const HOST = '127.0.0.1';

server.listen(PORT, HOST, (error) =>{
    if (error){
        console.log(error);
    }
    else{
        console.log(`Сервер запустился по адресу: http://${HOST}:${PORT}`);
    }
})
server.on('request', (req) => {
    console.log(`HTTP-запрос: ${req.url}`);
});
function readhtml(filePath) {
    try {
        const contentBuffer = fs.readFileSync(filePath);
        const contentString = contentBuffer.toString();
        const contentLength = Buffer.byteLength(contentString, 'utf8');
        const contentType = 'text/html';
        return {
            content: contentString,
            length: contentLength,
            contentType: contentType
        };
    } 
    catch (error) {
        console.error(`Ошибка чтения файла: ${filePath}`, error);
    }
}
async function insertintodb(db, data) {
    const runAsync = promisify(db.run.bind(db));
    try {
        const sql = `INSERT INTO Pages (num_page) VALUES (${data})`;
        await runAsync(sql);
    }
    catch (err) {
        throw new Error(`Ошибка базы данных: ${err.message}`);
    }
}
async function getfromdb(db) {
    const allAsync = promisify(db.all.bind(db));
    try {
        const sql = `SELECT * FROM Pages`;
        const row = await allAsync(sql);
        if (!row) {
            throw new Error(`База данных пуста`);
        }
        return row;
    }
    catch (err) {
        throw new Error(`Ошибка базы данных: ${err.message}`);
    }
}


