# multithreadlogger

#### 介绍
跨平台的多线程日志库，支持Windows和Linux操作系统

#### 软件架构
支持多线程并发使用。日志库内部维护了一个日志消息队列，支持多线程并发向消息队列中添加日志消息。
日志库内部同时保存了一个向系统写入文件的线程，当消息队列中有消息加入时，自动写入到系统文件中。


#### 安装教程

直接使用

#### 使用说明

```
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

```