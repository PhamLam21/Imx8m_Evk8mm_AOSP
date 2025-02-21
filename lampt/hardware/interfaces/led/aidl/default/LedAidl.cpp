#define LOG_TAG "vendor.lampt.hardware.ledAidl"

#include "LedAidl.h"
#include <utils/Log.h>

namespace aidl {
namespace vendor {
namespace lampt {
namespace hardware {
namespace led {
ndk::ScopedAStatus LedAidl::setLed(const std::string& in_value, int32_t* _aidl_return) {
    *_aidl_return = 1;
    ALOGI("%s: Led %s", __func__, in_value.c_str());
    return ndk::ScopedAStatus::ok();
}
ndk::ScopedAStatus LedAidl::getLed(std::string* _aidl_return) {
    *_aidl_return = "on";
    return ndk::ScopedAStatus::ok();
}
} // led
} // hardware
} // lampt
} // vendor
} // aidl
