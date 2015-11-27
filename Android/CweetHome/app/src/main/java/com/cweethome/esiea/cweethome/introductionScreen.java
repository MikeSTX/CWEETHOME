package com.cweethome.esiea.cweethome;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.common.api.GoogleApiClient;

import java.io.IOException;
import java.util.*;
import java.util.logging.Handler;
import java.util.logging.LogRecord;

// Library of HTTP request
// ---------------------------------------------
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.MediaType;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.RequestBody;
import com.squareup.okhttp.Response;

/**
 * Created by a190239 on 25/11/2015.
 */
public class introductionScreen extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Link with the activity
        setContentView(R.layout.introduction_screen);

        // Delay before going to the home activity
        // ------------------------------------------------
        Timer timer = new Timer();
        TimerTask task = new TimerTask() {
            @Override
            public void run() {
                finish();
                Intent myIntent = new Intent(introductionScreen.this, home.class);
                startActivity(myIntent);
            }
        };

        timer.schedule(task, 1000);

    }

}
