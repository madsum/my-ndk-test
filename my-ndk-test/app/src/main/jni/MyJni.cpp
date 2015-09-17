#include "MyJni.h"
#include "MyJniLog.h"
#include <stdlib.h>

void get_string(JNIEnv *env, jobject obj) {
    jclass myJni = env->GetObjectClass(obj);
    if (NULL == myJni) {
        LOGE("In C: myJni class is NULL");
        return;
    }

    jfieldID fidMyStr = env->GetFieldID(myJni, "myStr", "Ljava/lang/String;");
    if (NULL == fidMyStr) {
        LOGE("In C: findMyStr is NULL");
        return;
    }

    jstring myStr = (jstring) env->GetObjectField(obj, fidMyStr);
    if (NULL == myStr) {
        LOGE("In C: myStr is NULL");
        return;
    }

    const char *cChar = env->GetStringUTFChars(myStr, NULL);
    if (NULL == cChar) {
        LOGE("In C: cChar class is NULL");
        return;
    }
    LOGI("In c cChar: %s", cChar);
    env->ReleaseStringUTFChars(myStr, cChar);
    myStr = env->NewStringUTF("set myStr val in C");
    (env)->SetObjectField(obj, fidMyStr, myStr);
}

void javaCallBack(JNIEnv *env, jobject obj)
{
    jclass thisClass = env->GetObjectClass(obj);
    if(NULL == thisClass )
    {
        LOGE("thisClass is NULL");
        return;
    }

    jmethodID midCallMe = (env)->GetMethodID(thisClass,
                                                  "callMe", "(Ljava/lang/String;)I");
    if (NULL == midCallMe) return;
    LOGI("In C, call back Java's called(String)\n");
    jstring message = (env)->NewStringUTF("Hello from C");
    env->CallIntMethod(obj, midCallMe, message);
}

void get_set_char_array(JNIEnv *env, jobject obj)
{
    jclass myJni = env->GetObjectClass(obj);
    if (NULL == myJni) {
        LOGE("In C: myJni class is NULL");
        return;
    }

    jfieldID fidMyCharArr = env->GetFieldID(myJni, "myCharArr", "[C");
    if (NULL == fidMyCharArr) {
        LOGE("In C: fidMyCharArr is NULL");
        return;
    }

    jobject jobj = env->GetObjectField(obj, fidMyCharArr);
    if (NULL == jobj) {
        LOGE("In C: jobj is NULL");
        return;
    }

    // Cast it to a jdoublearray
    jcharArray * arr = reinterpret_cast<jcharArray *>(&jobj);
    if (NULL == arr) {
        LOGE("In C: arr is NULL");
        return;
    }

    jchar * ch  = env->GetCharArrayElements(*arr, NULL);
    if (NULL == ch) {
        LOGE("In C: ch is NULL");
        return;
    }
    LOGI("ch: %c",ch[2]);
    jsize length = env->GetArrayLength(*arr);
//    jcharArray buf[3] = {'x', 'y', 'z'};
  //  jcharArray
  //  env->SetCharArrayRegion(*arr, 0, lenght, )
}

void callStaticMethod(JNIEnv *env, jobject obj)
{
    jclass  thisClass = env->GetObjectClass(obj);
    jmethodID midCallBackStatic = (env)->GetStaticMethodID(thisClass,"myStatic", "(I)V");
    if (NULL == midCallBackStatic) {
        LOGE("midCallBackStatic is NULL");
        return;
    }
    (env)->CallStaticObjectMethod(thisClass, midCallBackStatic, 10);
}

JNIEXPORT jstring JNICALL Java_com_my_ndk_MyJni_setGetString
        (JNIEnv *env, jobject obj, jstring str) {
    const char *inCStr = (env)->GetStringUTFChars(str, NULL);
    if (NULL == inCStr) {
        LOGE("In C: inCStr is NULL");
        return NULL;
    }
    LOGI("In C, the received string is: %s\n", inCStr);
    (env)->ReleaseStringUTFChars(str, inCStr);

    get_string(env, obj);

    javaCallBack(env, obj);

    get_set_char_array(env, obj);

    callStaticMethod(env, obj);

    const char *outCStr = "Return str";
    return env->NewStringUTF(outCStr);
}

JNIEXPORT void JNICALL Java_com_my_ndk_MyJni_getMeThoseStrings
        (JNIEnv * env, jobject obj, jcharArray resultBuffer1, jcharArray resultBuffer2)
{
    // Get the size of our result buffer sent from Java so we know how much room we have to use.
    int len = env->GetArrayLength(resultBuffer1);

// Allocate a character buffer for the C method we want to call to store the result in.
    char *charBuffer1 = (char *)calloc(sizeof(char), len);

// Call the C method.  Note in this example I haven't shown the code for allocating charBuffer2.
//    getMeThoseStrings(charBuffer1, charBuffer2);

// Update the length to match the actual string we're going to be returning.
    len = strlen(charBuffer1) + 1;

// Copy the result out of the C character buffer into a jchar buffer.  This is where we are converting chars to jchars.
    jchar *jcharBuffer1 = (jchar *)calloc(sizeof(jchar), len);

    for (int i = 0; i < len; i ++) {
        jcharBuffer1[i] = (jchar)charBuffer1[i];
    }

// Free the C character buffer.
    free(charBuffer1);

// Copy the result into the jcharArray.
    env->SetCharArrayRegion(resultBuffer1, 0, len, jcharBuffer1);

// Free the jchar buffer
    free(jcharBuffer1);
}


JNIEXPORT void JNICALL Java_com_my_ndk_MyJni_myStatic
        (JNIEnv *evn, jclass cls, jint a_int)
{

}

