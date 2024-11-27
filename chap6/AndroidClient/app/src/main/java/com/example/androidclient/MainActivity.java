package com.example.androidclient;

import static com.example.androidclient.R.id.greetingButton;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "Android MQTT Client";
    private String mqttBroker = "tcp://mqtt.netpie.io";
    private String mqttTopic = "@msg/greeting";
    private String clientId = "clientId"; // client id
    MqttClient mqttClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final TextView greetingTextView = (TextView) findViewById(R.id.greetingTextView);

        try {
            Log.i(TAG, "Creating New Client.");
            //MqttClient mqttClient = new MqttClient(mqttBroker, clientId, new MemoryPersistence());
            mqttClient = new MqttClient(mqttBroker, clientId, new MemoryPersistence());
            Log.i(TAG, "Setting Connection Options");
            MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();

            mqttConnectOptions.setCleanSession(true);
            mqttConnectOptions.setUserName("username"); //เพิ่ม (token)
            mqttConnectOptions.setPassword("password".toCharArray()); //เพิ่ม (secrete)
            mqttClient.connect(mqttConnectOptions);

            Log.i(TAG, "Subscribing to Topic");

            mqttClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable arg0) {
                    Log.i(TAG, "Client lost Connection");
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken arg0) {
                    Log.i(TAG, "Message delivered complete" );
                }

                @Override
                public void messageArrived(String topic, final MqttMessage msg) throws Exception {
                    Log.i(TAG, "New Message Arrived from Topic - " + topic + " - " + msg);

                    try {
                        greetingTextView.setText(msg.toString());

                    } catch (Exception e) {
                        e.printStackTrace();
                        Log.i("MQTT Client", "Exception: " + e.getMessage());
                    }
                }

            });

            mqttClient.subscribe(mqttTopic, 1);

        } catch (MqttException e)
        { e.printStackTrace();}

        final Button pubButton = (Button) findViewById(R.id.greetingButton);

        pubButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                pubMessage("Hello Node MCU");
            }
        });

    }
    public void pubMessage(String payload) {
        try {
            if (!mqttClient.isConnected()) {
                mqttClient.connect();
            }

            // Publish message to topic
            Log.i(TAG, "Publishing to Topic");
            MqttMessage mqttMessage = new MqttMessage();
            mqttMessage.setPayload(payload.getBytes());
            mqttMessage.setQos(0);
            mqttClient.publish(mqttTopic, mqttMessage);
            Log.i(TAG, "Publishing Complete");

            //Log.i(TAG, "Disconnecting from MQTT");
            //mqttClient.disconnect();

        } catch (MqttException e) {
            Log.e(TAG, e.toString());
            e.printStackTrace();
        }
    }

}