
function sendNumber() {
    console.log('sendNumber function called');
    // Получите значение из инпута
    var numberValue = document.getElementById('numberInput').value;

    // Используйте fetch без .json()
    fetch('bin-cgi/what_day.py?Number=' + numberValue, {
        method: 'GET',
    })
        .then(response => {
            // Перенаправление на нужную страницу
            window.location.href = 'bin-cgi/what_day.py?Number=' + numberValue;
        })
        .catch(error => {
            console.error('Error:', error);
        });
}