package com.lampt.ledlamptservice;

import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.Icon;
import android.os.IBinder;
import android.util.Log;

public class LedLamptService extends Service {
    private static final String TAG = LedLamptService.class.getSimpleName();
    private static final String LED_CONTROL_SERVICE_NOTIFICATION_CHAN_ID =
                                                        "lampt_led_control_service_channel";
    private LedLamptServiceImpl mServiceImpl;
    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "onCreate");

        mServiceImpl = new LedLamptServiceImpl(this);
    }
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        startForegroundMethod();
        Log.i(TAG, "onStartCommand");

        return START_STICKY;
    }
    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        if(mServiceImpl == null) {
            Log.e(TAG, "LedLamptServiceImpl bind failed");
        }
        Log.i(TAG, "LedLamptServiceImpl bind");
        return mServiceImpl;
    }

    @SuppressLint({"NewApi", "ForegroundServiceType"})
    private void startForegroundMethod() {
        //1. Notification
        final NotificationChannel channel = new NotificationChannel(
                LED_CONTROL_SERVICE_NOTIFICATION_CHAN_ID, "Led Control Service",
                NotificationManager.IMPORTANCE_NONE);

        channel.setLockscreenVisibility(Notification.VISIBILITY_PRIVATE);

        final NotificationManager notificationManager =
                (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.createNotificationChannel(channel);

        final Notification.Builder notificationBuilder = new Notification.Builder(
                this, LED_CONTROL_SERVICE_NOTIFICATION_CHAN_ID
        );

        //2. Start foreground
        final Notification notification = notificationBuilder.setOngoing(true)
                .setContentTitle("LedControlService is running")
                .setSmallIcon(createNotificationIcon())
                .setCategory(Notification.CATEGORY_SERVICE)
                .setContentText("Context")
                .build();
        startForeground(1, notification);
        Log.i(TAG, "Starting foreground service!!!!");
    }

    Icon createNotificationIcon() {
        Bitmap mTestBitmap = Bitmap.createBitmap(50, 50, Bitmap.Config.ARGB_8888);
        final Canvas canvas = new Canvas(mTestBitmap);
        canvas.drawColor(Color.BLUE);
        return  Icon.createWithBitmap(mTestBitmap);
    }
}