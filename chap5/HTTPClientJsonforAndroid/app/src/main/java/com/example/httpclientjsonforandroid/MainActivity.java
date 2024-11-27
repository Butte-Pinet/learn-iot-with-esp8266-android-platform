package com.example.httpclientjsonforandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {
    String strJson, ldrTextView, ledTextView;
    private static Button buttonGet;
    private static TextView jsonLdrTextView, jsonLedTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        jsonLdrTextView = (TextView) findViewById(R.id.jsonTextView);
        jsonLedTextView = (TextView) findViewById(R.id.jsonLedTextView);

        buttonGet = (Button) findViewById(R.id.buttonGet);
        buttonGet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new HttpGetReq().execute(); 
            }
        });
    }
    public class HttpGetReq extends AsyncTask<Void, Void, String> {
        private static final String TAG_Response = "HTTP Response ->";
        private static final String TAG_Header = "HTTP Request ->";
        @Override
        protected String doInBackground(Void... voids) {

            HttpURLConnection httpURLConnection = null;
            StringBuilder strResult = new StringBuilder();
            try {
                URL url = new URL("https://thingspeak.com/channels/2038363/feeds/last.json?key=your_api_key&results=1");
                httpURLConnection = (HttpURLConnection) url.openConnection();
                InputStream inputStream = httpURLConnection.getInputStream();
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

                int responseCode = httpURLConnection.getResponseCode();
                String responseMessage = httpURLConnection.getResponseMessage();
                Log.d(TAG_Header, "HTTP/1.x " + responseCode + " " + responseMessage);

                String line;
                while ((line = bufferedReader.readLine()) != null) {
                    strResult.append(line);
                    Log.d(TAG_Response, line);
                }
                //Log.d(TAG_HTML, strResult.toString());
                strJson = strResult.toString();
                try {
                    JSONObject jsonObject = new JSONObject(strJson);
                    Log.d("HTTP Request Response", "JSON string parsed");

                    ldrTextView = jsonObject.getString("field1");
                    jsonLdrTextView.setText(ldrTextView);
                    ledTextView = jsonObject.getString("field2");
                    jsonLedTextView.setText(ledTextView);
                } catch (JSONException e) {
                    throw new RuntimeException(e);
                }

            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if (httpURLConnection != null) {
                    httpURLConnection.disconnect();

                    Log.d("HTTP Request", "Disconnecting from client.");
                }
            }
            return null;
        }
    }

}