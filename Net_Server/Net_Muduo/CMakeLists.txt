project(Server)

include_directories(./ ./Code)



set(net_main
	main.cpp
	Code/Base/*.*
	Code/Net/*.*)

add_executable(net_test ${net_main})