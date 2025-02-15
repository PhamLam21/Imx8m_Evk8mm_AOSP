#define LOG_TAG "vendor.lampt.led-Test"

#include <vendor/lampt/led/1.0/ILedHidl.h>
#include <hidl/Status.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <utils/Log.h>

using vendor::lampt::led::V1_0::ILedHidl;
using android::sp;
using android::hardware::hidl_string;

int main() {
    sp<ILedHidl> ledService = ILedHidl::getService();
    if (ledService == nullptr) {
        ALOGE("Failed to get LED HIDL Service");
        return 1;
    }

    // Bật LED
    bool result = ledService->setLed("on");
    ALOGI("Set LED to ON: %s", (result ? "Success" : "Failed"));
    sleep(1);
    // Đọc trạng thái LED
    ledService->getLed([](const hidl_string& status) {
        ALOGI("LED Status: %s", status.c_str());
    });
    sleep(1);
    return 0;
}
