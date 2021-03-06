#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

#include <microhttpd.h>

struct MHD_Daemon;
struct MHD_Connection;

struct gpu_data {
	std::string name;
	bool isInUse;
	std::string config;
};

typedef std::map<std::string, gpu_data> T_GPU_Map;

struct config_data {
	bool isNeedUpdate = false;

	int http_port = 8282;
	std::string pool_address = "mining.bit.tube:13333";
	std::string wallet_address = "bxd2iN7fUb2jA4ix9S37uw1eK2iyVxDbyRD5aVzCbFqj6PSMWP6G5eW1LgBEA6cqRUEUi7hMs1xXm5Mj9s4pDcJb2jfAw9Zvm";

	int cpu_count = -1;
	std::vector<std::string> nvidia_list;
	std::vector<std::string> amd_list;

	int current_cpu_count = -1;
	bool current_use_nvidia = false;
	bool current_use_amd = false;

	bool isMining = false;

	bool gpu_active = false;
	T_GPU_Map gpu_list;

	bool oldWeb = false;
	bool expertMode = false;
};

class httpd {

public:
	static httpd* inst() {

		if (oInst == nullptr) oInst = new httpd;
		return oInst;
	};

	static void cls() {	

		if (httpd::miner_config != nullptr) {
			delete httpd::miner_config;
			httpd::miner_config = nullptr;
		}

		if (oInst->d != nullptr) {
			MHD_stop_daemon(oInst->d);

#ifndef CONF_HTTPD_NO_HTTPS
			if (oInst->key_pem != nullptr) {
				delete oInst->key_pem;
				oInst->key_pem = nullptr;
			}

			if (oInst->cert_pem != nullptr) {
				delete oInst->cert_pem;
				oInst->cert_pem = nullptr;
			}
#endif
			

			delete oInst;
			oInst = nullptr;
		}


	};

	static config_data* miner_config;

	static void miningState(bool isMiningIN) {
		if (httpd::miner_config != nullptr) {
			httpd::miner_config->isMining = isMiningIN;
		}
	};

	bool start_daemon();

	static std::string getCustomInfo();

private:
	httpd();
	static httpd* oInst;

	static std::string parseCPUFile();
	static std::string parseGPUNvidiaFile();
	static std::string parseGPUAMD();
	static std::string parseConfigFile();
	static std::string parsePoolFile();

	static bool updateCPUFile();
	static bool updateGPUNvidiaFile();
	static bool updateGPUAMD();
	static bool updateConfigFile();
	static bool updatePoolFile();

	static bool parseCustomInfo (std::string keyIN, std::string valueIN);
	static void updateConfigFiles ();

	static int starting_process_post (MHD_Connection* connection,
												  const char* method,
												  const char* upload_data,
												  size_t* upload_data_size,
												  void ** ptr);

	static int send_page (struct MHD_Connection *connection,
								 const char *page);

	static int iterate_post (void *coninfo_cls, 
									 MHD_ValueKind kind, 
									 const char *key,
									 const char *filename, 
									 const char *content_type,
									 const char *transfer_encoding, 
									 const char *data, 
									 uint64_t off, 
									 size_t size);

	static void request_completed (void *cls, 
									struct MHD_Connection *connection, 
									void **con_cls,
									enum MHD_RequestTerminationCode toe);

	static int req_handler(void * cls,
								  MHD_Connection* connection,
								  const char* url,
								  const char* method,
								  const char* version,
								  const char* upload_data,
								  size_t* upload_data_size,
								  void ** ptr);

	MHD_Daemon *d;

	static std::string getGPUInfo();
	static void generateInfoHtml(std::string& out);

#ifndef CONF_HTTPD_NO_HTTPS
	char *key_pem = nullptr;
	char *cert_pem = nullptr;

	long sizePEMFiles(const char* filename);
	void loadPEMfiles();
#endif
};
