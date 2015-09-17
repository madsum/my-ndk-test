package com.my.ndk;

import android.app.Activity;
import android.os.Bundle;

import com.example.plasma.R;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        MyJni.test();
    }
}
