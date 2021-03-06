/*
 * Copyright 2014 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define GLM_FORCE_RADIANS

#include <jni.h>
#include <tango-augmented-reality/augmented_reality_app.h>

static tango_augmented_reality::AugmentedRealityApp app;

#ifdef __cplusplus
extern "C" {
#endif
jint JNI_OnLoad(JavaVM* vm, void*) {
  // We need to store a reference to the Java VM so that we can call into the
  // Java layer to trigger rendering.
  app.SetJavaVM(vm);
  return JNI_VERSION_1_6;
}

JNIEXPORT jint JNICALL
Java_de_stetro_master_arcv_TangoJNINative_initialize(
    JNIEnv* env, jobject, jobject activity) {
  return app.TangoInitialize(env, activity);
}

JNIEXPORT jint JNICALL
Java_de_stetro_master_arcv_TangoJNINative_setupConfig(
    JNIEnv*, jobject) {
  return app.TangoSetupConfig();
}

JNIEXPORT jint JNICALL
Java_de_stetro_master_arcv_TangoJNINative_connect(
    JNIEnv*, jobject) {
  return app.TangoConnect();
}

JNIEXPORT jint JNICALL
Java_de_stetro_master_arcv_TangoJNINative_connectCallbacks(
    JNIEnv*, jobject) {
  int ret = app.TangoConnectCallbacks();
  return ret;
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_disconnect(
    JNIEnv*, jobject) {
  app.TangoDisconnect();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_destroyActivity(
    JNIEnv*, jobject) {
  app.ActivityDestroyed();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_resetMotionTracking(
    JNIEnv*, jobject) {
  app.TangoResetMotionTracking();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_pauseMotionTracking(
    JNIEnv*, jobject) {
  app.TangoPauseMotionTracking();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_initGlContent(
    JNIEnv*, jobject) {
  app.InitializeGLContent();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_setupGraphic(
    JNIEnv*, jobject, jint width, jint height) {
  app.SetViewPort(width, height);
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_render(
    JNIEnv*, jobject) {
  app.Render();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_deleteResources(
    JNIEnv*, jobject) {
  app.DeleteResources();
}

JNIEXPORT jstring JNICALL
Java_de_stetro_master_arcv_TangoJNINative_getPoseString(
    JNIEnv* env, jobject) {
  return (env)->NewStringUTF(app.GetPoseString().c_str());
}

JNIEXPORT jstring JNICALL
Java_de_stetro_master_arcv_TangoJNINative_getDepthString(
        JNIEnv* env, jobject) {
    return (env)->NewStringUTF(app.GetDepthString().c_str());
}

JNIEXPORT jstring JNICALL
Java_de_stetro_master_arcv_TangoJNINative_getEventString(
    JNIEnv* env, jobject) {
  return (env)->NewStringUTF(app.GetEventString().c_str());
}

JNIEXPORT jstring JNICALL
Java_de_stetro_master_arcv_TangoJNINative_getVersionNumber(
    JNIEnv* env, jobject) {
  return (env)->NewStringUTF(app.GetVersionString().c_str());
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_setCamera(
    JNIEnv*, jobject, int camera_index) {
  using namespace tango_gl;
  GestureCamera::CameraType cam_type =
      static_cast<GestureCamera::CameraType>(camera_index);
  app.SetCameraType(cam_type);
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_onDepthTouchEvent(
        JNIEnv*, jobject, int x, int y) {
    app.OnDepthTouchEvent(x,y);
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_toggleVisible(
        JNIEnv*, jobject) {
    app.toggleVisible();
}

JNIEXPORT void JNICALL
Java_de_stetro_master_arcv_TangoJNINative_onTouchEvent(
    JNIEnv*, jobject, int touch_count, int event, float x0, float y0, float x1,
    float y1) {
  using namespace tango_gl;
  GestureCamera::TouchEvent touch_event =
      static_cast<GestureCamera::TouchEvent>(event);
  app.OnTouchEvent(touch_count, touch_event, x0, y0, x1, y1);
}
#ifdef __cplusplus
}
#endif
