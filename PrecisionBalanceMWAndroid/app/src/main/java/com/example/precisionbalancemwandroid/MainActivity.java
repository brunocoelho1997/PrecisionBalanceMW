package com.example.precisionbalancemwandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import static com.example.precisionbalancemwandroid.Config.PERMISSIONS;

public class MainActivity extends AppCompatActivity {

    PrecisionBalanceMwController precisionBalanceMwController;

    private Button btnConnect;
    private Button btnExportValues;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.precisionBalanceMwController = new PrecisionBalanceMwController(getApplicationContext());

        boolean userHasPermissionsTmp = precisionBalanceMwController.hasPermissions(this, PERMISSIONS);
        precisionBalanceMwController.setUserHasPermissions(userHasPermissionsTmp);

        if(precisionBalanceMwController.isUserHasPermissions())
        {
            defineSensors();
            defineLayout();
        }
        else
        {
            precisionBalanceMwController.requestPermissionsToUser(this);
        }
    }

    private void defineLayout() {

        btnConnect = findViewById(R.id.btn_connect);
        btnConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                precisionBalanceMwController.verifyIfBluetoothIsEnabled(MainActivity.this);
                String result = precisionBalanceMwController.startDiscoveringDevices(MainActivity.this);

                Toast.makeText(getApplicationContext(), result, Toast.LENGTH_LONG).show();

            }
        });

        btnExportValues = findViewById(R.id.btn_export_values);
        btnExportValues.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                boolean result = precisionBalanceMwController.exportValues();
                if(!result)
                    Toast.makeText(getApplicationContext(), "Error with connection with the RC.", Toast.LENGTH_LONG).show();

            }
        });
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        for(int i=0; i<=grantResults.length-1; i++)
        {
            if(grantResults[i] == PackageManager.PERMISSION_DENIED)
            {
                throwAlertBuilder(getString(R.string.permissions_denied),getString(R.string.permissions_denied_desc));
                return;
            }
        }

        //TODO: test this
        defineSensors();
        defineLayout();
    }

    public void throwAlertBuilder(String titleMessage, String descMessage){
        new AlertDialog.Builder(this)
                .setTitle(titleMessage)
                .setMessage(descMessage)

                // Specifying a listener allows you to take an action before dismissing the dialog.
                // The dialog is automatically dismissed when a dialog button is clicked.
                .setPositiveButton(android.R.string.yes, new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int which) {
                        finish();
                    }
                })
                .setIcon(android.R.drawable.ic_dialog_alert)
                .show();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    private void defineSensors() {
        BluetoothAdapter bluetoothAdapterTmp = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapterTmp == null) {
            // Device doesn't support Bluetooth
            finish();
        }
        precisionBalanceMwController.setBluetoothAdapter(bluetoothAdapterTmp);
    }
}
