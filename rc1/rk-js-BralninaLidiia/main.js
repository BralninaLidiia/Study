const http = require('http');

const requestStats = {
    "correct": 0,
    "incorrect": 0
};

const server = http.createServer((req, res) => {
    const method = req.method;
    const url = req.url;
    if (method === 'POST' && url === '/solution'){
        let body = '';
        req.on('data', (chunk) => {
            body += chunk.toString();
        });
        function Request() {
            try {
                const data = JSON.parse(body);
                if (data && data.letters) {
                    const number = visiting(data.letters);
                    const dataResult = {
                        solution: number,
                        name: "Бральнина Л.С."
                    };
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    requestStats.correct++;
                    res.end(JSON.stringify(dataResult));
                } else {
                    res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                    requestStats.incorrect++;
                    res.end('Bad Request: неверный формат данных');
                }
            } catch (err) {
                res.writeHead(400, { 'Content-Type': 'text/plain; charset=utf-8' });
                requestStats.incorrect++;
                res.end('Bad Request: неверный JSON-формат');
            }
        }
        
        req.on('end', Request);
    }
    else if (method === 'GET' && url === '/task'){
        const taskText = `
        Дана строка, представляющая запись о посещаемости студента, где каждый символ означает, отсутствовал ли студент, опоздал или присутствовал в этот день. Запись содержит только следующие три символа:

‘Н’: Отсутствует. ‘О’: Опоздал. ‘П’: Присутствует.

Студент имеет право на поощрение за посещаемость, если он соответствует обоим следующим критериям:

Студент отсутствовал (“Н”) строго менее 2 дней в общей сложности.
Студент никогда не опаздывал (“О”) в течение 3 или более дней подряд.
Верните истину, если студент имеет право на получение награды за посещаемость, или ложь в противном случае.

Допустимы только буквы Н, О, П.
        `;
        res.writeHead(200, {'Content-Type': 'text/plain; charset=utf-8'});
        requestStats.correct++;
        res.end(taskText);
    }
    else if (method === 'GET' && url === '/stats'){
        res.writeHead(200, { 'Content-Type': 'application/json' });
        requestStats.correct++;
        res.end(JSON.stringify(requestStats));
    } 
    else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        requestStats.incorrect++;
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
//обработчик события "запрос"
server.on('request', (req) => {
    console.log(`HTTP-запрос: ${req.url}`);
});

function visiting(letters) {
    let absentCount = 0;
    let lateCount = 0;
    let consecutiveLateCount = 0;

    for (let i = 0; i < letters.length; i++) {
        if (letters[i] === 'Н') {
            absentCount++;
        } else if (letters[i] === 'О') {
            lateCount++;
            consecutiveLateCount++;
        } else {
            consecutiveLateCount = 0;
        }

        if (consecutiveLateCount >= 3) {
            return 'ложь'; 
        }
    }


    if (absentCount < 2){
        return "истина";
    }

}