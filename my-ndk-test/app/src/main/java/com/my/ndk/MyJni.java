package com.my.ndk;

import android.util.Log;

/**
 * Created by masum on 17/09/15.
 */
public class MyJni {

    static {
        System.loadLibrary("my-ndk-test");
    }

    private String myStr = "myStr val";
    private Double myDouble = 100.50;
    private char[] myCharArr = {'a','b','c'};
    public native String setGetString(String str);

    public native void getMeThoseStrings(char[] resultBuffer1, char[] resultBuffer2);

    public int callMe(String str){
        Log.i("tag", "got call: "+str);
        return 1;
    }
    public static void myStatic(int arg){
        Log.i("tag", "arg: "+arg);
    };

    public void accStaticVal(){
        Log.i("tag", "myStr: " + myStr);
        Log.i("tag","myStr: "+myDouble);
        Log.i("tag","myCharArr[0]: "+myCharArr[0]+" myCharArr[1] "+myCharArr[1]+" myCharArr[2] "+myCharArr[2]);
    }
    public  void printStr(){
        Log.i("tag", "now myStr: "+myStr);
    }
    public static void test(){
        int x = 10;
        MyJni jni = new MyJni();
        String str = jni.setGetString("arg str");
        Log.i("tag", "str: "+str);
        jni.printStr();
        jni. accStaticVal();
       // jni.myStatic(x);
        //jni.accStaticVal();
    }

}
