#include "ExampleAndroidJni.h"
#include "MyJniLog.h"
#include <stdlib.h>

#define AUDIO_TRACK_BUFFER_SIZE (48)

JNIEXPORT jobjectArray JNICALL Java_com_my_ndk_ExampleAndroidJni_nativeGetAudioTracks
        (JNIEnv * env, jobject obj, jstring filePath) {

  // Convert filePath from jstring to null terminated UTF8 string
  const char *path = (*env)->GetStringUTFChars(env, filePath, 0);
  if (!path ) {
    LOGE ("ERROR : pathToFile Conversion error in nativeGetAudioTracks");
    (*env)->ReleaseStringUTFChars(env, filePath, path);
    return NULL;
  }

  // Each track is 3 chars + a null terminator.
  // Allows for up to 12 languages.
  char langCodeHolder[AUDIO_TRACK_BUFFER_SIZE] = {0};
  int numTracks = 0;
  int fd = 0;//open(path, O_RDONLY);
  if (fd > 0) {
    // get audio track magic through custom FUSE IOCTL handler
  //  numTracks = ioctl(fd, GET_AUDIO_TRACKS, &(langCodeHolder[0]));
   // close(fd);
  } else {
    LOGE ("ERROR: open(%s) failed in nativeGetAudioTracks", path);
    (*env)->ReleaseStringUTFChars(env, filePath, path);
   // close(fd);
    return NULL;
  }

  if (numTracks < 0) {
    LOGE("ERROR: Invalid value returned from GET_AUDIO_TRACKS");
    (*env)->ReleaseStringUTFChars(env, filePath, path);
    return NULL;
  }

  if (numTracks == 0) {
    LOGE("ERROR: No audio tracks returned");
    (*env)->ReleaseStringUTFChars(env, filePath, path);
    return NULL;
  }

  // Instantiate array to hold language codes.
  jobjectArray langs;
  const jint langArraySize = numTracks;
  jclass stringObject = (*env)->FindClass(env, "java/lang/String");
  if (stringObject == NULL) {
    (*env)->ReleaseStringUTFChars(env, filePath, path);
    return NULL;
  }
  langs = (*env)->NewObjectArray(env, langArraySize, stringObject, (*env)->NewStringUTF(env, NULL));

  // Extract each 3-letter language code and stuff them into the array.
  jstring langCode;
  char* temp = &(langCodeHolder[0]);
  jint i;
  for (i = 0; i < langArraySize; i++) {
    langCode = temp;
    (*env)->SetObjectArrayElement(env, langs, i, (*env)->NewStringUTF(env, langCode));
    temp += 4;
  }

  (*env)->ReleaseStringUTFChars(env, filePath, path);
  return langs;
}