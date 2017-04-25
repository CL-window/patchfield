package com.cl.slack.opensl_es;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

import com.cl.slack.opensl_es.audio_demo.AudioDemoActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void audioDemo(View view) {
        startNewIntent(AudioDemoActivity.class);
    }

    private void startNewIntent(Class zlass){
        startActivity(new Intent(this, zlass));
    }

}
