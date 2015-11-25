package com.cweethome.esiea.cweethome;

// Android library
// -------------------------------------------
import android.util.Log;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.TextView;

// Library of HTTP request
// ---------------------------------------------
import com.squareup.okhttp.Callback;
import com.squareup.okhttp.MediaType;
import com.squareup.okhttp.OkHttpClient;
import com.squareup.okhttp.Request;
import com.squareup.okhttp.RequestBody;
import com.squareup.okhttp.Response;

// Java library
// -------------------------------------------
import java.io.*;



public class mainCweetHome extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.home);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        Button btn = (Button) findViewById(R.id.buttonConnexiontoIP);
        Button btn2 = (Button) findViewById(R.id.bubul);

        btn2.setOnClickListener(new View.OnClickListener() {

            OkHttpClient client = new OkHttpClient();

            @Override
            public void onClick(View view) {

                final TextView txt = (TextView) findViewById(R.id.textStateHttpReq);

                // Creation of JSON object
                // ------------------------------------------------
                String messageHttp = "{\"LIG\":1:0,2:1,3:1}";
                //String messageHttp = "bonjour";
                MediaType JSON = MediaType.parse("application/json; charset=utf-8");
                RequestBody JSONbody = RequestBody.create(JSON, messageHttp);
                txt.setText("Bouh");

                // Do this fucking request
                // ---------------------------------------------
                Request request = new Request.Builder()
                        .url("http://192.168.1.102/")
                        .post(JSONbody)
                        .build();

                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Request request, IOException e) {
                        Log.w("OK", "NOK : " + e);
                    }

                    @Override
                    public void onResponse(Response response) throws IOException {
                        System.out.println(response.toString());
                        Log.d("OK", response.toString());
                        Log.d("OK", "OK");
                    }
                });
            }
        });

        btn.setOnClickListener(new View.OnClickListener() {

            OkHttpClient client = new OkHttpClient();

            @Override
            public void onClick(View view) {

                final TextView txt = (TextView) findViewById(R.id.textStateHttpReq);

                // Creation of JSON object
                // ------------------------------------------------
                String messageHttp = "{\"LIG\":1:1,2:0,3:0}";
                //String messageHttp = "bonjour";
                MediaType JSON = MediaType.parse("application/json; charset=utf-8");
                RequestBody JSONbody = RequestBody.create(JSON, messageHttp);
                txt.setText("Connect");

                // Do this fucking request
                // ---------------------------------------------
                Request request = new Request.Builder()
                        .url("http://192.168.1.102/")
                        .post(JSONbody)
                        .build();

                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Request request, IOException e) {
                        Log.w("OK", "NOK 2: " + e);
                    }

                    @Override
                    public void onResponse(Response response) throws IOException {
                        System.out.println(response.toString());
                        Log.d("OK", response.toString());
                        Log.d("OK", "OK 2");
                    }
                });
            }
        });
    }

}

        /* Button btn = (Button) findViewById(R.id.buttonConnexiontoIP);
        btn.setOnClickListener(new View.OnClickListener() {

            // create the HTTP Client & text of state of http request
            // -------------------------------------------------
            OkHttpClient client = new OkHttpClient();


            @Override
            public void onClick(View view) {


               // MediaType JSON = MediaType.parse("application/json; chart-utf-8");
               // RequestBody body = RequestBody.create(JSON, "OK");

                // Send HTTP Request
                // -----------------------------------------------------------------
               Request requestHTTP = new Request.Builder()
                       .url("http://192.168.1.102/")
                       .build();

               try {

                   Response responseHTTP = client.newCall(requestHTTP).execute();

                   txt.setText("Connexion OKI");
                   Snackbar.make(view, "OK", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();

               } catch (IOException exception) {
                   txt.setText("Connexion NOKI : ");
               }

            }

        });*/


        /*FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });*/


