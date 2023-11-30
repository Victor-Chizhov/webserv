#!/bin/bash

echo "HTTP/1.1 200 OK"
echo "Content-type: text/html"
echo ""
echo "<html>"
echo "<head>"
echo "<title>CGI Bash Script</title>"
echo "<head>"
echo "<body>"
echo "<h1>CGI Bash Script</h1>"
echo "<p>System Information:</p>"
echo "<pre>"
uname -a
echo "</pre>"
echo "</body>"
echo "</html>"