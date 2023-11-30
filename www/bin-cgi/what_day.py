import os
from datetime import datetime, timedelta

def printError(error_str):
    print("HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html;charset=utf-8\r\n\r\n")
    print("<H1>" + error_str + "</H1>")

try:
    current_date = datetime.now().date()
except OSError as e:
    printError("Error obtaining current time: {}".format(e))

number = os.environ.get("Number", "1")

def printError(error_str):
    print "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html;charset=utf-8\r\n\r\n" #may be should return Vitya's HTML error page
    print "<H1>" + error_str + "</H1>"

try:
        try:
            new_date = current_date + timedelta(int(number))
            weekday = new_date.strftime("%A")
            HTML = """
<!DOCTYPE html>
<html lang="en">
<head>
    <!-- basic -->
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- mobile metas -->
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="viewport" content="initial-scale=1, maximum-scale=1">
    <!-- site metas -->
    <title>CGI Python</title>
    <meta name="keywords" content="">
    <meta name="description" content="">
    <meta name="author" content="">
    <!-- bootstrap css -->
    <link rel="stylesheet" type="text/css" href="../css/bootstrap.min.css">
    <!-- style css -->
    <link rel="stylesheet" type="text/css" href="../css/style.css">
    <!-- Responsive-->
    <link rel="stylesheet" href="../css/responsive.css">
    <!-- fevicon -->
    <!-- Scrollbar Custom CSS -->
    <link rel="stylesheet" href="../css/jquery.mCustomScrollbar.min.css">
    <!-- Tweaks for older IEs-->
    <link rel="stylesheet" href="https://netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css">
    <!-- fonts -->
    <link href="https://fonts.googleapis.com/css?family=Poppins:400,700|Righteous&display=swap" rel="stylesheet">
    <!-- owl stylesheets -->
    <link rel="stylesheet" href="../css/owl.carousel.min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/fancybox/2.1.5/jquery.fancybox.min.css" media="screen">
</head>
<body>
    <!-- header section start -->
    <div class="header_section">
        <div class="header_main">
            <div class="mobile_menu">
                <nav class="navbar navbar-expand-lg navbar-light bg-light">
                    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
                        <span class="navbar-toggler-icon"></span>
                    </button>
                    <div class="collapse navbar-collapse" id="navbarNav">
                        <ul class="navbar-nav">
                            <li class="nav-item">
                                <a class="nav-link" href="../index.html">Home</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="../about.html">About</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link" href="../42yerevan.html">42 Yerevan</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link " href="../info.html">Info</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link " href="../cgi.html">CGI</a>
                            </li>
                        </ul>
                    </div>
                </nav>
            </div>
            <div class="container-fluid">
                <div class="menu_main">
                    <ul>
                        <li class="active"><a href="../index.html">Home</a></li>
                        <li><a href="../about.html">About</a></li>
                        <li><a href="../42yerevan.html">42 Yerevan</a></li>
                        <li><a href="../info.html">Info</a></li>
                        <li><a href="../cgi.html">CGI</a></li>
                    </ul>
                </div>
            </div>
        </div>
    </div>
    <!-- header section end -->
    <!-- contact section start -->
    <div class="contact_section layout_padding" style="height: 51vh;">
        <h1 class="contact_taital" style="margin-top: 50px;">{new_date}, {weekday}</h1>
    </div>
    <!-- contact section end -->
    <!-- footer section start -->
    <div class="footer_section">
        <div class="container">
            <footer class="bg-color text-white mt-6">
                <div class="container">
                    <div class="row py-5">
                        <div class="col-12 col-md-6 col-lg-4 mb-4">
                            <div class="pe-lg-5 pe-0 pe-md-3">
                                <img src="../images/logo42white.svg" alt="" width="200" class="mb-3">
                                <p class="opacity-75">
                                    <b>Webserv Project</b>
                                </p>
                            </div>
                        </div>
                   <div class="col-12 col-md-6 col-lg-4 mb-4">
                     <h6 class="text-uppercase fw-bold mb-4 text-white">
                       <b>42 Yerevan</b>
                     </h6>
                     <p class="opacity-75">
                       <a href="../about.html" class="text-decoration-none text-white">
                         About Project
                       </a>
                     </p>
                     <p class="opacity-75">
                       <a href="../info.html" class="text-decoration-none text-white">
                         What is Webserver
                       </a>
                     </p>
                     <p class="opacity-75">
                       <a href="../cgi.html" class="text-decoration-none text-white">
                        Common Gateway Interface
                       </a>
                     </p>
                     <p class="opacity-75">
                         <a href="../42yerevan.html" class="text-decoration-none text-white">
                             42 Yerevan
                         </a>
                     </p>
                   </div>
                        <div class="col-12 col-md-6 col-lg-4 mb-4">
                            <p class="opacity-75">
                                <font-awesome-icon icon="fa-solid fa-home" class="me-3" />
                                2a Halabyan St, Yerevan 0038
                            </p>
                            <p class="opacity-75">
                                <font-awesome-icon icon="fa-solid fa-envelope" class="me-3" />
                                info@42yerevan.am
                            </p>
                            <p class="opacity-75">
                                <font-awesome-icon icon="fa-solid fa-phone" class="me-3" />
                                +374 10 398413
                            </p>
                            <p class="opacity-75 mt-5 underline">
                            </p>
                        </div>
                    </div>
                </div>
                <!-- Copyright -->
                <div class="text-center p-4" style="background-color: rgba(0, 0, 0, 0.35);">
                     2023 Copyright 42 Yerevan
                </div>
                <!-- Copyright -->
            </footer>
        </div>
    </div>
</body>
</html>
""".format(new_date=new_date, weekday=weekday)

            print("HTTP/1.1 200 OK")
            print("\r\n")
            print(HTML)
        except ValueError:
            printError("Invalid input: BODY is not a valid integer.")
except Exception as e:
    printError("Error: {}".format(e))