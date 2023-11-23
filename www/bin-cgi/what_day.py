#с помощью этого скрипта можно узнать какой день будет через n дней. То есть на фронтенде вывести текущую дату и написать строку:
#какой день будет через n(поле) дней?

import os
from datetime import datetime, timedelta

def printError(error_str):
    print("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html;charset=utf-8\r\n\r\n")
    print("<H1>" + error_str + "</H1>")

try:
    current_date = datetime.now()
except OSError as e:
    printError("Error obtaining current time: {}".format(e))

file_path = os.environ.get("BODY_FILE", "1")

def printError(error_str):
    print "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html;charset=utf-8\r\n\r\n",
    print "<H1>" + error_str + " doesn't set" + "</H1>"

try:
    # Open the file for reading
    with open(file_path, "r") as file:
        # Read the content of the file
        file_data = file.read()
    if file_data:
        try:
            new_date = current_date + timedelta(int(file_data))
            print("HTTP/1.1 200 OK")
            print("\r\n")
            print(new_date)
            print("\r\n")
        except ValueError:
            printError("Invalid input: BODY is not a valid integer.")
    else:
        printError("BODY is not set or is an empty string.")
except Exception as e:
    printError("Error: {}".format(e))