package com.itita.androidservice;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class ServiceReceiver extends BroadcastReceiver{

	@Override
	public void onReceive(Context arg0, Intent arg1) {
//		System.out.println("得吃得吃得吃得吃得吃得吃得吃得吃");
		arg0.startService(new Intent(arg0,NotificationService.class));
	}

}

