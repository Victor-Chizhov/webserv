function fileUpload(input) {
    const file = input.files[0];
    var reader = new FileReader();
	reader.onload = function(e) {
		
        fetch('/upload', {
            method: 'POST',
            body: btoa(e.target.result)
        })
            .then(response => response.text())
            .then(data => {
                console.log('File uploaded successfully:', data);
            })
            .catch(error => {
                console.error('Error uploading file:', error);
            })
	};
	reader.onerror = function(e) {
		// error occurred
		console.log('Error : ' + e.type);
	};
	reader.readAsBinaryString(file);
}