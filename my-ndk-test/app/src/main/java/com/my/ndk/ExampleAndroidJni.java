package com.my.ndk;

import android.util.Log;

public class ExampleAndroidJni {

    private static ExampleAndroidJni sInstance;
    private static final String TAG = "ExampleAndroidJni";

    public static String[] getAudioTracks(final String filePath) {
        if (sInstance == null) {
            sInstance = new ExampleAndroidJni();
        }

        if (filePath == null) {
            Log.e(TAG, "file path is null");
            return null;
        }

        final String[] auduioTracks = sInstance.nativeGetAudioTracks(filePath);
        if (auduioTracks == null || auduioTracks.length == 0) {
            Log.i(TAG, "No audio tracks returned for : " + filePath);
        }

        return auduioTracks;
    }

    native String[] nativeGetAudioTracks(String filePath);

    static {
        System.loadLibrary("ExampleNativeJni");
    }
}