export LAMPT_PACKAGE=vendor.lampt.led@1.0
export LAMPT_LOC=default/
export HIDL_INF=vendor.lampt:/home/phamlam21/working_space/AOSP/android_build/vendor/lampt/hardware/interfaces
export HIDL_LIB=android.hidl:/home/phamlam21/working_space/AOSP/android_build/system/libhidl/transport

hidl-gen -o $LAMPT_LOC -Lc++-impl \
    -r$HIDL_INF -r$HIDL_LIB $LAMPT_PACKAGE

hidl-gen -o $LAMPT_LOC -Landroidbp-impl \
    -r$HIDL_INF -r$HIDL_LIB $LAMPT_PACKAGE
