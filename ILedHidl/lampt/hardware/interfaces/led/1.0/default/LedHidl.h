// FIXME: your file license if you have one

#pragma once

#include <vendor/lampt/led/1.0/ILedHidl.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor::lampt::led::implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct LedHidl : public V1_0::ILedHidl {
    // Methods from ::vendor::lampt::led::V1_0::ILedHidl follow.
    Return<bool> setLed(const hidl_string& value) override;
    Return<void> getLed(getLed_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ILedHidl* HIDL_FETCH_ILedHidl(const char* name);

}  // namespace vendor::lampt::led::implementation
