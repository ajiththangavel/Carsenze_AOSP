
#define LOG_TAG "Carsenze"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "Carsenze.h"

namespace aidl {
    namespace android {
        namespace hardware {
            namespace carsenze {
                //String getMemoryStats();
                ndk::ScopedAStatus Carsenze::getMemoryStats(std::string* _aidl_return) {
                    ALOGD("***-Memory Info is REQUESTED-***");
                    *_aidl_return =  "Memory = 1024 MB";
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
