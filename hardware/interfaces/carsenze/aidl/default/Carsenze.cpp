
#define LOG_TAG "Carsenze_HAL_service"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <sstream>
#include <string>
#include "Carsenze.h"

namespace aidl {
    namespace android {
        namespace hardware {
            namespace carsenze {
                //String getMemoryStats();
                ndk::ScopedAStatus Carsenze::getMemoryStats(std::string* _aidl_return) {
                    ALOGD("***-Memory Info is REQUESTED-***");
                    struct sysinfo memInfo;
                    sysinfo(&memInfo);
                     // Calculate total physical memory in bytes
                     long long int totalPhysMem = memInfo.totalram;
                     totalPhysMem *= memInfo.mem_unit;

                    // Calculate free physical memory in bytes
                    long long int freePhysMem = memInfo.freeram;
                    freePhysMem *= memInfo.mem_unit;
                    // Calculate used physical memory in bytes
                    long long int usedPhysMem = totalPhysMem - freePhysMem;

                    // Convert memory values to megabytes and format the output string
                    std::ostringstream oss;
                    oss << "Total RAM: " << (totalPhysMem / (1024 * 1024)) << " MB\n"
                    << "Free RAM: " << (freePhysMem / (1024 * 1024)) << " MB\n"
                    << "Used RAM: " << (usedPhysMem / (1024 * 1024)) << " MB";
                    *_aidl_return = oss.str();
                    return ndk::ScopedAStatus::ok();
                }
                //String getCpuStats();
                ndk::ScopedAStatus Carsenze::getCpuStats(std::string* _aidl_return) {
                    ALOGD("***-CPU Info is REQUESTED-***");
                    *_aidl_return =  "CPU = 74.32 %";
                    return ndk::ScopedAStatus::ok();
                }
                //String getNetworkStats();
                ndk::ScopedAStatus Carsenze::getNetworkStats(std::string* _aidl_return) {
                    ALOGD("***-Network Info is REQUESTED-***");
                    *_aidl_return =  "Network = 10 Mb/s";
                    return ndk::ScopedAStatus::ok();
                }
            }  // namespace carsenze
        }  // namespace hardwares
    }  // namespace android
}  // namespace aidl

