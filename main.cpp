#include "common_logger.h"
#include "common_utils.h"

#include <thread>

AppLogger *g_pLogger = NULL;
int g_log_level = LOG_LEVEL_VERBOSE;

int main()
{
	if (!check_path_exists("/opt/logger/logs"))
	{
		create_directory_recursively("/opt/logger/logs");
	}

	AppLogger *pLogger = new AppLogger("logger");
	if (pLogger)
	{
		bool ret = pLogger->initialize("/opt/logger/logs", true, 1024 * 10, 10);
		std::cout << "AppLogger::initialize(): " << ret << std::endl;
	}
	g_pLogger = pLogger;

	LOG_INFO("Program begins.......");

	for (int i = 0; i < 10000; i++)
	{
		LOG_INFO("%d", i);
	}

	LOG_INFO("Program ends.......");

	std::this_thread::sleep_for(std::chrono::seconds(5));
	if (g_pLogger)
	{
		g_pLogger->uninitialize();
		delete g_pLogger;
	}

	return 0;
}

