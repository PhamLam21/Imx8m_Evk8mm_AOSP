// ILedLamptService.aidl
package com.lampt.ledlamptservice;

// Declare any non-default types here with import statements
import com.lampt.ledlamptservice.ILedLamptServiceCallback;

interface ILedLamptService {
    void setLed(in String value);
    String getLed();
    void subscribe(in ILedLamptServiceCallback callback);
    void unsubscribe(in ILedLamptServiceCallback callback);
}