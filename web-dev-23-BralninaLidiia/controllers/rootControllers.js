function rootGetController(req, res){
    const FILES = require('../main.js');
    const data = FILES[req.url];
    res.writeHead(200, {
        'Content-Type': data.contentType,
        'Content-Length': data.length
    });
    res.write(data.content);
    res.end();
}

exports.rootGetController = rootGetController;