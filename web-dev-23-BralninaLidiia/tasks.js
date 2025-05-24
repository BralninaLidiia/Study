import { callbackOut } from './callback.js'

//Корень из числа
export function calculateSquareRoot(number) {
    if (number < 0) {
      throw new Error("Нельзя извлечь корень из отрицательного числа")
    }
    return Math.sqrt(number)
}

//Счетчики
export function createCounter() {
    let counter = 0
    return function() {
      counter++
      return counter
    }
}

//Логгер
export function periodicLogger(message, interval){
    let count = 0
    const intervalId = setInterval(() => {count = callbackOut(message, count)}, interval)
    return function stopLogger() {
        clearInterval(intervalId)
        console.log(`Логгер остановлен после ${count} интервалов.`)
    }
}

//Данные пользователя
export async function getUserData(userId, callback){
    if (typeof userId !== 'number') {
        return callback(new Error('UserId должен быть числовым значением'), null)
    }

    try {
        await new Promise(resolve => setTimeout(resolve, 1000))
        if (Math.random() < 0.5) {    
            const userData = {
                userId: userId,
                username: 'BralninaLS',
                email: 'sateshy77@gmail.com'
            }
            callback(null, userData)
        }
        else{
            throw new Error('Ошибка при запросе данных')
        }
    }
    catch (error) {
        callback(error, null)
    }
}

//Отрправка почты 
export async function sendEmail(emailAddress, callback) {
    if (emailAddress.indexOf("@") === -1) {
        callback(new Error('В адресе нет символа @'), null)
    }
    else {
        await new Promise(resolve => setTimeout(resolve, 1000))
        if (Math.random() < 0.5) {
            callback(null, "Успешно отправлено")
        }
        else {
            callback(new Error('Ошибка отправки'),null)
        } 
    }
}