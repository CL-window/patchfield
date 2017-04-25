package com.cl.slack.opensl_es.audio_demo.tester;

import android.os.Handler;
import android.os.SystemClock;
import android.util.Log;

public class NativeAudioTester extends Tester {

    private boolean mIsTestCapture = true;
    private boolean mIsStop = false;
    private Handler mHandler = new Handler();

    public NativeAudioTester(boolean isTestCapture) {
        mIsTestCapture = isTestCapture;
    }

    @Override
    public boolean startTesting() {
        new Thread(new Runnable() {
            @Override
            public void run() {
                if (mIsTestCapture) {
                    nativeStartCapture();
                } else {
                    nativeStartPlayback();
                }

            }
        }).start();
        mIsStop = false;
        startTimeStamp();
        return false;
    }

    private void startTimeStamp() {
        mHandler .post(new Runnable() {
            @Override
            public void run() {
                Log.i("slack","time: " + nativeGetTimeStamp());
                if(mIsStop){
                    mHandler.removeCallbacks(this);
                    return;
                }
                mHandler.postDelayed(this,200);
            }
        });
    }

    @Override
    public boolean stopTesting() {
        mIsStop = true;
        if (mIsTestCapture) {
            nativeStopCapture();
        } else {
            nativeStopPlayback();
        }
        return false;
    }

    private native boolean nativeStartCapture();

    private native boolean nativeStopCapture();

    private native boolean nativeStartPlayback();

    private native boolean nativeStopPlayback();

    private native double nativeGetTimeStamp();

    static {
        System.loadLibrary("native_audio");
    }
}
