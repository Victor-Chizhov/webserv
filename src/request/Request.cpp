#include "Request.hpp"

Request::Request() {}
Request::~Request() {}
void Request::Parsing(std::string const &input) {
	std::map<std::string, std::string>	headers;
	std::string							line;
	std::istringstream					iss(input);

	std::getline(iss, line);
	this->method = this->parseMethod(line);
	this->url = this->parseUrl(line);
	this->version = this->parseVersion(line);
	this->headers = this->parseHeaders(input);
    this->request = this->parseBody(input);
    this->body = this->parseBody(input);
    this->args = this->parseArgs();
}
Request::Request(Request const &src) {
	*this = src;
}
Request &Request::operator=(Request const &src) {
	if (this != &src) {
		this->method = src.method;
		this->url = src.url;
		this->version = src.version;
		this->headers = src.headers;
	}
	return *this;
}

std::string const &Request::getMethod() const {
	return this->method;
}

std::string const &Request::getVersion() const {
	return this->version;
}


std::string const &Request::getUrl() const {
	return this->url;
}

std::map<std::string, std::string> const &Request::getHeaders() const {
	return this->headers;
}

std::string const Request::parseMethod(std::string const &input) {
	std::istringstream	iss(input);
	std::string			method;

	std::getline(iss, method, ' ');
	return method;
}

std::string const Request::parseBody(std::string const &input) {
    std::string			body;

    // Находим пустую строку, разделяющую заголовки и тело
    size_t doubleLineBreakPos = input.find("\r\n\r\n");
    if (doubleLineBreakPos != std::string::npos) {
        // Если нашли разделение, извлекаем тело
        body = input.substr(doubleLineBreakPos + 4);
        return body;
    } else {
        // Если разделения нет, вернем пустую строку или что-то еще, что покажет отсутствие тела
        return "";
    }
}

std::string const Request::parseUrl(std::string const &input) {
	std::istringstream	iss(input);
	std::string			url;

	std::getline(iss, url, ' ');
	if (url.empty())
		throw std::invalid_argument("Invalid URL");
	std::getline(iss, url, ' ');
	if (url.empty())
		throw std::invalid_argument("Invalid URL");

	return url;
}

std::map<std::string, std::string> const Request::parseArgs() {
    std::map<std::string, std::string> args;
    std::string url = this->getUrl();
    std::string argsString;
    size_t argsStart = url.find('?');
    if (argsStart != std::string::npos) {
        argsString = url.substr(argsStart + 1);
        url = url.substr(0, argsStart);
    }
    std::istringstream iss(argsString);
    std::string arg;
    while (std::getline(iss, arg, '&')) {
        size_t argStart = arg.find('=');
        if (argStart != std::string::npos) {
            std::string key = arg.substr(0, argStart);
            std::string value = arg.substr(argStart + 1);
            args.insert(std::pair<std::string, std::string>(key, value));
        }
    }
    return args;
}

std::string const Request::parseVersion(std::string const &input) {
	return (input.substr(input.find("HTTP/")));
}

std::map<std::string, std::string> const Request::parseHeaders(std::string const &input) {
	std::map<std::string, std::string>	headers;
	std::istringstream					iss(input);
	std::string							line;

	std::getline(iss, line);
	while (std::getline(iss, line)) {
		if (line.empty() || line == "\n" || line == "\r" || line == "\r\n")
			continue;
		headers.insert(std::pair<std::string, std::string>(this->toLower(line.substr(0, line.find(":"))),
															line.substr(line.find(":") + 2)));
	}
	return headers;
}

std::string const Request::toLower(std::string const &input) {
	std::string	output;

	for (size_t i = 0; i < input.length(); i++)
		output += std::tolower(input[i]);
	return output;
}

std::string const &Request::getBody() const {
    return this->body;
}

const std::map<std::string, std::string> &Request::getArgs() const {
    return args;
}