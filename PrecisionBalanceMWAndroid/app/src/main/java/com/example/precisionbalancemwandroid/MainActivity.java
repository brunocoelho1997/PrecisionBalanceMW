package com.example.precisionbalancemwandroid;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.bluetooth.BluetoothAdapter;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

import static com.example.precisionbalancemwandroid.Config.CONNECTION_ERROR_MESSAGE;
import static com.example.precisionbalancemwandroid.Config.PERMISSIONS;

public class MainActivity extends AppCompatActivity {
    private static String TAG = "MainActivity";

    PrecisionBalanceMwController precisionBalanceMwController;
    String actualRawData;

    private TextView textViewRawData;
    private TextView textViewGroupCellA;
    private TextView textViewGroupCellB;
    private TextView textViewGroupCellC;
    private TextView textViewGroupCellD;
    private Button btnConnect;
    private Button btnExportValues;
    private Button btnTare;

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
                Toast.makeText(getApplicationContext(), CONNECTION_ERROR_MESSAGE, Toast.LENGTH_SHORT).show();

            }
        });

        btnTare = findViewById(R.id.btn_tare);
        btnTare.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
            boolean result = precisionBalanceMwController.tare();
            if(!result)
                Toast.makeText(getApplicationContext(), CONNECTION_ERROR_MESSAGE, Toast.LENGTH_SHORT).show();

            }
        });

        textViewRawData = findViewById(R.id.tv_raw_data);
        textViewGroupCellA = findViewById(R.id.tv_group_cell_a);
        textViewGroupCellB = findViewById(R.id.tv_group_cell_b);
        textViewGroupCellC = findViewById(R.id.tv_group_cell_c);
        textViewGroupCellD = findViewById(R.id.tv_group_cell_d);

        ScheduledExecutorService textService = Executors.newScheduledThreadPool(1);
        textService.scheduleAtFixedRate(new Runnable() {
            @Override
            public void run() {
                textViewRawData.post(new Runnable() {
                    @Override
                    public void run() {
                        actualRawData = precisionBalanceMwController.readRawData();

                        updateTextViews(actualRawData);

                        Log.d(TAG, "Was requested raw data to be printed. Data:" + actualRawData);
                    }
                });
            }
        }, 0, 2, TimeUnit.SECONDS);

    }

    void updateTextViews(String actualRawData) {

        textViewRawData.setText(actualRawData);
        textViewGroupCellA.setText(String.valueOf(precisionBalanceMwController.getMeanFromGroupCell(GroupCell.A, actualRawData)));
        textViewGroupCellB.setText(String.valueOf(precisionBalanceMwController.getMeanFromGroupCell(GroupCell.B, actualRawData)));
        textViewGroupCellC.setText(String.valueOf(precisionBalanceMwController.getMeanFromGroupCell(GroupCell.C, actualRawData)));
        textViewGroupCellD.setText(String.valueOf(precisionBalanceMwController.getMeanFromGroupCell(GroupCell.D, actualRawData)));

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
