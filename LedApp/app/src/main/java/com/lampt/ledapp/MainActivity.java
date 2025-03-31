package com.lampt.ledapp;

import android.os.Bundle;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import com.lampt.ledlamptmanager.LedLamptManager;

public class MainActivity extends AppCompatActivity {
    private final static String TAG = "LedApp";
    private LedLamptManager mLedLamptManager;
    private Button buttonOn, buttonOff;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    private void init() {
        mLedLamptManager = new LedLamptManager(this);
        try {
            mLedLamptManager.connectToService();
        } catch (RemoteException e) {
            Log.e(TAG, "Couldn't connect to service");
        }

        buttonOn = (Button) findViewById(R.id.btOn);
        buttonOff = (Button) findViewById(R.id.btOff);

        buttonOn.setOnClickListener(new View.OnClickListener() {
            String retVal;
            @Override
            public void onClick(View v) {
                mLedLamptManager.setLed("on");

                try {
                    retVal = mLedLamptManager.getLed();
                } catch (NumberFormatException e) {
                    Log.e(TAG, "get led failed");
                    retVal = null;
                }
            }
        });

        buttonOff.setOnClickListener(new View.OnClickListener() {
            String retVal;
            @Override
            public void onClick(View v) {
                mLedLamptManager.setLed("off");

                try {
                    retVal = mLedLamptManager.getLed();
                } catch (NumberFormatException e) {
                    Log.e(TAG, "get led failed");
                    retVal = null;
                }
            }
        });
    }
}