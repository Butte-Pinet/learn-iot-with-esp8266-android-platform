package com.example.httpclientforandroid;

import android.os.AsyncTask;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
public class HttpRegTaskOff extends AsyncTask<Void, Void, String> {
    private static final String TAG_Response = "HTTP Response ->";
    //private static final String TAG_HeaderField = "Header field ->";
    private static final String TAG_Header = "HTTP Request ->";
    private static final String TAG_HTML = "HTTP Response";
    @Override
    protected String doInBackground(Void... params) {
        HttpURLConnection httpURLConnection = null;

        try {
            URL url = new URL("http://192.168.1.39/gpio4/0");
            httpURLConnection = (HttpURLConnection) url.openConnection();
            InputStream inputStream = httpURLConnection.getInputStream();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream));

            int responseCode = httpURLConnection.getResponseCode();
            String responseMessage = httpURLConnection.getResponseMessage();
            Log.d(TAG_Header, "HTTP/1.x " + responseCode + " " +responseMessage);

            StringBuilder htmlResult = new StringBuilder();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                htmlResult.append(line);
                Log.i(TAG_Response, " " + line);
            }

            //Log.d(TAG_HTML, htmlResult.toString());

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            httpURLConnection.disconnect();

            Log.d(TAG_Response, "Disconnectting from client.");
        }
        return null;
    }
}