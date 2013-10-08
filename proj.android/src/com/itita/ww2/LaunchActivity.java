package com.itita.ww2;

import com.umeng.update.UmengUpdateAgent;
import com.umeng.update.UmengUpdateListener;
import com.umeng.update.UpdateResponse;

import android.app.Activity;
import android.os.Bundle;
import android.widget.Toast;

public class LaunchActivity extends Activity{

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		UmengUpdateAgent.update(this);
		UmengUpdateAgent.setUpdateAutoPopup(false);
		UmengUpdateAgent.setUpdateListener(new UmengUpdateListener() {
		       
				@Override
				public void onUpdateReturned(int arg0, UpdateResponse arg1) {
					switch (arg0) {
		            case 0: // has update
		                UmengUpdateAgent.showUpdateDialog(LaunchActivity.this, arg1);
		                break;
		            case 1: // has no update
		                Toast.makeText(LaunchActivity.this, "没有更新", Toast.LENGTH_SHORT)
		                        .show();
		                break;
		            case 2: // none wifi
		                Toast.makeText(LaunchActivity.this, "没有wifi连接， 只在wifi下更新", Toast.LENGTH_SHORT)
		                        .show();
		                break;
		            case 3: // time out
		                Toast.makeText(LaunchActivity.this, "超时", Toast.LENGTH_SHORT)
		                        .show();
		                break;
		            }
					
				}
		});
	}
	
	
	
	
}
