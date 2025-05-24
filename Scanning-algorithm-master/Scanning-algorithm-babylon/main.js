// Массивы рямоугольников
const rectangles1 = [
    { x1: 4, y1: 10, x2: 12, y2: 22 },
    { x1: 8, y1: 4, x2: 18, y2: 16 },
    { x1: 14, y1: 6, x2: 24, y2: 14 }
];
const rectangles2 = [
    { x1: 1, y1: 1, x2: 4, y2: 4 },
    { x1: 2, y1: 2, x2: 6, y2: 8 },
    { x1: 4, y1: 6, x2: 8, y2: 10 }
];
const rectangles3 = [
    { x1: 2, y1: 3, x2: 5, y2: 6 },
    { x1: 4, y1: 4, x2: 7, y2: 7 },
    { x1: 6, y1: 5, x2: 8, y2: 8 },
    { x1: 7, y1: 6, x2: 11, y2: 10 },
    { x1: 7, y1: 3, x2: 10, y2: 7 },
    { x1: 4, y1: 1, x2: 8, y2: 5 },
    { x1: 9, y1: 8, x2: 10, y2: 15 },
    { x1: 5, y1: -4, x2: 7, y2: 2 },
    { x1: 9, y1: 5, x2: 14, y2: 8 }
];

// Функция для рендера прямоугольников 
function createSceneRectangle(rectangles) {
    var canvas = document.getElementById('renderRectangles');
    var engine = new BABYLON.Engine(canvas, true);
    var scene = new BABYLON.Scene(engine);
    var camera = new BABYLON.ArcRotateCamera("ArcRotateCamera", 0, 0, 80, new BABYLON.Vector3(15, 15, 0), scene);
    camera.setPosition(new BABYLON.Vector3(15, 15, -80));
    camera.lowerBetaLimit = Math.PI / 2; 
    camera.upperBetaLimit = Math.PI / 2; 
    camera.attachControl(canvas, true);
    var light = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(0, 1, 0), scene);
    light.intensity = 0.7;
    for (let i = 0; i < rectangles.length; i++) {
        let contourPoints = [];
        contourPoints.push({x: rectangles[i].x1, y: rectangles[i].y1});
        contourPoints.push({x: rectangles[i].x1, y: rectangles[i].y2});
        contourPoints.push({x: rectangles[i].x2, y: rectangles[i].y2});
        contourPoints.push({x: rectangles[i].x2, y: rectangles[i].y1});
        contourPoints.push({x: rectangles[i].x1, y: rectangles[i].y1});
        const lines = BABYLON.MeshBuilder.CreateLines("lines", {
            points: contourPoints.map(point => new BABYLON.Vector3(point.x, point.y, 0))
        }, scene);
    }
    engine.runRenderLoop(function() {
        scene.render();
    });
};

// Функция для рендера контура
function createSceneCanvas(rectangles) {
    var canvas = document.getElementById('renderCanvas');
    var engine = new BABYLON.Engine(canvas, true);
    var scene = new BABYLON.Scene(engine);
    var camera = new BABYLON.ArcRotateCamera("ArcRotateCamera", 0, 0, 80, new BABYLON.Vector3(15, 15, 0), scene);
    camera.setPosition(new BABYLON.Vector3(15, 15, -80));
    camera.lowerBetaLimit = Math.PI / 2; 
    camera.upperBetaLimit = Math.PI / 2; 
    camera.attachControl(canvas, true);
    var light = new BABYLON.HemisphericLight("light1", new BABYLON.Vector3(0, 1, 0), scene);
    light.intensity = 0.7;
    const contourPoints = createContour(rectangles);
    const lines = BABYLON.MeshBuilder.CreateLines("lines", {
        points: contourPoints.map(point => new BABYLON.Vector3(point.x, point.y, 0))
    }, scene);
    engine.runRenderLoop(function() {
        scene.render();
    });
};

// Обработчики событий кнопок
document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('btn1').addEventListener('click', function() {
        createSceneRectangle(rectangles1); 
    });
    document.getElementById('btn2').addEventListener('click', function() {
        createSceneRectangle(rectangles2); 
    });
    document.getElementById('btn3').addEventListener('click', function() {
        createSceneRectangle(rectangles3); 
    });
    document.getElementById('btn1_1').addEventListener('click', function() {
        createSceneCanvas(rectangles1); 
    });
    document.getElementById('btn2_2').addEventListener('click', function() {
        createSceneCanvas(rectangles2); 
    });
    document.getElementById('btn3_3').addEventListener('click', function() {
        createSceneCanvas(rectangles3); 
    });
});

//////// ФУНКЦИИ ДЛЯ СОЗДАНИЯ КОНТУРА ////////

// Функция для создания массива всех точек
function createArrayPoints(rectangles) {
    let points = [];
    // Добавляем все углы прямоугольников в массив точек
    rectangles.forEach(rect => {
        points.push({ x: rect.x1, y: rect.y1 });
        points.push({ x: rect.x1, y: rect.y2 });
        points.push({ x: rect.x2, y: rect.y1 });
        points.push({ x: rect.x2, y: rect.y2 });
    });
    // Находим точки пересечения и добавляем их в массив точек
    for (let i = 0; i < rectangles.length; i++) {
        for (let j = i + 1; j < rectangles.length; j++) {
            let inters = findIntersections(rectangles[i], rectangles[j]);
            points.push(...inters);
        }
    }
    // Сортируем точки по X и Y
    points.sort((a, b) => {
        if (a.x === b.x) {
          return a.y - b.y; // Если x равны, сортируем по y
        }
        return a.x - b.x; // Сортируем по x
      });
      
    // Удаляем дублирующиеся точки
    points = uniquePoints(points);
    for (let i = 0; i < points.length; i++){
        points[i].number = i;
    }
    // Возвращаем массив
    return points;

    // Функция для нахождения пересечений двух прямоугольников
    function findIntersections(rect1, rect2) {
        let intersections = [];
        let lines1 = getLines(rect1);
        let lines2 = getLines(rect2);

        for (let line1 of lines1) {
            for (let line2 of lines2) {
                let intersection = getLineIntersection(line1, line2);
                if (intersection) {
                    intersections.push(intersection);
                }
            }
        }

        return intersections;
    }
    // Получить линии, образующие прямоугольник
    function getLines(rect) {
        return [
            { p1: { x: rect.x1, y: rect.y1 }, p2: { x: rect.x2, y: rect.y1 } },
            { p1: { x: rect.x2, y: rect.y1 }, p2: { x: rect.x2, y: rect.y2 } },
            { p1: { x: rect.x2, y: rect.y2 }, p2: { x: rect.x1, y: rect.y2 } },
            { p1: { x: rect.x1, y: rect.y2 }, p2: { x: rect.x1, y: rect.y1 } }
        ];
    }
    // Функция для нахождения пересечения двух линий
    function getLineIntersection(line1, line2) {
        let { p1, p2 } = line1;
        let { p1: q1, p2: q2 } = line2; 
        // Проверка, что все точки существуют
        if (!p1 || !p2 || !q1 || !q2) return null;
        // Вычисление детерминанта
        let det = (p2.x - p1.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q2.x - q1.x);
        // Линии параллельны или совпадают
        if (det === 0) return null; 
        // Вычисление параметров λ и γ, используются для нахождения точки пересечения в параметрической форме
        let lambda = ((q2.y - q1.y) * (q2.x - p1.x) + (q1.x - q2.x) * (q2.y - p1.y)) / det;
        let gamma = ((p1.y - p2.y) * (q2.x - p1.x) + (p2.x - p1.x) * (q2.y - p1.y)) / det;
        // Условие пересечения
        if (0 <= lambda && lambda <= 1 && 0 <= gamma && gamma <= 1) {
            return {
                x: p1.x + lambda * (p2.x - p1.x),
                y: p1.y + lambda * (p2.y - p1.y)
            };
        }
        // Если нет пересечения
        return null;
    }
    // Уникальные точки
    function uniquePoints(points) {
        let unique = [];
        let set = new Set();
        for (let point of points) {
            let key = `${point.x},${point.y}`;
            if (!set.has(key)) {
                set.add(key);
                unique.push(point);
            }
        }
        return unique;
    }
}
// Функция для создания первоначального выпуклого контура
function createConvexContour(Points) {
    let points = Points;
    // Функция для нахождения ориентации тройки точек (p, q, r)
    function orientation(p, q, r) {
        // Вычисляем детерминант 
        let val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val === 0) return 0; // Коллинеарны
        if (val > 0) {
            return 1; // Поворот по часовой стрелке
        } 
        else {
            return 2; // Поворот против часовой стрелки
        }
    }

    // Функция для нахождения следующей точки в контуре (алгоритм Джарвиса)
    function nextPoint(points, p) {
        let next = points[0];
        for (let i = 1; i < points.length; i++) {
            let q = points[i];
            let o = orientation(p, next, q);
            // Если находим точку, которая дальше от p по часовой стрелке или является коллинеарной и дальше от p.
            if (next === p || o === 2 || (o === 0 && distance(p, q) > distance(p, next))) {
                next = q;
            }
        }
        return next;
    }

    // Функция для нахождения расстояния между двумя точками
    function distance(p, q) {
        return (p.x - q.x) ** 2 + (p.y - q.y) ** 2;
    }

    // Инициализация контура
    let hull = [];
    let start = points[0];
    for (let i = 1; i < points.length; i++) {
        if (points[i].x < start.x) {
            start = points[i];
        }
    }

    // Построение контура
    let p = start;
    do {
        hull.push(p);
        p = nextPoint(points, p);
    } while (p !== start);

    return hull;
}
// Функция для создания первоначального конечного контура
function createContour(rectangles) {
    const rectanglesPoints = createArrayPoints(rectangles);
    const contourPoints = createConvexContour(rectanglesPoints);
    let buffPoints = new Set();
    contourPoints.push(contourPoints[0]);
    for (let i = 1; i < contourPoints.length; i++){
        let oldPoint = contourPoints[i - 1];
        let currentPoint = contourPoints[i];
        buffPoints.add(oldPoint);
        if (oldPoint.x === currentPoint.x || oldPoint.y === currentPoint.y){
            continue;
        }
        let oldPointBuff = oldPoint;
        if (oldPoint.y < currentPoint.y && oldPoint.number < currentPoint.number) {
            for (let i = oldPointBuff.number + 1; i < currentPoint.number; i++){
                let buffPoint = rectanglesPoints[i];
                if (oldPointBuff === oldPoint) {
                    if (oldPointBuff.y != buffPoint.y) {
                        continue;
                    }
                    else {
                        buffPoints.add(buffPoint);
                        oldPointBuff = buffPoint;
                        continue;
                    }
                }
                else {
                    if (buffPoint === rectanglesPoints[currentPoint.number - 1] && buffPoints[buffPoints.length - 1] !== buffPoint) {
                        buffPoints.add(buffPoint);
                        break;
                    }
                    if (buffPoint.x === oldPointBuff.x){
                        buffPoints.add(buffPoint);
                        oldPointBuff = buffPoint;
                        oldPoint = buffPoint;
                        continue;
                    }
                }
            }
            if (buffPoints[buffPoints.length - 1] !== rectanglesPoints[currentPoint.number - 1]) {
                buffPoints.add(rectanglesPoints[currentPoint.number - 1]);
            }
        }
        else if (oldPoint.y > currentPoint.y && oldPoint.number > currentPoint.number) {
            for (let i = oldPointBuff.number - 1; i > currentPoint.number; i--){
                let buffPoint = rectanglesPoints[i];
                if (oldPointBuff === oldPoint) {
                    if (oldPointBuff.y != buffPoint.y) {
                        continue;
                    }
                    else {
                        buffPoints.add(buffPoint);
                        oldPointBuff = buffPoint;
                        continue;
                    }
                }
                else {
                    if (buffPoint === rectanglesPoints[currentPoint.number - 1] && buffPoints[buffPoints.length - 1] !== buffPoint) {
                        buffPoints.add(buffPoint);
                        break;
                    }
                    if (buffPoint.x === oldPointBuff.x){
                        buffPoints.add(buffPoint);
                        oldPointBuff = buffPoint;
                        oldPoint = buffPoint;
                        continue;
                    }
                }
            }
            if (buffPoints[buffPoints.length - 1] !== rectanglesPoints[currentPoint.number + 1]) {
                buffPoints.add(rectanglesPoints[currentPoint.number + 1]);
            }
        }
        else if (oldPoint.y > currentPoint.y && oldPoint.number < currentPoint.number ) {
            for (let i = oldPointBuff.number - 1; i < currentPoint.number; i++){
                let buffPoint = rectanglesPoints[i]
                if (buffPoint.number ===  oldPointBuff.number - 1){
                    buffPoints.add(buffPoint);
                    continue;
                }
                if (buffPoint === oldPointBuff){
                    continue;
                }
                if (buffPoint.y !== rectanglesPoints[oldPointBuff.number - 1].y){
                    continue;
                }
                else {
                    buffPoints.add(buffPoint);
                    oldPointBuff = buffPoint;
                    i -= 2;
                    continue;
                }
            }
        }
        else if (oldPoint.y < currentPoint.y && oldPoint.number > currentPoint.number) {
            for (let i = oldPointBuff.number + 1; i > currentPoint.number; i--){
                let buffPoint = rectanglesPoints[i]
                if (buffPoint.number ===  oldPointBuff.number + 1){
                    buffPoints.add(buffPoint);
                    continue;
                }
                if (buffPoint === oldPointBuff){
                    continue;
                }
                if (buffPoint.y !== rectanglesPoints[oldPointBuff.number + 1].y){
                    continue;
                }
                else {
                    buffPoints.add(buffPoint);
                    oldPointBuff = buffPoint;
                    i += 2;
                    continue;
                }
            }
        }
    }
    let buff = Array.from(buffPoints);
    buff.push(buff[0]);
    return buff;
}