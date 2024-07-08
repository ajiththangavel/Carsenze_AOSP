
#define LOG_TAG "Carsenze_HAL_service"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include <sys/sysinfo.h>
#include <sstream>
#include <string>
#include <vector>
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

                    double usage = calculateCpuUsage();
                    *_aidl_return = "CPU Usage = " + std::to_string(usage) + " %";
                    return ndk::ScopedAStatus::ok();
                }
                //String getNetworkStats();
                ndk::ScopedAStatus Carsenze::getNetworkStats(std::string* _aidl_return) {
                    ALOGD("***-Network Info is REQUESTED-***");
                    
                    std::string path = "/sys/class/net/wlan0/operstate";
                    std::ifstream operstateFile(path);

                    if (!operstateFile.is_open()) {
                         ALOGD("***-Failed to open file /sys/class/net/wlan0/operstate-***");

                    }

                    std::string operstate;
                    operstateFile >> operstate;
                    operstateFile.close();

                    if (operstate == "up") {
                         *_aidl_return = "Connected";
                    } else if (operstate == "down") {
                         *_aidl_return = "Disconnected";
                    } else {
                         *_aidl_return = "Error";
                    }
                                
                    return ndk::ScopedAStatus::ok();
                }
                double Carsenze::calculateCpuUsage() {
                    std::ifstream file("/proc/stat");
                    
                     if(!file.is_open()) {
                    ALOGE("**-Failed to open /proc/stat-**");
                     }

                    std::string line;
                    std::getline(file, line);

                    std::istringstream ss(line);
                    std::string cpu;
                    ss >> cpu;

                    std::vector<long long> times;
                    long long time;
                    while (ss >> time) {
                        times.push_back(time);
                    }

                    if (times.size() < 4) {
                        return 0.0;
                    }

                    long long total = 0;
                    for (long long t : times) {
                        total += t;
                    }

                    long long idle = times[3];

                    long long totalDiff = total - prevTotalTime;
                    long long idleDiff = idle - prevIdleTime;

                    prevTotalTime = total;
                    prevIdleTime = idle;

                    if (totalDiff == 0) {
                        return 0.0;
                    }

                    return (double)(totalDiff - idleDiff) / totalDiff * 100.0;
                }
            }  // namespace carsenze
        }  // namespace hardwares
    }  // namespace android
}  // namespace aidl

