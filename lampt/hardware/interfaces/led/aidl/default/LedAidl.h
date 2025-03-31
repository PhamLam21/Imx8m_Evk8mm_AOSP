#pragma once //Tranh viec include 2 lan file .h

#include<aidl/vendor/lampt/hardware/led/BnLedAidl.h> 
#include<string>
#include<android-base/properties.h>
#include<utils/Log.h>
#include<fstream>

namespace aidl {
namespace vendor {
namespace lampt {
namespace hardware {
namespace led {

class LedAidl : public BnLedAidl {
public: 
    ndk::ScopedAStatus setLed(const std::string& in_value, int32_t* _aidl_return);
    ndk::ScopedAStatus getLed(std::string* _aidl_return);
};
} // led
} // hardware
} // lampt
} // vendor
} // aidl
