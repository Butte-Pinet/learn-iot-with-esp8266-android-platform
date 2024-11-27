package com.example.internetconnect;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity{
    private static final String DEBUG_TAG = "NetworkStatus";
    TextView textViewStatus;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textViewStatus = findViewById(R.id.txtViewStatus);
        final Button btnNetworkChk = findViewById(R.id.buttonClick);
        btnNetworkChk.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                internetConnectChck();
            }
        });
    }
    private void internetConnectChck() {
        ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        boolean isWifiConn = false;
        for (Network network : connMgr.getAllNetworks()) { // A for-each style for loop
            NetworkInfo networkInfo = connMgr.getNetworkInfo(network);
            if (networkInfo != null && networkInfo.getType() == ConnectivityManager.TYPE_WIFI) {
                isWifiConn |= networkInfo.isAvailable();
                textViewStatus.setText("เชื่อมต่อไวไฟแล้ว");
            }
            else {
                textViewStatus.setText("ไม่มีการเชื่อมต่อไวไฟ");
            }
        }
        Log.d(DEBUG_TAG, "WiFi Connected: " + isWifiConn);

    }
}