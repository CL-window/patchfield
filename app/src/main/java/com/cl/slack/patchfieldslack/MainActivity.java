package com.cl.slack.patchfieldslack;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.cl.slack.patchfieldslack.control.ControlActivity;
import com.cl.slack.patchfieldslack.lowpass.LowpassActivity;
import com.cl.slack.patchfieldslack.pcm.PcmActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void controller(View view) {
        startNewIntent(ControlActivity.class);
    }

    private void startNewIntent(Class zlass){
        startActivity(new Intent(this, zlass));
    }

    public void pcm(View view) {
        startNewIntent(PcmActivity.class);
    }

    public void lowpass(View view) {
        startNewIntent(LowpassActivity.class);
    }
}
