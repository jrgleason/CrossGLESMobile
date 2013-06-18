LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := box2D-prebuilt
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libbox2D.so
LOCAL_EXPORT_C_INCLUDES := ./
include $(PREBUILT_SHARED_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE    := framework
# LOCAL_SRC_FILES := \
#        $(subst $(LOCAL_PATH)/,, \
#        $(wildcard $(LOCAL_PATH)/framework/*.cpp) \
#        $(wildcard $(LOCAL_PATH)/framework/*.c))
# LOCAL_SHARED_LIBRARIES := box2D-prebuilt
# LOCAL_LDLIBS := -lm -lGLESv2 -llog
# include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := testand 

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
        $(wildcard $(LOCAL_PATH)/src/*.cpp) \
	$(wildcard $(LOCAL_PATH)/src/*.c))
# LOCAL_SHARED_LIBRARIES := framework
LOCAL_SHARED_LIBRARIES := box2D-prebuilt
LOCAL_LDLIBS := -lm -lGLESv2 -llog
include $(BUILD_SHARED_LIBRARY)
