// FIXME: your file license if you have one

#pragma once

#include <vendor/lampt/led/1.0/ILedHidl.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace vendor {
namespace lampt {
namespace led {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct LedHidl : public ILedHidl {
    // Methods from ::vendor::lampt::led::V1_0::ILedHidl follow.
    Return<uint32_t> setLed(uint32_t value) override;
    Return<uint32_t> getLed() override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" ILedHidl* HIDL_FETCH_ILedHidl(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace led
}  // namespace lampt
}  // namespace vendor
