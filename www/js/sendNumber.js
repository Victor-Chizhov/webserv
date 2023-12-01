
function sendNumber() {
    console.log('sendNumber function called');

    let numberValue = document.getElementById('numberInput').value;

    fetch('bin-cgi/what_day.py?Number=' + numberValue, {
        method: 'GET',
    })
        .then(response => {

            window.location.href = 'bin-cgi/what_day.py?Number=' + numberValue;
        })
        .catch(error => {
            console.error('Error:', error);
        });
}