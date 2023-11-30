function fileUpload(input) {
    const file = input.files[0];
    var reader = new FileReader();
	reader.onload = function(e) {
		
        fetch('/upload', {
            method: 'POST',
            body: btoa(e.target.result)
        })
            .then(response => {
                if (!response.ok) {
                    window.location.href = 'errorPages/413.html';
                }
                return response.text();
            })
            .then(data => {
                console.log('File uploaded successfully. Response from server:', data);
            })
            .catch(error => {
                console.error('Error uploading file:', error.message);
            });
	};
	reader.onerror = function(e) {
		// error occurred
		console.log('Error : ' + e.type);
	};
	reader.readAsBinaryString(file);
}