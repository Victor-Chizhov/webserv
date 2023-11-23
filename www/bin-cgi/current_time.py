import datetime

def printError(error_str):
    print("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html;charset=utf-8\r\n\r\n")
    print("<H1>" + error_str + "</H1>")

try:
    current_time = datetime.datetime.now()
    print("HTTP/1.1 200 OK")
    print("\r\n")
    print(current_time)
    print("\r\n")
except OSError as e:
    printError("Error obtaining current time: {}".format(e))
