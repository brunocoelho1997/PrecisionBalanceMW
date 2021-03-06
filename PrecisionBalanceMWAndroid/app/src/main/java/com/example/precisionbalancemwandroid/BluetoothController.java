package com.example.precisionbalancemwandroid;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.IOException;
import java.util.Set;
import java.util.UUID;

import static com.example.precisionbalancemwandroid.Config.CONNECTION_ERROR_MESSAGE;
import static com.example.precisionbalancemwandroid.Config.MY_PERMISSIONS_REQUEST_CODE_BT;


public class BluetoothController {
    private static String TAG = "BluetoothController";
    private BluetoothAdapter bluetoothAdapter;

    String bluetoothAddressArduino;
    private BluetoothSocket mmSocket;
    private BluetoothDevice mmDevice;
    private boolean isBtConnected = false;
    private Context context;
    private int lastThrootlePercentageTmp;

    public BluetoothController(Context context) {
        this.context = context;
    }

    public void verifyIfBluetoothIsEnabled(Context context) {
        //if the bluetooth is not enabled
        if (!bluetoothAdapter.isEnabled()) {
            //Request to enable the bluetooth
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            ((Activity) context).startActivityForResult(enableBtIntent, MY_PERMISSIONS_REQUEST_CODE_BT);
        }
    }

    public String startDiscoveringDevices(Context context) {

        //verify again if the bluetooth is enabled... just for precaution
        if (!bluetoothAdapter.isEnabled()) {
            Log.d("startDiscoringDevices", "Bluetooth isn't enabled.");
            return "Bluetooth isn't enabled.";
        }

        Set<BluetoothDevice> pairedDevices = bluetoothAdapter.getBondedDevices();

        if (pairedDevices.size() > 0) {
            for (BluetoothDevice bt : pairedDevices) {
                Log.d("BluetoothController", "paired device: " + bt.getName() + "\n" + bt.getAddress());

                if (bt.getName().equals("HC-06")) {
                    String info = bt.getAddress();
                    String address = info.substring(info.length() - 17);
                    this.bluetoothAddressArduino = address;

                    //start the connection with the bt device
                    new BluetoothConnection().execute();

                    return "Starting connection with the precision balance...";
                }
            }
            return "Didn't find a paired device with name HC-06. It's necessary to pair the Android with the device. Pin: 1234";
        }

        return "No Paired Bluetooth Devices Found.";
    }

    public boolean sendCommand(String command) {

        try {
            if (mmSocket == null)
                return false;

//            DataOutputStream mmOutStream = new DataOutputStream(mmSocket.getOutputStream());
//
//            mmOutStream.write(command.getBytes());


            mmSocket.getOutputStream().write(command.getBytes());
            Log.d(TAG, "The value has been sent to the balance.");

            return true;

        } catch (IOException e) {
            e.printStackTrace();
            Log.d(TAG, "Does not exist a connectedThread alive. Error: " + e);
            return false;
        }
    }

    public String readFromBluetooth() {

        try {
            if (mmSocket == null)
                return "";

            byte[] buffer = new byte[160];  // buffer store for the stream
            int bytes;

            DataInputStream mmInStream = new DataInputStream(mmSocket.getInputStream());
            bytes = mmInStream.read(buffer);
            String readMessage = new String(buffer, 0, bytes);

            readMessage = removeNoise(readMessage);

            Log.d(TAG, "Was received data from Arduino. Data: " + readMessage);

            return readMessage;

        } catch (IOException e) {
            e.printStackTrace();
            Log.d(TAG, "Does not exist a connectedThread alive. Error: " + e);
            return "";
        }
    }

    /**
     * When is received raw values from arduino... It comes like "getRawValuesFromCells:  0.13 0.24 -0.01 -0.02". The "getRawValuesFromCells:" must be removed
     *
     * @param readMessage raw data from arduino with noise
     * @return clean raw data (only with cell values)
     */
    private String removeNoise(String readMessage) {

        String messageWithoutNoise = readMessage;

        if (readMessage.contains(";")) {
            messageWithoutNoise = messageWithoutNoise.split("\\;")[0];

        } else {
            return "";
        }

        return messageWithoutNoise;
    }


    public boolean exportValues() {
        return sendCommand(Config.EXPORT_VALUES_COMMAND);
    }

    public boolean tare() {
        return sendCommand(Config.TARE_COMMAND);
    }

    private class BluetoothConnection extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute() {
            Toast.makeText(context, "Connecting with the bluetooth precision balance...", Toast.LENGTH_LONG).show();
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try {
                if (mmSocket == null || !isBtConnected) {
                    bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                    mmDevice = bluetoothAdapter.getRemoteDevice(bluetoothAddressArduino);//connects to the device's address and checks if it's available
                    mmSocket = mmDevice.createInsecureRfcommSocketToServiceRecord(UUID.fromString(Config.RC_UUID));//create a RFCOMM (SPP) connection
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    mmSocket.connect();//start connection
                }
            } catch (IOException e) {
                ConnectSuccess = false;//if the try failed, you can check the exception here
                Log.d("BluetoothController", "error: " + e.getMessage());

            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
                Toast.makeText(context, CONNECTION_ERROR_MESSAGE, Toast.LENGTH_LONG).show();
            else
                Toast.makeText(context, "Connection initialized with success.", Toast.LENGTH_LONG).show();


        }
    }

    /*
        Getters and Setters
     */
    public BluetoothAdapter getBluetoothAdapter() {
        return bluetoothAdapter;
    }

    public void setBluetoothAdapter(BluetoothAdapter bluetoothAdapter) {
        this.bluetoothAdapter = bluetoothAdapter;
    }
}
