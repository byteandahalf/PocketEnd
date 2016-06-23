LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := com.byteandahalf.enddimension # should match the name in the AndroidManifest.xml

define findfiles
	$(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call findfiles, $(e)))
endef
ALLFILES = $(call findfiles, $(LOCAL_PATH))
FILE_LIST := $(filter %.cpp, $(ALLFILES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_LDLIBS    := -L$(LOCAL_PATH) -llog -ldl -lminecraftpe -lmcpelauncher_tinysubstrate -lGLESv1_CM

# ignore undefined symbols.
# workaround for method not found errors.
TARGET_NO_UNDEFINED_LDFLAGS :=

include $(BUILD_SHARED_LIBRARY)
