package vendor.lampt.hardware.led;

@VintfStability
interface ILedAidl {
    int setLed(in String value);  
    String getLed();              
}