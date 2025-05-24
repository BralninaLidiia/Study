export function callbackOut(message, count) {
    count++
    console.log(message, count)
    return count 
}

export function callbackDataOut(error, userData) {
    if (error) {
        console.error('Ошибка:', error.message)
    } 
    else {
        console.log('Данные:')
        console.log(`id: ${userData.userId}, Имя: ${userData.username}, email: ${userData.email}`)
    }
}

export function callbackEmailOut(error, message) {
    if (error) {
        console.error('Ошибка:', error.message)
    } 
    else {
        console.log(message)
    }
}