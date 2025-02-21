#define LOG_TAG "vendor.led.hardware-test"

//test -> ILedAidl (vendor binder) -> AIDL service (AIDL HAL)

#include<aidl/vendor/lampt/hardware/led/ILedAidl.h>
#include<utils/Log.h>
#include<android-base/logging.h>
#include<android/binder_manager.h>
#include<android/binder_process.h>
#include<binder/ProcessState.h>

using aidl::vendor::lampt::hardware::led::ILedAidl;
using ndk::ScopedAStatus;
using std::string;

int main() {

    std::string serviceName = std::string(ILedAidl::descriptor) + "/default";
    std::shared_ptr<ILedAidl> ledService = ILedAidl::fromBinder(
        ndk::SpAIBinder(AServiceManager_waitForService(serviceName.c_str()))); 
    if (ledService == nullptr) {
        ALOGE("Failed to get LED AIDL Service");
        return 1;
    }

    // Bật LED
    int32_t result = 0;
    ScopedAStatus status = ledService->setLed("on", &result);
    if(status.isOk()) {
        ALOGI("Set LED to ON: %s", "Success");
    } else {
        ALOGI("Set LED to ON: %s", "Failed"); 
    }
    sleep(1);

    // Đọc trạng thái LED
    string ledStatus;
    ledService->getLed(&ledStatus);
    ALOGI("LED Status: %s", ledStatus.c_str());

    sleep(1);

    return 0;
}
