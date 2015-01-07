LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/CGameScene.cpp \
../../Classes/CUtil.cpp \
../../Classes/CAnimationHelper.cpp \
../../Classes/CPlayerNode.cpp \
../../Classes/CGameManager.cpp \
../../Classes/CRandom.cpp \
../../Classes/CTimer.cpp \
../../Classes/CMainTimerNode.cpp \
../../Classes/CPauseLayer.cpp \
../../Classes/CChikenSprite.cpp \
../../Classes/CTitleScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
