const http = require('http');
const fs = require('fs');
const path = require('path');
const sqlite3 = require('sqlite3').verbose();
class VanillaApp{
    //конструктор
    constructor() {
        this.routes = new Map(); 
        this.server = http.createServer(this.handleRequest.bind(this)); //создание сервера
        //создание экземпляра базы данных 
        this.db = new sqlite3.Database("comments.db", (err) => {
            if (err) {
                console.error('Ошибка при подключении к базе данных:', err.message);
            } 
            else {
                console.log('Подключение к базе данных успешно установлено');
            }
        });
    }
    //метод для добавления новых url и методов HTTP в объект routes
    add(method, url, handler) {
        //проверяем существует ли объект с ключом method
        if (!this.routes[method]) {
            this.routes[method] = {};
        }
        //присваиваем значение handler в объект 
        this.routes[method][url] = handler;
    }
    //метод, который начинает прослушивание сервера
    listen(port, host) {
        this.server.listen(port, host, () => {
            console.log(`Сервер запустился по адресу: http://${host}:${port}`);
        });
    }
    //обработчик запроса на сервер
    async handleRequest(req, res) {
        const method = req.method;
        let url = req.url;
        console.log(`Пришел запрос: ${method}, ${url}`)
        //существует ли обработчик для данного метода и url
        if (this.routes[method] && this.routes[method][url]) {
            const funkDB = require('./services/databaseOperation.js');
            if (url == '/lastcomment'){
                await funkDB.getQuery(this.db);
            }
            if (method === 'POST' && url == '/comments'){
                let body = '';
                await req.on('data', (chunk) => {
                    body += chunk.toString();
                });
                const data = JSON.parse(body);
                await funkDB.setQuery(this.db, data);
            }
            this.routes[method][url](req, res);
        } 
        else if (method === 'GET') {
            const controllers = require('./controllers/rootControllers.js');
            controllers.rootGetControllerPlug(this.db, req, res);
        }
        else {
            const filePath = __dirname + "\\public" + "\\404.html";
            const contentBuffer = fs.readFileSync(filePath);
            const contentString = contentBuffer.toString();
            const contentLength = Buffer.byteLength(contentString, 'utf8');
            res.writeHead(404, { 
                'Content-Type': 'text/html',
                'Content-Length': contentLength
                });
            res.write(contentString);
            res.end();
        }
    }
    //метод для считывания папки 
    static(filesInfo, nameFolder) {
        //считываем содержимое папки по пути fileFolder
        try {
            const pathFolder = __dirname + nameFolder;
            const files = fs.readdirSync(pathFolder);
            //запускаем чтение каждого файла
            files.forEach(file => {
                let filePath = path.join(pathFolder, file);
                const resultObject = readFile(filePath);
                if (file == "index.html"){
                    file = "";
                }
                if (file == "lastcomment.html"){
                    file = "lastcomment";
                }
                filePath = "/" + file;
                filesInfo[filePath] = resultObject;
            });
        } 
        catch (err) {
            console.error('Ошибка при чтении папки:', err);
        }
        //функция считывания файла
        function readFile(filePath) { 
            try {
                const contentBuffer = fs.readFileSync(filePath);
                let contentString;
                if (getTypeData(filePath)){
                    contentString = contentBuffer
                }
                else{
                    contentString = contentBuffer.toString();
                }
                const contentLength = Buffer.byteLength(contentString, 'utf8');
                const contentType = getContentType(filePath);
                return {
                    content: contentString,
                    length: contentLength,
                    contentType: contentType
                };
            } 
            catch (error) {
                console.error(`Ошибка чтения файла: ${filePath}`, error);
                return null;
            }
            //функция для определения типа контента на основе расширения файла
            function getContentType(filePath) {
                const extname = path.extname(filePath).toLowerCase();
                switch (extname) {
                    case '.html':
                        return 'text/html';
                    case '.css':
                         return 'text/css';
                    case '.png':
                        return 'image/png';
                    case '.jpg':
                        return 'image/jpeg';
                    case '.svg':
                        return 'image/svg+xml';
                }
            }
            //функция, которая определяет какой формат файла считывается 
            function getTypeData(filePath){
                const extname = path.extname(filePath).toLowerCase();
                switch (extname) {
                    case '.html':
                    case '.css':
                        return false;
                    case '.png':
                    case '.jpg':
                    case '.svg':
                         return true;
                }
            }
        }
    }
}
//экспортируем класс
module.exports = new VanillaApp();
