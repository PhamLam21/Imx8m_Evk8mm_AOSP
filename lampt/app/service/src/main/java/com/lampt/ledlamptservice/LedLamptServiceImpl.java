package com.lampt.ledlamptservice;

import android.content.Context;
import android.os.RemoteCallbackList;
import android.os.RemoteException;
import android.util.Log;

//Stub: Server, Stub.asInterface: Client
//Bp: Client, Bn: Server

public class LedLamptServiceImpl extends ILedLamptService.Stub {

    private static final String TAG  = LedLamptServiceImpl.class.getSimpleName();
    public final RemoteCallbackList<ILedLamptServiceCallback> subcriber = new RemoteCallbackList<>();
    private LedHalClient mLedHalClient;
    public LedLamptServiceImpl(Context context) {
        Log.d(TAG, "Constructor of LedLamptServiceImp");
        //Context mContext = context;
        //LedHalClient -> nối đến Led HAL
        mLedHalClient = LedHalClient.getLedHalClient();
    }
    public void setLed(String value) throws RemoteException {
        //LedHalClient.setLed
        mLedHalClient.setLed(value);
        Log.i(TAG, "setLed with value = " + value);
    }
    public String getLed() throws RemoteException {
        String mValue = "off";
        Log.i(TAG, "getLed " + mValue);
        //mValue = LedHalClient.getLed
        mValue = mLedHalClient.getLed();
        return mValue;
    }

    @Override
    public void subscribe(ILedLamptServiceCallback callback) throws RemoteException {
        subcriber.register(callback);
        Log.d(TAG, "Register ILedLamptServiceCallBack successfully!");
    }

    @Override
    public void unsubscribe(ILedLamptServiceCallback callback) throws RemoteException {
        subcriber.unregister(callback);
        Log.d(TAG, "Unregister ILedLamptServiceCallBack successfully!");
    }
}