package com.example.httpclientforandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "HTTP Request";
    private static Button buttonOn, buttonOff;
    private static TextView ledTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ledTextView = (TextView) findViewById(R.id.ledTextView);

        buttonOn = (Button) findViewById(R.id.buttonOn);
        buttonOn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new HttpRegTaskOn().execute();

                ledTextView.setText("LED (GPIO): ON");

                Log.d(TAG, "LED (GPIO): ON");
            }
        });

        buttonOff = (Button) findViewById(R.id.buttonOff);
        buttonOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new HttpRegTaskOff().execute();

                ledTextView.setText("LED (GPIO4):OFF");

                Log.d(TAG, "LED (GPIO4): OFF");
            }
        });
    }
}