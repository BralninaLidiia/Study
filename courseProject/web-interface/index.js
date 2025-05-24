
var express = require('express');
var bodyParser = require('body-parser');

var app = express()

const urlencodedParser = bodyParser.urlencoded({extended: false});
app.use(express.static(__dirname));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/index.html' )
})

app.listen(8000, function() {
    console.log('Server started at http://localhost:8000');
});

let lc = '';
let lt = '';
let lr = '';
let lb = '';
let d0 = '';
let dc = '';
let ht = '';
let hb = '';
let U = '';

app.post('/', urlencodedParser, function (req, res) {
    if(!req.body) return res.sendStatus(400);
    console.log(req.body);
    lc = req.body.lc;
    lt = req.body.lt;
    lr = req.body.lr;
    lb = req.body.lb;
    d0 = req.body.d0;
    dc = req.body.dc;
    ht = req.body.ht;
    hb = req.body.hb;
    U = req.body.U;
    try {
        cleanSh();
        changeParams();
        runSh();
        res.redirect('/calc');
    } catch(error) {
        res.send('Не удалось выполнить расчет.')
    }
});

const { exec } = require('child_process')

function cleanSh() {
    const script1 = exec('cd /home/chrt/OpenFOAM/chrt-v2406/run/courseProject/Project; ./Clean.sh', 
        (error, stdout, stderr) => {
            console.log(stdout);
            console.log(stderr);
            if (error !== null) {
                console.log(`exec error: ${error}`);
            }
        });
        if (script1 == -1) {
            cleaned = 'Не удалось очистить файлы предыдущего решения.';
            return cleaned;
        } 
        else {
        cleaned = 'Файлы предыдущего решения успешно удалены.';
        return cleaned;
        }
}

function changeParams() {
    const script2 = exec(`
        cd /home/chrt/OpenFOAM/chrt-v2406/run/courseProject/Project;
        sed -i "2s/.*/${lc}/; 5s/.*/${lt}/; 8s/.*/${lr}/; 
        11s/.*/${lb}/; 14s/.*/${d0}/; 17s/.*/${dc}/;
        20s/.*/${ht}/; 23s/.*/${hb}/; 26s/.*/${U}/;" params.txt;
        ./ChangeParams.sh;`, (error, stdout, stderr) => {
        console.log(stdout);
        console.log(stderr);
        if (error !== null) {
            console.log(`exec error: ${error}`);
        }
    });
    if (script2 == -1) {
        changed = 'Не удалось внести изменения в файлы.';
        return changed;
    } 
    else {
        changed = 'Файлы решения успешно изменены.';
        return changed;
    }
}

function runSh() {
    // Выполняем команды
    const script3 = exec('cd /home/chrt/OpenFOAM/chrt-v2406/run/courseProject/Project; ./Run.sh', 
        (error, stdout, stderr) => {
        console.log(stdout);
        console.log(stderr);
        if (error !== null) {
            console.log(`exec error: ${error}`);
        }
    });

    // Возвращаем сообщение о запуске
    if (script3 == -1) {
        runned = 'Не удалось запустить решатель.';
        return runned;
    } 
    else {
        runned = 'Решатель успешно запущен. Ожидайте завершения выполнения расчета. ParaView запустится автоматически.';
        return runned;
    }
}


app.get('/result', function (req, res) {
    res.json({changedParams: `${changed}`, Cleaned: `${cleaned}`, Runned: `${runned}`, 
        Lc: `${lc}`, Lt: `${lt}`, Lr: `${lr}`, Lb: `${lb}`,
        D0: `${d0}`, Dc: `${dc}`, Ht: `${ht}`, Hb: `${hb}`,
        UU: `${U}`});//: `${}`
})

app.get('/calc',(req, res)=>{
    res.sendFile(__dirname + '/calc.html')
});