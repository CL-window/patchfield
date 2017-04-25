/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_noisepages_nettoyeur_openslstreamsample_Lowpass */

#ifndef _Included_com_noisepages_nettoyeur_openslstreamsample_Lowpass
#define _Included_com_noisepages_nettoyeur_openslstreamsample_Lowpass
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    open
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_open
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_close
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    start
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_start
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    stop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_stop
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    setAlpha
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_setAlpha
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     com_noisepages_nettoyeur_openslstreamsample_Lowpass
 * Method:    isRunning
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_cl_slack_opensl_1stream_1sample_Lowpass_isRunning
  (JNIEnv *, jclass, jlong);


#ifdef __cplusplus
}
#endif
#endif
