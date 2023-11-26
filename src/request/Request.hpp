#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "../../include/Libraries.hpp"

class Request {
	private:
		std::string method;
		std::string version;
		std::string url;
        std::string host;
        std::map<std::string, std::string> args;
        std::string body;
		std::map<std::string, std::string> headers;

		std::string const parseMethod(std::string const &input);
		std::string const parseUrl(std::string const &input);
		std::string const parseVersion(std::string const &input);
		std::string const parseHost(std::string const &input);
        std::map<std::string, std::string> const parseArgs();
        std::string const parseBody(std::string const &input);
		std::string const toLower(std::string const &input);
		std::map<std::string, std::string> const parseHeaders(std::string const &input);

	public:
        Request();
		~Request();
		void Parsing(std::string	const &input);
		Request(Request const &src);
		Request &operator=(Request const &src);

		std::string const &getMethod() const;
		std::string const &getVersion() const;
		std::string const &getUrl() const;
		std::string const &getHost() const;
        std::string const &getBody() const;
        const std::map<std::string, std::string> &getArgs() const;
		std::map<std::string, std::string> const &getHeaders() const;
        std::string request;


};

#endif
