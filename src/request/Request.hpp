#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>
#include <map>

class Request {
	private:
		std::string metod;
		std::string	host;
		std::string port;
		std::map<std::string, std::string> headers;
	
	public:
		Request();
		~Request();
		Request(std::string	const &input);
		Request(Request const &src);
		Request &operator=(Request const &src);
};

#endif
