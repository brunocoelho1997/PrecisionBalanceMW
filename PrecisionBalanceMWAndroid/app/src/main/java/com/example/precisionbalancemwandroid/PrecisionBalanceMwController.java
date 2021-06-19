package com.example.precisionbalancemwandroid;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.pm.PackageManager;
import android.util.Log;

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

    public BluetoothAdapter getBluetoothAdapter() {
        return this.bluetoothController.getBluetoothAdapter();
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

    public double getMeanFromGroupCell(GroupCell groupCell, String actualRawData) {
        double total = 0;

        String[] cellsRawData = actualRawData.split("\\s+");

        if(cellsRawData.length <= 16) {
            return 0;
        }

        switch (groupCell){
            case A:
                total = Double.valueOf(cellsRawData[0]) + Double.valueOf(cellsRawData[1]) + Double.valueOf(cellsRawData[2]) + Double.valueOf(cellsRawData[3]);
                break;
            case B:
                total = Double.valueOf(cellsRawData[4]) + Double.valueOf(cellsRawData[5]) + Double.valueOf(cellsRawData[6]) + Double.valueOf(cellsRawData[7]);
                break;
            case C:
                total = Double.valueOf(cellsRawData[8]) + Double.valueOf(cellsRawData[9]) + Double.valueOf(cellsRawData[10]) + Double.valueOf(cellsRawData[11]);
                break;
            case D:
                total = Double.valueOf(cellsRawData[12]) + Double.valueOf(cellsRawData[13]) + Double.valueOf(cellsRawData[14]) + Double.valueOf(cellsRawData[15]);
                break;
        }


        return round(total/4, 2);
    }

    public static double round(double value, int places) {
        if (places < 0) throw new IllegalArgumentException();

        long factor = (long) Math.pow(10, places);
        value = value * factor;
        long tmp = Math.round(value);
        return (double) tmp / factor;
    }
}
