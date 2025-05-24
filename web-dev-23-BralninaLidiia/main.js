const PORT = 3000;
//импортируем класс
const myServer = require('./VanillaApp.js');
//считываем статический файлы из папки Public
const HOST = '127.0.0.1';
let FILES = {};
myServer.static(FILES, "\\templates");
myServer.static(FILES, "\\public");
module.exports = FILES; //экспорт объекта FILES
//импортируем контроллеры
const controllers = require('./controllers/rootControllers.js');
//перебираем все файлы и добавляем в метод add
for (let key in FILES) {
    myServer.add("GET", key, controllers.rootGetController);
}
myServer.add("POST", "/submit", controllers.rootPostController);
myServer.add("POST", "/comments", controllers.rootGetController);
//запускаем прослушку сервера
myServer.listen(PORT, HOST);