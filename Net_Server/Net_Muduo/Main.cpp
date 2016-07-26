#include <iostream>
#include "Net/EventLoop.h"

using namespace xtProxima;

void ThreadFunc()
{
	EventLoop el;
	el.Loop();
}

int main(int argc, char* argv[])
{
	std::thread t(ThreadFunc);
	t.join();
	getchar();
	return 0;
}