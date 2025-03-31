#define LOG_TAG "vendor.lampt.hardware.ledAidl"

#include "LedAidl.h"

//constexpr char ledValueProperty[] = "vendor.led.value";
#define LED_DEFAULT "on"

namespace aidl {
namespace vendor {
namespace lampt {
namespace hardware {
namespace led {
ndk::ScopedAStatus LedAidl::setLed(const std::string& in_value, int32_t* _aidl_return) {
    std::ofstream led_dev("/dev/led_demo");  // Mở file trực tiếp

    if (!led_dev.is_open()) {  // Kiểm tra nếu không mở được
        ALOGE("SetLed: Cannot open /dev/led_demo");
        *_aidl_return = -1;  // Trả về lỗi
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    led_dev << in_value;  // Ghi giá trị vào thiết bị
    if (led_dev.fail()) {  // Kiểm tra lỗi ghi file
        ALOGE("SetLed: Failed to write to /dev/led_demo");
        *_aidl_return = -2;
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    led_dev.close();  // Đóng file sau khi ghi
    *_aidl_return = 1;
    ALOGI("SetLed: LED set to %s", in_value.c_str());

    return ndk::ScopedAStatus::ok();
}
ndk::ScopedAStatus LedAidl::getLed(std::string* _aidl_return) {
    std::ifstream led_dev("/dev/led_demo");  // Mở file để đọc

    if (!led_dev.is_open()) {  // Kiểm tra lỗi mở file
        ALOGE("GetLed: Cannot open /dev/led_demo");
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    std::string led_status;
    led_dev >> led_status;  // Đọc trạng thái LED từ file

    if (led_dev.fail()) {  // Kiểm tra lỗi đọc file
        ALOGE("GetLed: Failed to read from /dev/led_demo");
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    led_dev.close();  // Đóng file
    *_aidl_return = led_status;  // Gán kết quả đọc được
    ALOGI("GetLed: LED status = %s", led_status.c_str());

    return ndk::ScopedAStatus::ok();
}
} // led
} // hardware
} // lampt
} // vendor
} // aidl
