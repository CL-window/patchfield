/*
 *  COPYRIGHT NOTICE
 *  Copyright (C) 2016, Jhuster <lujun.hust@gmail.com>
 *  https://github.com/Jhuster/AudioDemo
 *
 *  @license under the Apache License, Version 2.0
 *
 *  @file    native_audio.c
 *
 *  @author  Jhuster
 *  @date    2016/04/17
 */
#include <stdio.h>
#include <jni.h>
#include <android/log.h>
#include "opensl_io/opensl_io.h"

#define LOG(...) __android_log_print(ANDROID_LOG_DEBUG,"AudioDemo-JNI",__VA_ARGS__)

#define SAMPLERATE 44100
#define CHANNELS 1
#define PERIOD_TIME 20 //ms
#define FRAME_SIZE SAMPLERATE*PERIOD_TIME/1000
#define BUFFER_SIZE FRAME_SIZE*CHANNELS
#define TEST_CAPTURE_FILE_PATH "/sdcard/audio.pcm"

static volatile int g_loop_exit = 0;

static OPENSL_STREAM* openslStream;

/*
 * Class:     com_jhuster_audiodemo_tester_NativeAudioTester
 * Method:    nativeStartCapture
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_cl_slack_opensl_1es_audio_1demo_tester_NativeAudioTester_nativeStartCapture(JNIEnv *env, jobject thiz)
{
    FILE * fp = fopen(TEST_CAPTURE_FILE_PATH, "wb");
    if( fp == NULL ) {
        LOG("cannot open file (%s)\n", TEST_CAPTURE_FILE_PATH);
        return -1;
    }
    android_CloseAudioDevice(openslStream);
    openslStream  = android_OpenAudioDevice(SAMPLERATE, CHANNELS, CHANNELS, FRAME_SIZE);
    if (openslStream == NULL) {
        fclose(fp);
        LOG("failed to open audio device ! \n");
        return JNI_FALSE;
    }

    int samples;
    short buffer[BUFFER_SIZE];
    g_loop_exit = 0;
    while (!g_loop_exit) {
        samples = android_AudioIn(openslStream, buffer, BUFFER_SIZE);
        if (samples < 0) {
            LOG("android_AudioIn failed !\n");
            break;
        }
        if (fwrite((unsigned char *)buffer, samples*sizeof(short), 1, fp) != 1) {
            LOG("failed to save captured data !\n ");
            break;
        }
        LOG("capture %d samples !\n", samples);
    }

    android_CloseAudioDevice(openslStream);
    fclose(fp);

    LOG("nativeStartCapture completed !");

    return JNI_TRUE;
}

/*
 * Class:     com_jhuster_audiodemo_tester_NativeAudioTester
 * Method:    nativeStopCapture
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_cl_slack_opensl_1es_audio_1demo_tester_NativeAudioTester_nativeStopCapture(JNIEnv *env, jobject thiz)
{
    g_loop_exit = 1;
    return JNI_TRUE;
}

/*
 * Class:     com_jhuster_audiodemo_tester_NativeAudioTester
 * Method:    nativeStartPlayback
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_cl_slack_opensl_1es_audio_1demo_tester_NativeAudioTester_nativeStartPlayback(JNIEnv *env, jobject thiz)
{
    FILE * fp = fopen(TEST_CAPTURE_FILE_PATH, "rb");
    if( fp == NULL ) {
        LOG("cannot open file (%s) !\n",TEST_CAPTURE_FILE_PATH);
        return -1;
    }
    android_CloseAudioDevice(openslStream);
    openslStream = android_OpenAudioDevice(SAMPLERATE, CHANNELS, CHANNELS, FRAME_SIZE);
    if (openslStream == NULL) {
        fclose(fp);
        LOG("failed to open audio device ! \n");
        return JNI_FALSE;
    }

    int samples;
    short buffer[BUFFER_SIZE];
    g_loop_exit = 0;
    while (!g_loop_exit && !feof(fp)) {
        if (fread((unsigned char *)buffer, BUFFER_SIZE*2, 1, fp) != 1) {
            LOG("failed to read data \n ");
            break;
        }

        samples = android_AudioOut(openslStream, buffer, BUFFER_SIZE);
        if (samples < 0) {
            LOG("android_AudioOut failed !\n");
        }
        LOG("playback %d samples !\n", samples);
    }

    android_CloseAudioDevice(openslStream);
    fclose(fp);

    LOG("nativeStartPlayback completed !");

    return JNI_TRUE;
}

/*
 * Class:     com_jhuster_audiodemo_tester_NativeAudioTester
 * Method:    nativeStopPlayback
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_cl_slack_opensl_1es_audio_1demo_tester_NativeAudioTester_nativeStopPlayback(JNIEnv *env, jobject thiz)
{
    g_loop_exit = 1;
    return JNI_TRUE;
}

JNIEXPORT jdouble JNICALL
Java_com_cl_slack_opensl_1es_audio_1demo_tester_NativeAudioTester_nativeGetTimeStamp(JNIEnv *env,
                                                                                     jobject instance) {
    if(openslStream == NULL){
        LOG("openslStream null !\n");
        return 0;
    }
    return android_GetTimestamp(openslStream);

}