// FIXME: your file license if you have one
#define LOG_TAG "vendor.lampt.led.iLedHidl"

#include "LedHidl.h"

namespace vendor {
namespace lampt {
namespace led {
namespace V1_0 {
namespace implementation {

// Methods from ::vendor::lampt::led::V1_0::ILedHidl follow.
Return<uint32_t> LedHidl::setLed(uint32_t value) {
    ALOGI("%s: OK with value = %d", __func__, value);
    return uint32_t {};
}

Return<uint32_t> LedHidl::getLed() {
    ALOGI("%s: OK", __func__);
    return uint32_t {};
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//ILedHidl* HIDL_FETCH_ILedHidl(const char* /* name */) {
    //return new LedHidl();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace led
}  // namespace lampt
}  // namespace vendor
