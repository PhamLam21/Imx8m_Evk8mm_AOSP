package com.lampt.ledlamptmanager;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.NonNull;
import com.lampt.ledlamptservice.ILedLamptService;
public class LedLamptManager {
    private static final String TAG = LedLamptManager.class.getSimpleName();
    private static final String LED_SETTINGS_PACKAGE = "com.lampt.ledlamptservice";
    private static final String LED_SETTINGS_CLASS = "com.lampt.ledlamptservice.LedLamptService";
    private Context mContext = null;

    private ILedLamptService mLedLamptService = null;
    private final ServiceConnection mServiceConnect = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder iBinder) {
            Log.i(TAG, "Connect to service");
            mLedLamptService = ILedLamptService.Stub.asInterface(iBinder);
            if(mLedLamptService == null) {
                Log.e(TAG, "Stub failed!");
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            mLedLamptService = null;
            Log.i(TAG, "Disconnect to service");
        }
    };
    public LedLamptManager(@NonNull Context context) {
        mContext = context;
    }

    public void connectToService() throws RemoteException {
        Intent intent = new Intent();
        intent.setComponent(new ComponentName(LED_SETTINGS_PACKAGE, LED_SETTINGS_CLASS));

        if(mContext.bindService(intent, mServiceConnect, Context.BIND_AUTO_CREATE)) {
            Log.e(TAG, "Couldn't connectToService");
            throw new RemoteException("Failed to bind to service");
        }
        Log.i(TAG, "Connect to service successfully!");
    }

    public void disconnectToService() throws RemoteException {
        if(mLedLamptService != null) {
            mContext.unbindService(mServiceConnect);
        }
        Log.i(TAG, "Disconnect to service successfully!");
    }

    public void setLed(String value) {
        try {
            if (mLedLamptService == null) {
                Log.e(TAG, "Interface NULL");
            }
            mLedLamptService.setLed(value);
        } catch (RemoteException e) {
            Log.e(TAG, "Error running set led", e);
        }
    }

    public String getLed() {
        Log.i(TAG, "get led called");
        try {
            String mValueLed = mLedLamptService.getLed();
            return mValueLed;
        } catch (RemoteException e) {
            Log.d(TAG, "Error running get led", e);
            return null;
        }
    }
}