#include "easylogging++.h"
#include <ctime>
#include <iostream>

#define ELPP_THREAD_SAFE
#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_STACKTRACE_ON_CRASH

const std::string MSG_FORMAT = " - %msg";
const std::string DEFAULT_LOG_CFG = "defaultlog.cfg";
const std::string DEFAULT_LOG_EXTENSION = ".log";

//INITIALIZE_EASYLOGGINGPP

class DefaultLogManager
{
public:
	
	enum LOG_CONFIG { SAME_FILE, DAILY_FILE, EXECUTION_FILE };

	// inicializar el helper
	void initialize(std::string fileName, LOG_CONFIG cfg)
	{
		// generar el nombre del archivo del log
		time_t t = time(0);
		struct tm * now = localtime( & t );
		switch(cfg) 
		{
		case SAME_FILE:
			mCurrentLogFile = fileName; break;
		case DAILY_FILE:
			mCurrentLogFile = fileName + "." 
				+ std::to_string(now->tm_year + 1900) 
				+ std::to_string(now->tm_mon + 1) 
				+ std::to_string(now->tm_mday); break;
		case EXECUTION_FILE:
			mCurrentLogFile = fileName + "." 
				+ std::to_string(now->tm_year + 1900) 
				+ std::to_string(now->tm_mon + 1) 
				+ std::to_string(now->tm_mday) + "_" 
				+ std::to_string(now->tm_hour) 
				+ std::to_string(now->tm_min); break;
		default:
			mCurrentLogFile = fileName;
		}
		mCurrentLogFile += DEFAULT_LOG_EXTENSION;
		mCurrentFormat = "%datetime{%H:%m:%s} - [ %level][%fbase:%line]";
		// configurar la instancia de easylogging
		el::Configurations currentConfig(DEFAULT_LOG_CFG);
		currentConfig.setGlobally(el::ConfigurationType::Filename, mCurrentLogFile);
		el::Loggers::reconfigureAllLoggers(currentConfig);
		el::Loggers::addFlag(el::LoggingFlag::LogDetailedCrashReason);
		el::Loggers::addFlag(el::LoggingFlag::AutoSpacing);
	};

	bool addCustomMetadata(std::string format, const el::CustomFormatSpecifier &resolver, bool reconfigure = true)
	{
		try 
		{
			el::Helpers::installCustomFormatSpecifier(resolver);
		} 
		catch (...)
		{
			LOG(ERROR) << "customMetadata" << "No se pudo instalar el CustomFormatSpecifier";
			return false;
		}

		addFormat(format, reconfigure);

		return true;
	};

	void addFormat(std::string format, bool reconfigure = true)
	{
		mCurrentFormat += "[" + format + "]";
		if(reconfigure)
			reconfigureLog();
	};

	void removeFormat(std::string format, bool reconfigure = true)
	{
		std::string str = "[" + format + "]";
		std::string::size_type i = mCurrentFormat.find(str);
		if (i != std::string::npos)
		   mCurrentFormat.erase(i, str.length());
		// Uninstall custom format specifier
		el::Helpers::uninstallCustomFormatSpecifier(format.c_str());
		if(reconfigure)
			reconfigureLog();
	}

	void reconfigureLog(void)
	{
		el::Configurations currentConfig;
		currentConfig.setGlobally(el::ConfigurationType::Filename, mCurrentLogFile);
		currentConfig.setGlobally(el::ConfigurationType::Format, mCurrentFormat + MSG_FORMAT);
		el::Loggers::reconfigureAllLoggers(currentConfig);
	};

private:

	std::string mCurrentFormat;
	std::string mCurrentLogFile;
};
