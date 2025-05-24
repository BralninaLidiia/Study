const http = require('http');

const comments = [];
const requestStats = {};
let countConnection = 0;

const server = http.createServer((req, res) => {
    //get-запрос на "/"
    if (req.method === 'GET' && req.url === '/'){
        res.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
        res.write("Привет, мир !");
        res.end();
    }
    //post-запрос на "/comments"
    else if (req.method === 'POST' && req.url === '/solution'){
        let body = '';
        req.on('data', (chunk) => {
            body += chunk.toString();
        });
        function Request() {
            try {
                const data = JSON.parse(body);
                if (data && data.name && data.comment) {
                    comments.push({ name: data.name, comment: data.comment });
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(JSON.stringify(comments));
                } 
                else {
                    res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                    res.end('Bad Request: неверный формат данных');
                }
            } 
            catch (error) {
                res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                res.end('Bad Request: неверный JSON-формат');
            }
        }
        
        req.on('end', Request);
    }
    //get-запрос на "/stats"
    else if(req.method === 'GET' && req.url === '/stats') {
        const htmlResponse = generateHtmlStats();
        res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
        res.end(htmlResponse);
    }
    else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('Not Found');
    }
})

const PORT = 3000;

server.listen(PORT, '127.0.0.1', (error) =>{
    if (error){
        console.log(error);
    }
    else{
        const address = server.address();
        console.log(`Сервер заработал на порту: ${address.port}, ip-aдрес: ${address.address}`);
    }
})

//обработчик события "подключение"
server.on('connection', (socket) => {
    countConnection++;
    console.log(`Подключение № ${countConnection}, ip-адрес: ${socket.remoteAddress}`);
  });

//обработчик события "запрос"
server.on('request', (req) => {
    const userAgent = req.headers['user-agent'];
    if (userAgent) {
        requestStats[userAgent] = (requestStats[userAgent] || 0) + 1;
    }
    console.log(`HTTP-запрос: ${req.url}`);
});

function generateHtmlStats() {
    let html = '<html><head><title>Статистика запросов</title></head><body>';
    html += '<h1>Статистика</h1>';
    html += '<table border="1">';
    html += '<tr><th>User-Agent</th><th>Кол-во запросов</th></tr>';

    for (const userAgent in requestStats) {
        html += `<tr><td>${userAgent}</td><td>${requestStats[userAgent]}</td></tr>`;
    }

    html += '</table></body></html>';
    return html;
}