#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <sstream>
#include <map>

class Request {
	private:
		std::string method;
		std::string version;
		std::string url;
		std::map<std::string, std::string> headers;

		Request();

		std::string const parseMethod(std::string const &input);
		std::string const parseUrl(std::string const &input);
		std::string const parseVersion(std::string const &input);
		std::string const parseHost(std::string const &input);
		std::string const toLower(std::string const &input);
		std::map<std::string, std::string> const parseHeaders(std::string const &input);

	public:
		~Request();
		Request(std::string	const &input);
		Request(Request const &src);
		Request &operator=(Request const &src);

		std::string const &getMethod() const;
		std::string const &getVersion() const;
		std::string const &getUrl() const;
		std::string const &getHost() const;
		std::map<std::string, std::string> const &getHeaders() const;
};

#endif
