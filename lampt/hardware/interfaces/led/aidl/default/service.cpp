#define LOG_TAG "vendor.led.hardware-service"

#include<android-base/logging.h>
#include<android/binder_manager.h>
#include<android/binder_process.h>
#include<binder/ProcessState.h>
#include"LedAidl.h"

using aidl::vendor::lampt::hardware::led::LedAidl;
int main() {
    // Bat vndbinder de giao tiep vendor-vendor
    android::ProcessState::initWithDriver("/dev/vndbinder");

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();

    std::shared_ptr<LedAidl> ledService = ndk::SharedRefBase::make<LedAidl>();
    const std::string name = std::string() + LedAidl::descriptor + "/default"; //vendor.lampt.hardware.led.IledAidl/default 

    if(ledService != nullptr) {
        if(AServiceManager_addService(ledService->asBinder().get(), name.c_str()) != STATUS_OK) {
            ALOGE("FAILED to add service");
            return -1;
        }
    } else {
        ALOGE("FAILED to add service");
        return -1;
    }

    ALOGD("ILed service start to join service pool");
    ABinderProcess_joinThreadPool();

    return EXIT_FAILURE; 
}
