#define LOG_TAG "vendor.lampt.led.service"

#include<hidl/HidlSupport.h>          
#include<hidl/HidlTransportSupport.h> //Thu vien log

#include "LedHidl.h"

using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;
using ::android::sp;
using ::android::OK;
using ::vendor::lampt::led::V1_0::ILedHidl;
using ::vendor::lampt::led::implementation::LedHidl;

int main(int /*argc*/, char* /*argv*/ []) {
    ALOGI("Loading LedControl HIDL HAL...");

    configureRpcThreadpool(1, true /*will join*/);
    sp<ILedHidl> ledHidl = new LedHidl;
    if(ledHidl == nullptr) {
        ALOGE("Failed to get LedHidl instance");
    }

    if(ledHidl->registerAsService() != OK) {
        ALOGE("Could not register service");
        return 1;
    }

    joinRpcThreadpool();
    return 1;
}