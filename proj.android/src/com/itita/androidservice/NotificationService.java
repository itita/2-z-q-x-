package com.itita.androidservice;

import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

import name.wwd.update.Updater;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.IBinder;
import android.util.Log;

import com.itita.dev.R;
import com.itita.ww2.HelloJni;

public class NotificationService extends Service {

	private NotificationManager mNotificationManager;
	// private Context mContext;
	NetworkInfo netinfo;
	ConnectivityManager nw = null;
	Timer timer = new Timer();

	@Override
	public void onCreate() {
		Log.i("create", "create");
		
		
		super.onCreate();
		delayCheckUpdate();
		
	}
	
	@Override
	public void onDestroy() {		
		super.onDestroy();
		timer.cancel();
	}

	@Override
	public void onStart(Intent intent, int startId) {
		super.onStart(intent, startId);
	}

	@Override
	public int onStartCommand(Intent intent, int flags, int startId) {
		Log.i("start", "start");
		mNotificationManager = (NotificationManager) getSystemService(android.content.Context.NOTIFICATION_SERVICE);
		nw = (ConnectivityManager) this
				.getSystemService(Context.CONNECTIVITY_SERVICE);
		netinfo = nw.getActiveNetworkInfo();
//		delayCheckUpdate();
//		if (checkInternet()) {
//			int replyCount = getReplyCount();
//			if (replyCount > 0) {
//				setUpNotification(replyCount);
//			}
//		}
		
//		SharedPreferences appInfo = this.getSharedPreferences("Date", 0);
//		String date = appInfo.getString("date", "");
//		final Calendar c = Calendar.getInstance();
//		int mYear = c.get(Calendar.YEAR); // ��ȡ��ǰ���
//		int mMonth = c.get(Calendar.MONTH);// ��ȡ��ǰ�·�
//		int mDay = c.get(Calendar.DAY_OF_MONTH);// ��ȡ��ǰ�·ݵ����ں���
////		System.out.println("�������ڣ�" + mYear+"-"+mMonth+"-"+mDay);
////		System.out.println("�ϴ����ڣ�"+ date);
//		if(!"".equals(date)) {
//			int lastDay  =Integer.parseInt(date.split("-")[2]);
//			int xinDay = mDay; 
//			if(mDay < lastDay) {
//				xinDay = mDay +30;
//			}
//			if(xinDay -  lastDay >= 3) {
//				setUpDateNotification();
//				appInfo.edit().putString("date", mYear+"-"+mMonth+"-"+mDay).commit();
//			} 
//		}
		return super.onStartCommand(intent, flags, startId);
	}
	
	public void delayCheckUpdate() {
		
		final Calendar c = Calendar.getInstance(); 
        int mYear = c.get(Calendar.YEAR); //获取当前年份 
        int mMonth = c.get(Calendar.MONTH);//获取当前月份 
        int mDay = c.get(Calendar.DAY_OF_MONTH);//获取当前月份的日期号码 
        int mHour = c.get(Calendar.HOUR_OF_DAY);//获取当前的小时数 
        int mMinute = c.get(Calendar.MINUTE);//获取当前的分钟数
        
        
        float nowTime = mHour + (float)mMinute/60.0f;
        System.out.println(nowTime);
        float dt  = 12.5f;
        float dt2 = 23f;
        if(nowTime < 12.5) {
        	dt = 12.5f - nowTime;
        	dt2 = 23f - nowTime;
        } else if (nowTime<23){
        	dt = 36.5f - nowTime;
        	dt2 = 23f - nowTime;
        } else {
        	dt = 36.5f - nowTime;
        	dt2 = 47f - nowTime;
        }
        long millsec = (long)(dt * 1000*3600);
        long millsec2 = (long)(dt2 * 1000*3600);
        
        System.out.println(millsec);
        
    	TimerTask task1 = new updateTimeTask();
		timer.schedule(task1, millsec, 86400000);
		TimerTask task2 = new updateTimeTask();
		timer.schedule(task2, millsec2, 86400000);
	}

	private void setUpNotification(int replyCount) {
		System.out.println("提醒");
		int icon = R.drawable.ic_wwicon;
		CharSequence tickerText = "您的部队需要指挥官！";
		long when = System.currentTimeMillis();
		Notification mNotification = new Notification(icon, tickerText, when);

		mNotification.flags = Notification.FLAG_AUTO_CANCEL;

		Intent intent = new Intent(this, Updater.class);
		PendingIntent contentIntent = PendingIntent.getActivity(this, 0,
				intent, 0);
		mNotification.defaults = Notification.DEFAULT_SOUND;
		mNotification.contentIntent = contentIntent;
		mNotification.setLatestEventInfo(this, "您的部队需要指挥官！",
				"您的基地受到攻击！碾碎入侵者", contentIntent);
		mNotificationManager.notify(0, mNotification);

	}
	
	private void setUpDateNotification() {

		int icon = R.drawable.ic_wwicon;
		CharSequence tickerText = "您的战友都很想念你";
		long when = System.currentTimeMillis();
		Notification mNotification = new Notification(icon, tickerText, when);

		mNotification.flags = Notification.FLAG_AUTO_CANCEL;

		Intent intent = new Intent(this, HelloJni.class);
		PendingIntent contentIntent = PendingIntent.getActivity(this, 0,
				intent, 0);

		mNotification.contentIntent = contentIntent;
		mNotification.setLatestEventInfo(this, "您的部队需要指挥官",
				"赶紧协助他们抵挡轴心国的进攻！", contentIntent);
		mNotificationManager.notify(0, mNotification);

	}

	@Override
	public IBinder onBind(Intent intent) {
		// TODO Auto-generated method stub
		return null;
	}

	public boolean checkInternet() {
		netinfo = nw.getActiveNetworkInfo();
		if (netinfo != null && netinfo.isAvailable()) {
			return true;
		}
		return false;
	}

	public int getReplyCount() {
		return 1;
	}
	
	private class updateTimeTask extends TimerTask {

		@Override
		public void run() {
			System.out.println("run");
			try{
				setUpNotification(1);
			} catch(Exception e){
				
			}
		}

	}

}
