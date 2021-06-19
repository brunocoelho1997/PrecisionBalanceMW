package com.example.precisionbalancemwandroid;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.pm.PackageManager;

import androidx.core.app.ActivityCompat;

import static com.example.precisionbalancemwandroid.Config.PERMISSIONS;

public class PrecisionBalanceMwController {

    private boolean userHasPermissions;
    private BluetoothController bluetoothController;

    public PrecisionBalanceMwController(Context context) {
        this.bluetoothController = new BluetoothController(context);
    }

    public boolean hasPermissions(Context context, String... permissions) {
        if (context != null && permissions != null) {
            for (String permission : permissions) {
                if (ActivityCompat.checkSelfPermission(context, permission) != PackageManager.PERMISSION_GRANTED) {
                    return false;
                }
            }
        }
        return true;
    }

    public void requestPermissionsToUser(Context context) {
        if(!hasPermissions(context, PERMISSIONS)){
            ActivityCompat.requestPermissions((Activity)context, PERMISSIONS, Config.MY_PERMISSIONS_REQUEST_CODE);
        }
    }


    public boolean isUserHasPermissions() {
        return userHasPermissions;
    }

    public void setUserHasPermissions(boolean userHasPermissions) {
        this.userHasPermissions = userHasPermissions;
    }

    public void verifyIfBluetoothIsEnabled(Context context){
        bluetoothController.verifyIfBluetoothIsEnabled(context);
    }

    public String startDiscoveringDevices(Context context){
        return bluetoothController.startDiscoveringDevices(context);
    }

    public void setBluetoothAdapter(BluetoothAdapter bluetoothAdapter) {
        this.bluetoothController.setBluetoothAdapter(bluetoothAdapter);
    }

    public boolean exportValues() {
        return bluetoothController.exportValues();
    }

    public boolean tare() {
        return bluetoothController.tare();
    }

    public String readRawData() {
        return bluetoothController.readFromBluetooth();
    }
}
