LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/CGameManager.cpp \
../../Classes/CGameScene.cpp \
../../Classes/CHomeScene.cpp \
../../Classes/CTitleScene.cpp \
../../Classes/CPauseScene.cpp \
../../Classes/CGameResultScene.cpp \
../../Classes/CPauseLayer.cpp \
../../Classes/CSceneManager.cpp \
../../Classes/CPlayerCharacterModel.cpp \
../../Classes/CPlayerModel.cpp \
../../Classes/CMainTimerNode.cpp \
../../Classes/CControllerLayer.cpp \
../../Classes/CPlayerCharacterNode.cpp \
../../Classes/CTimer.cpp \
../../Classes/CUtil.cpp \
../../Classes/CAnimationHelper.cpp \
../../Classes/CRandom.cpp \
../../Classes/CChikenNode.cpp \
../../Classes/CLabelAnimate.cpp \
../../Classes/CNextTargetPrintNode.cpp \
../../Classes/CBulletNode.cpp \
../../Classes/CAvatarUnitNode.cpp \
../../Classes/CCardNode.cpp \
../../Classes/CUnitNode.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
