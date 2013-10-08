package com.itita.ww2;

import java.io.IOException;

import com.itita.wwdz.WW14;


import android.app.Activity;
import android.app.Service;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public class HelloJni extends Activity
{
	Button button;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        LinearLayout ll = new LinearLayout(this);
        TextView  tv = new TextView(this);
        tv.setText("hahahaha");
        ll.addView(tv);
        button = new Button(this);
        button.setText("button");
        try {
			Util.moveAssetsFile2SDCard(this, "terrain.png");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			finish();
		}
        
        button.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent intent = new Intent(HelloJni.this,WW14.class);
				startActivity(intent);
				finish();
			}
		});
        ll.addView(button);
        setContentView(ll);
        TelephonyManager tm = (TelephonyManager) this.getSystemService(Service.TELEPHONY_SERVICE);
        Util.deviceId = tm.getDeviceId();
//        ExtraArgs.ITITAID =  Util.deviceId;
//        ExtraArgs.NICKNAME = "";
//        ExtraArgs.VERSION="0.3";
    }

    
}
