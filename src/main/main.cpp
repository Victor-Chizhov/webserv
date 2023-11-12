#include "../../include/Config.hpp"
#include "../request/Request.hpp"
#include "../../include/Parser.hpp"
#include "../../include/ServerSocket.hpp"


int main(int argc, char **argv) {


	(void)argc;
	ServerSocket run;
	run.configure(atoi(argv[1]), 32);
	run.start();


    return 0;
}
