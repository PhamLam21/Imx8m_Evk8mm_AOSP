"# Imx8m_Evk8mm_AOSP" 
## Tìm hiểu chung 
- Các bên đóng góp, xây dựng AOSP:  
    - OSS community: cộng đồng làm việc, sử dụng aosp -> đóng góp phát hiện lỗi, sửa
	- Google : code phát triển android
	- Gerrit : giống GitHub -> day code len 
	- kernel.org : tổ chức Linux kernel đóng góp vào android  
- Các bên sử dụng AOSP -> Silicon vendor : Sử dụng aosp thay đổi phù hợp với chip của mình 
    - board vendor : dùng chip bên silicon vendor tạo ra các board sử dụng 
	- design house : giống vinfast  
## Android architecture  
- Application -> ứng dụng tương tác trực tiếp với người dùng  
- Java API framework -> bộ các thư viện được cung cấp cho các mục đích cụ thể (tập hợp các API -> vd: tập hợp các API phân tích bản tin GNSS) 
- Native libraries -> android NDK -> Thư viện bằng c/c++ (Thư viện xử lý 1 việc -> vd: thuật toán xử lý hình ảnh), có thể là thư viện của bên thứ 3, giao tiếp với các lớp sau
- Android runtime -> virtual machine 
- Hardware abstraction layer ->  lớp trừu tượng hardware -> giao tiếp với hardware thật -> cung cấp func, api cho các lớp trên
- Linux kernel  
## Kernel  
Viết driver mới: Trong vendor -> nxp-opensource -> kernel_nxp -> drivers -> tao folder cua minh -> them .c , Makefile  

Cách thêm drive của mình tự build: vendor - nxp-opensource - kernel_nxp - arch - arm64 - configs - ten_board_gki.fragment  
- Thêm: 
    ```  
    CONFIG_LED_DEMO=y -> tạo .ko
    CONFIG_LED_DEMO=m -> tạo module 
    ```  
Cách để load driver vào board để mỗi khi khởi động có sẵn driver: 
- device -> (board) -> SharedBoardConfig.mk -> them module .ko vao  

Khi build xong tìm file .ko trong: out -> targer - product -> evk_8mm -> obj -> KERNEL_OBJ -> drivers  
## GKI modules  
<p align = "center">
<img src = "https://static1.xdaimages.com/wordpress/wp-content/uploads/2021/09/New-GKI-apprach-to-isolate-vendor-modules-reduce-fragmentation.jpg" width = "400" height = "200">  

- GKI modules -> module gg viết sẵn -> hỗ trợ test rất kĩ -> thư mục kernel -> kernel gốc
- vendor modules -> modules nhà phát triển viết ->  có thể sửa đổi, giao tiếp GKI qua KMI (kernel module interface) -> vendor (viet driver kernel trong vendor)  

## JNI (Java native interface)
- Giao tiep giữa service phía triên với hal, do hal sử dụng c++, service phía trên sử dụng java
- Là các wrapper function: hàm gọi đến hàm  

## BINDER IPC
**Binder** một giao tiếp liên tiến trình được sử dụng trong AOSP sử dụng kiến trúc: client-server, cơ chế: RPC -> đóng gói, gửi
- Binder Proxy (Bp) -> client transact (Đã gửi)
- Binder Stub (Bn) -> server onTransact (Đã nhận)
- SeLinux: binder -> cau hinh selinux nhung phan duoc su dung  
## AOSP .img và partition quan trọng
- dtbo-"...".img: Device tree của board
- vbmeta-"...".img: check mã hash của device tree có match với kernel không tránh lỗi hoặc nạp firm trái phép 
- system.img: system và root folder
- system_ext.img: Các service thêm
- product.img: product folder  
- partition-table.img: Để android biết sẽ boot từ phân vùng nào lấy thông tin các img từ đâu
- u-boot-"...".img: đóng gói trong boot.img
- vendor.img: vendor folder
- vendor_dlkm.img (Phân vùng động): chứa các mô-đun có thể tải động vào kernel khi cần thiết.
- super.img: system, system_ext, vendor, vendor_dlkm, product
- boot.img: u-boot, kernel image ...  

Tìm hiểu partiontion: [AOSP](https://source.android.com/docs/core/architecture/partitions)  
Tìm hiểu dynamic partition : [AOSP](https://source.android.com/docs/core/ota/dynamic_partitions/implement)  
## HAL
- Hal để người dùng phía trên giao tiếp với phần cứng đỡ phức tạp -> thể hiện tính trừu tượng -> viết các API đơn giản hóa cho người dùng không cần hiểu sâu về phần cứng hoạt động như nào.
Vd: việc scan wifi và bluetooth -> người dùng nhấn scan thì việc xử lý sẽ do hal và gửi xuống kernel giảm phức tạp cho người sử dụng  
- Khởi điểm cho user space giúp hiệu suất tốt nhất  
### HIDL  
Giai đoạn trước Android 8 (trước Project Treble)  
Trước khi Android 8.0 (Oreo) ra mắt:  
- HAL (Hardware Abstraction Layer) được viết bằng C/C++.
- Dùng shared libraries (.so), liên kết trực tiếp với Android Framework, nạp trực tiếp vào System Process.
- Framework thay đổi thì HAL cũng phải thay đổi → Tốn nhiều công sức porting driver khi nâng cấp Android.  

Vấn đề lớn:  
- Vendor HAL được build tĩnh (include vào Framework).
- Mỗi lần update Android, driver phải rebuild lại, dẫn đến fragmentation.
- Lỗi trong HAL có thể làm crash cả System Process.  

Project Treble (Android 8.0) tách Vendor HAL ra khỏi Framework.  
- HIDL dùng hwbinder để giao tiếp giữa Android Framework và HAL.
- Không cần build lại Vendor HAL khi update Android.
- Không còn liên kết shared libraries giữa Framework và HAL. 
- HIDL vẫn có binary .so, nhưng chỉ là IMPLEMENTATION, không còn gắn trực tiếp vào System Process.
- HAL chạy trong một tiến trình (vendor process) riêng biệt, giao tiếp với System Process qua hwbinder. 

Kết quả:  
- Android Framework có thể update mà không cần thay đổi driver của vendor.
- Giảm fragmentation giữa các thiết bị.  

<p align = "center">
<img src = "https://github.com/PhamLam21/Imx8m_Evk8mm_AOSP/blob/main/20200805204512893.jpg" width = "600" height = "600">  

- version: 
    - 8.x về trước sử dụng legacy HAL
	- 8.x đến 10.x sử dụng HIDL
	- 11.x về sau sử dụng AIDL  
- Tạo mới HIDL    
    - Tạo các file cần thiết
	- vendor - lampt (thay bang tên cty làm sp) - hardware - interfaces - led (ten HAL) - 1.0 (phien ban)
	- Tạo 1 file Android.bp ở folder interface -> de khai bao duong dan thu muc moi tao
	- Tạo 1 file interface .hal và Android.bp -> build ra Hidl interface (lệnh mm) ->
    out/soong/.intermediates/vender/lampt/harware/interface/led/... -> các file include sẽ nằm ở đây để sử dụng
	- Tạo generate.sh (hidl-gen) để lấy mẫu thư mục hidl
	- Chạy generate.sh tạo thư mục default -> trong đó thêm 3 file packagename_service.rc và packagename_service.xml
	- service.cpp: Để sử dung serice từ hal thì phải đăng ký với hwservicemanager để quản lý = hàm registerAsService(); 
	- Build xong service nằm ở: out/target/product/evk_8mm/vendor/ lib (32  bit) | lib64 (64 bit)  
### Hal Service
- hwservicemanager -> quản lý các service hal được tạo ra để xử lý và tìm service
- Đăng ký service -> service.cpp
- Define 1 instance của interface hal mới để đăng ký cho AOSP biết về service hal mới tạo
- Sử dung hàm registerAsService()
### Vendor interface object
- Device manifest: đăng ký về hal mới viết cho framework -> framework compatibility matrix: đánh giá, chấp nhận quản lý device manifest
    - Hal quan tâm device manifest
- Device compatibility matrix - framework manifest: tương tự -> frame manifest liên quan đến: system, product, system_ext  
- Device manifest & framework manifest có dạng như sau:
```  
<manifest version="1.0" type="device">
    <hal format="hidl">
        <name>vendor.lampt.led</name>
        <transport>hwbinder</transport>
        <version>1.0</version>
        <interface>
            <name>ILedHidl</name>
            <instance>default</instance>
        </interface>
    </hal>
</manifest>
```  
- Compatibility matrix có dạng như sau: device/nxp/ek_8mm/device_framework...  
```  
<compatibility-matrix version="1.0" type="framework">
    <hal format="hidl" optional="true">
        <name>vendor.lampt.led</name>
        <version>1.0</version>
        <interface>
            <name>ILedHidl</name>
            <instance>default</instance>
        </interface>
    </hal>
</compatibility-matrix>
```  
### Triển khai file .rc để chạy service
- service nằm trong /out/target/product/evk_8mm/vendor/bin/hw/  
```  
service vendor.lampt.led-1-0 /vendor/bin/hw/vendor.lampt.led@1.0-service
    interface vendor.lampt.led@1.0::ILedHidl default
    class hal
    user system
    group system
```  
- Để boarđ biết dịch vụ cần chạy thì khai báo trong /device/nxp/imx8mm/evk_8mm/evk_8mm.mk (device.mk)
```  
PRODUCT_PACKAGES += vendor.lampt.led@1.0-service
```  
### Khai báo để cấp quyền sepolicy  
- Thêm vào device/nxp/imx8mm/sepolicy/file_contexts
```  
/vendor/bin/hw/vendor\.lampt\.led@1\.0-service u:object_r:hal_lamptled_exec:s0
```  
- Tạo 1 file trong sepolicy : hal_lamptled.te , tạo quyền cần thiết cho service
```  
type hal_lamptled, domain;

allow hal_lamptled hal_allocator:fd use;
type hal_lamptled_exec, exec_type, file_type, vendor_file_type;
init_daemon_domain(hal_lamptled)
```  
### Debug 
- lshal -> thong tin các service đang chạy trong board
- logcat | grep -iE "LOG_TAG" -> debug
### AIDL  
AIDL đã có từ trước HIDL và dùng trong Java Framework.
- Android Framework cần giao tiếp giữa Service và App → Dùng AIDL qua binder.
- AIDL chỉ hoạt động trong Java/Kotlin + NDK, không thể dùng cho Vendor HAL.  

Android 11+: HIDL dần bị thay thế bằng AIDL cho HAL  
- AIDL được mở rộng để thay thế HIDL trong các HAL mới.
- Từ Android 11, Google khuyến khích dùng AIDL thay vì HIDL.
- HIDL: Giao tiếp với service phía trên qua jni 
- AIDL: Bỏ jni -> tường minh trong service và client giao tiếp qua binder IPC
- Đồng nhất lại kiểu giao tiếp như trên java framework vẫn sử dụng AIDL
- Kiểm soát version và update dễ quản lý hơn  

Nơi tìm AIDL file:
- hardware/interfaces
- frameworks/hardware/interfaces
- system/hardware/interfaces  

Tạo mới AIDL interfaces:
- hardware/interfaces
- hardware/device/vendor hoặc để trong vendor/

AIDL sử dụng backend NDK, ngôn ngữ c++  
Java framework sử dụng backend java, ngôn ngữ java  
- Backend Java (AIDL Java) dùng trong Android Framework, giao tiếp với App dễ dàng.
- Backend NDK (AIDL C++) dùng trong native system services, nhanh hơn và hỗ trợ C++/HAL.
- Nếu làm việc với HAL hoặc C++ System Services, nên dùng Backend NDK.
- Nếu làm việc với App hoặc Java Framework, nên dùng Backend Java.  

### Tạo một AIDL 
- vendor - lampt (thay bang tên cty làm sp) - hardware - interfaces - led (ten HAL) - aidl
- Tạo file Android.bp  
    ```  
    aidl_interface {
        name: "vendor.lampt.hardware.led",
        vendor_available: true,
        srcs: [
            "vendor/lampt/hardware/led/*.aidl"
        ],
        stability: "vintf",
        owner: "phamlam",
        backend: {
            cpp: {
                enabled: false,
            },
            java: {
                sdk_version: "module_current",
            },
        },
    }
    ```    
- vendor - lampt (thay bang tên cty làm sp) - hardware - interfaces - led (ten HAL) - aidl - vendor - lampt - hardware - led
- Tạo file ILedAidl.aidl  
    ```  
    package vendor.lampt.hardware.led;

    @VintfStability
    interface ILedAidl {
            int setLed(String value);
            String getLed();
    };
    ```  
- Tại thư mục aidl -> chạy lệnh mm để build ra các file include nằm trong out/soong/.intermediates/vender/lampt/harware/interface/led/...
    - AIDL có check các phiên bản thay đổi như nào mỗi lần build -> với lần thay đổi chạy `m vendor.lampt.hardware.led-update-api` tạo ra bản snapshot lưu bản để so sánh với bản sau -> trước khi chạy thay đổi cần chắc chắn cập nhật không vấn đề với các api đã đánh giá chạy ổn định trước
    - Để tạo ra bản giữ cố định chạy `m vendor.lampt.hardware.led-freeze-api`  
- Các bước tiếp giống với tạo HIDL nhưng AIDL không cần khai báo trong device.mk -> tự động khởi chạy khi được thiết lập quyền đầy đủ trong SELinux
- file .xml
```  
<manifest version="1.0" type="device">
    <hal format="aidl">
        <name>vendor.lampt.hardware.led</name>
        <version>1</version>
        <fqname>ILedAidl/default</fqname>
    </hal>
</manifest>
```  
- file .rc
```  
service vendor.lampt.hardware.led-service /vendor/bin/hw/vendor.lampt.hardware.led-service
    interface aidl vendor.lampt.hardware.led.ILedAidl/default
    class hal
    user system
    group system
```  
### Hal Service
- Quản lý bởi servicemanager  

Các API để đăng ký và sử dụng service:  
- register<addService>  
- getting<getService>  
- wait<waitForService> -> try liên tục để đăng ký với servicemanager đến khi đk service thành công

```  
#include<android/binder_manager.h>

//registering
binder_exception_t err = AServiceManager_addService(myService->asBinder().get(), "service-name");
//return if service is started now
myService = IFoo:fromBinder(ndk::SpAIBinder(AServiceManager_checkService("service-name")));
//is a service declared in the VINTF manifest
//VINTF services have the type in the interface instance name 
bool isDeclared = AServiceManager_isDeclared("android.hardware.light.ILights/default");
//wait until a service is available (if isDeclared of you know it's available)
myService = IFoo:fromBinder(ndk::SpAIBinder(AServiceManager_waitForService("service-name")));
```  

### Annotations
- nullable : version 7 
- utf8InCpp: 7
- VintfStability: 11 -> đánh giá trong 2 phần interface với Android.bp phía trên để match với nhau -> build sẽ check version 1 với version 2 có stable không
- UnsupportedAppUsage: 10
- Hide: 11
- Backing: 11
- NdkOnlyStableParcelable: 14
- JavaOnlyStableParcelable: 11
- JavaDerive: 12
- JavaPassthrough: 12
- FixedSize: 12
- Descriptor: 12

## SELinux
- Kiểm tra quyền của các chức năng, service  
- MAC (Mandatory Access Controls): tạo bởi OS/vendor -> tùy chỉnh labels u:oject_t:"name-label":s0
- DAC (Discreptionary Access Controls) : quyền rwx của 1 file
- Check quyền: getenforce 
    - permissive = 0 -> cảnh báo chứ không chặn
    - enforcing = 1 -> chặn 
- Cập nhật quyền: setenforce = 0/1
- Device driver: selinuxfs -> bật board lên sẽ chạy 1 lần lưu từ database vào AVC
    - Lưu trong database (chứa secuirity) -> AVC (access vector cache) lưu thông tin quyền ở cache
    - AVC cache: lưu quyền trung gian check qua cache luôn nhanh hơn <-> server check quyền 
    - server <-> abtract(lớp nằm giữa giao tiếp) <-> linux serciurity modules <- DAC
- Cách hoạt động:
    - user space -> system call
    - check errors
    - DAC checks -> check quyền rwx
    - LSM Hook -> Linux seciurity module check -> AVC, selinux serciurity 
    - Return for system call

### Finding SELinux file
- system/sepolicy
- Từ Android 8 -> /system hợp với /vendor
- system/policy/public: Define quyền cho cả system và vendor
    - thêm tính năng mới 
- system/policy/private: Cho system
- system/policy/vendor: Cho vendor 
- BOARD_SEPOLICY_DIRS: địa chỉ thư mục sử dụng sepolicy
- SYSTEM_EXT_PUBLIC_SEPOLICY_DIRS: thường sử dụng khi tích hợp app và framework
- Các macro define quyền trong selinux cho file .te: [te_macro](https://android.googlesource.com/platform/system/sepolicy/+/refs/heads/master/public/te_macros)  
    - Các macro hay dùng: binder_Call, init_daemon_domain, ...  
### Tool debug cho selinux  
- pull file database từ board về máy: `adb pull /sys/fs/selinux/policy`  
- audit2allow: In ra dmesg thông báo thiếu quyền gì cho 1 service  
`adb logcat -b events -d | grep vendor.lampt.led | audit2allow -p policy` tìm quyền thiếu  
- chcon: thay đổi quyền 
- restorecon: trả về quyền default  
### Writing sepolicy
- Các _contexts: gắn nhãn lable
    - file_contexts: label to file
    - genfs_contexts: label của filesystem -> usb, ... -> cấp quyền cho file system mới
    - property_contexts: kiểu string, `getprop` để check property lable, `setprop "name-prop" "giá trị"` thay đổi giá trị ở terminal,   
    - hwservice_contexts: service hidl
    - service_contexts: service aidl  
- File .te: các quyền  
- Các macro và cách viết file .te
<p align = "center">
<img src = "https://github.com/PhamLam21/Imx8m_Evk8mm_AOSP/blob/main/SELinux.jpg" width = "800" height = "600">  

- allow: cho phép quyền
- dontaudit: ẩn các thông tin muốn ẩn
- neverallow: cấm quyền 
- Binder Sepolicy: 
<p align = "center">
<img src = "https://github.com/PhamLam21/Imx8m_Evk8mm_AOSP/blob/main/BinderSepolicy.jpg" width = "800" height = "600">  

- Cú pháp file contexts: [file contexts](https://android.googlesource.com/platform/system/sepolicy/+/refs/heads/main/private/file_contexts)
- Khai báo label service: hidl -> hwservice_contexts , aidl -> service_contexts
- Khai báo type cho service: [Type](https://android.googlesource.com/platform/system/sepolicy/+/master/public/attributes)  

### Property_contexts
- Sử dụng để thay đổi giá trị của biến trong code từ terminal   
- Có thể lấy giá trị trong code bằng hàm `android::base::GetProperty(key, default_value)`  
```  
constexpr char ledValueProperty[] = "vendor.led.value"
#define LED_DEFAULT 1

std::string ledValue;
ledValue = android::base::GetProperty(ledValueProperty, std::to_string(LED_DEFAULT));
```  
- Để khai báo 1 key như "vendor.led.value" trong board:
    - Khai báo label trong property_contexts `vendor.led.value`
    - Cấp quyền trong property.te: `vendor_internal_inti()`
    - Khai báo setprop trong init.rc -> file giống shell
    - Cấp quyền trong board_init.te cho câu lệnh ở init.rc
    - Cấp quyền cho label để sử dụng property: `set_prop(hal_lamptled_default, vendor_led_prop)`


