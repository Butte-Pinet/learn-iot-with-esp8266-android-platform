package com.example.livingroommonitoring;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.json.JSONObject;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MQTT Client";
    private String mqttBroker = "tcp://mqtt.netpie.io";
    private String mqttTopic = "@msg/livingroom/temphum";
    private String clientId = "";
    MqttClient mqttClient;
    private String temperature, humidity;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("Temp and Humidity in Living Room");
        //setting text view
        final TextView statusTextView = (TextView) findViewById(R.id.show_status);
        final TextView tempTextView = (TextView) findViewById(R.id.show_temp);
        final TextView humTextView = (TextView) findViewById(R.id.show_humi);

        try {
            Log.i(TAG, "Creating New Client.");

            mqttClient = new MqttClient(mqttBroker, clientId, new MemoryPersistence());
            Log.i(TAG, "Setting Connection Options");
            MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
            mqttConnectOptions.setCleanSession(true);
            mqttConnectOptions.setUserName("");
            mqttConnectOptions.setPassword("".toCharArray());
            mqttClient.connect(mqttConnectOptions);

            Log.i(TAG, "Subscribing to Topic");
            mqttClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    Log.i(TAG, "Client lost Connection");
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) throws Exception {
                    Log.i(TAG, "New Message Arrived from Topic - " + topic + " - " + message);
                    statusTextView.setText("Client connected");

                    try {
                        //Parse JSON object
                        JSONObject jsonObject = new JSONObject(message.toString());

                        temperature = jsonObject.getJSONObject("dht").getString("temp") + "°C";
                        humidity = jsonObject.getJSONObject("dht").getString("hum") + "%";
                        tempTextView.setText(temperature);
                        humTextView.setText(humidity);
                        Log.d("MQTT Client", "JSON string is parsed");

                    } catch (Exception e) {
                        e.printStackTrace();
                        Log.i("MQTTClient", "Exception: " + e.getMessage());
                    }
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    Log.i(TAG, "Message delivered complete" );
                }
            });

            mqttClient.subscribe(mqttTopic, 0);
        } catch (MqttException e) {

            e.printStackTrace();
            Log.i("MQTT Client", "Exception: " + e.getMessage());
        }
    }
}
