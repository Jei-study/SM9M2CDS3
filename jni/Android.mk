LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := JNIDriver
LOCAL_SRC_FILES := JNIDriver.c

include $(BUILD_SHARED_LIBRARY)
