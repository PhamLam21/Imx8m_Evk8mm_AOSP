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
## HAL
### HIDL  
- HAL -> Service trao đổi qua binder IPC -> 1 service hỏng không ảnh hưởng đến các serice khác trong HAL
- Conventional HAL : implement thư viện .so -> lỗi thì lỗi toàn bộ
- Binderize -> build ra file binary không còn sharelib
<p align = "center">
<img src = "https://img-blog.csdnimg.cn/20200805204512893.jpg?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3lpcmFuZmVuZw==,size_16,color_FFFFFF,t_70" width = "400" height = "200">  

- version: 
    - 8.x về trước sử dụng legacy HAL
	- 8.x đến 10.x sử dụng HIDL
	- 11.x về sau sử dụng AIDL  
- Tạo mới HIDL    
    - Tạo các file cần thiết
	- vendor - lampt (thay bang tên cty làm sp) - hardware - interfaces - led (ten HAL) - 1.0 (phien ban)
	- Tạo 1 file Android.bp ở folder interface -> de khai bao duong dan thu muc moi tao
	- Tạo 1 file interface .hal và Android.bp -> build ra Hidl interface (lệnh mm)
	- Tạo generate.sh (hidl-gen) để lấy mẫu thư mục hidl
	- Chạy generate.sh tạo thư mục default -> trong đó thêm 3 file packagename_service.rc và packagename_service.xml
	- service.cpp: Để sử dung serice từ hal thì phải đăng ký với hwservicemanager để quản lý = hàm registerAsService(); 
	- Build xong service nằm ở: out/target/product/evk_8mm/vendor/ lib (32  bit) | lib64 (64 bit)  
### Hal Server  
- hwservicemanager -> quản lý các service hal được tạo ra để xử lý và tìm service
- Đăng ký service -> service.cpp
- Define 1 instance của interface hal mới để đăng ký cho AOSP biết về service hal mới tạo
- Sử dung hàm registerAsService()
### Vendor interface object
- Device manifest: đăng ký về hal mới viết cho framework -> framework compatibility matrix: đánh giá, chấp nhận quản lý device manifest
    - Hal quan tâm device manifest
- Device compatibility matrix - framework manifest: tương tự -> frame manifest liên quan đến: system, product, system_ext


