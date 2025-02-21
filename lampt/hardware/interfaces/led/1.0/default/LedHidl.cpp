// FIXME: your file license if you have one

#include "LedHidl.h"

namespace vendor::lampt::led::implementation {

// Methods from ::vendor::lampt::led::V1_0::ILedHidl follow.
Return<bool> LedHidl::setLed(const hidl_string& value) {
    // TODO implement
    return true;
}

Return<void> LedHidl::getLed(getLed_cb _hidl_cb) {
    // TODO implement

    _hidl_cb("on");
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//ILedHidl* HIDL_FETCH_ILedHidl(const char* /* name */) {
    //return new LedHidl();
//}
//
}  // namespace vendor::lampt::led::implementation
