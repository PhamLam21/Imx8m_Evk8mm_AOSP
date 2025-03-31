package com.lampt.ledlamptservice;

import android.app.Service;
import android.os.IBinder;
import android.os.Binder;
import android.content.Intent;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;

import androidx.annotation.Nullable;

import java.util.Objects;

import vendor.lampt.hardware.led.ILedAidl; //Import HAL

public class LedHalClient extends Service {
    private static final String TAG = LedHalClient.class.getSimpleName();
    private IBinder mBinder;
    private ILedAidl mLedAidl;
    private static final String LED_AIDL_SERVICE = "vendor.lampt.hardware.led.ILedAidl/default";
    private static LedHalClient mLedHalClient;
    static @Nullable IBinder getService() {
        return Binder.allowBlocking(ServiceManager.waitForDeclaredService(LED_AIDL_SERVICE));
    }
    public LedHalClient() {
        init();
    }

    public static LedHalClient getLedHalClient() {
        if(mLedHalClient == null) {
            mLedHalClient = new LedHalClient();
        }
        return mLedHalClient;
    }

    public void init() {
        mBinder = Objects.requireNonNull(getService());
        mLedAidl = ILedAidl.Stub.asInterface(mBinder);
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    public void setLed(String value) {
        try {
            mLedAidl.setLed(value);
            Log.i(TAG, "setLed with value = " + value);
        } catch (RemoteException e) {
            Log.e(TAG, "setLed with value = " + value + "failed");
        }

    }

    public String getLed() throws RemoteException {
        String mLedValue = mLedAidl.getLed();
        Log.i(TAG, "getLed " + mLedValue);
        return mLedValue;
    }

}