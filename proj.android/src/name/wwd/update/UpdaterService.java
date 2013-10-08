package name.wwd.update;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.RandomAccessFile;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.DecimalFormat;

import com.itita.dev.R;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.os.AsyncTask;
import android.os.AsyncTask.Status;
import android.os.Environment;
import android.os.IBinder;
import android.widget.RemoteViews;


public class UpdaterService extends Service 
{
	private static final String tempFileName = "erzhanqianxian.temp";
	
	private static final int NOTIFY_ID = 0;
	
	private File ExternalStorageDir;
	private long fileSize = Integer.MAX_VALUE;
    private long hasReadedSize = 0;

    private NotificationManager mNotificationManager;  
    private Notification mNotification;  
    
    private GetLatestTask task;
    
    @Override  
    public void onCreate() {  
        super.onCreate();
        System.out.println("---update service create---");
        ExternalStorageDir = Environment.getExternalStorageDirectory();
        IntentFilter filter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
        registerReceiver(connectivityChange, filter);
        mNotificationManager = (NotificationManager) getSystemService(android.content.Context.NOTIFICATION_SERVICE);
    }  
    
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
    	System.out.println("---update service start command---");
    	startUpdate();
    	return super.onStartCommand(intent, flags, startId);
    }
    
	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

    @Override  
    public void onDestroy() {  
        super.onDestroy(); 
        unregisterReceiver(connectivityChange);
        ClientIndex.isUpdating = false;
        System.out.println("---stop update service---");
    }  
    private void createNotification() 
    {
        int icon = R.drawable.ic_wwicon;  
        String tickerText = "二战前线开始更新";  
        long when = System.currentTimeMillis();  
        mNotification = new Notification(icon, tickerText, when);  
  
        // 放置在"正在运行"栏目中   
        mNotification.flags = Notification.FLAG_ONGOING_EVENT;  
  
        RemoteViews contentView = new RemoteViews(getPackageName(), R.layout.notification_download);  
        // 指定个性化视图   
        mNotification.contentView = contentView;  
        
        Intent intent = new Intent(this, Updater.class);  
        PendingIntent contentIntent = PendingIntent.getActivity(this, 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);  
        mNotification.contentIntent = contentIntent;  
    	// 最后别忘了通知一下,否则不会更新   
        mNotificationManager.notify(NOTIFY_ID, mNotification);  
    }  
    
	private void startUpdate() {
		if (task == null || task.isCancelled()) {//启动更新
			task = new GetLatestTask();
			createNotification();
            task.execute(ClientIndex.getInstance().updateContent.latestApkUrl);
            ClientIndex.isUpdating = true;
		}
	}
	
	private void showUpdateProgress() {
		RemoteViews contentView = mNotification.contentView;
    	contentView.setProgressBar(R.id.pbDownloading, (int)fileSize, (int)hasReadedSize, false); 
    	if (fileSize == hasReadedSize) {
    		contentView.setTextViewText(R.id.tvMessage, "更新完成");
    		
    		File tempFile = new File(ExternalStorageDir, tempFileName);
    		File apkFile = new File(ExternalStorageDir, Updater.apkFileName);
    		tempFile.renameTo(apkFile);
    		
    		mNotification.flags = Notification.FLAG_AUTO_CANCEL;
        	mNotificationManager.cancel(NOTIFY_ID);
        	UpdaterContext.openAPKFileIntent(this);
        	stopSelf();
    	} else {
    		float percent = hasReadedSize / (float) fileSize;
        	String percentStr = new DecimalFormat("0.00%").format(percent);
        	contentView.setTextViewText(R.id.tvMessage, "更新中（" + percentStr + "）");
        	mNotification.flags = Notification.FLAG_ONGOING_EVENT; 
        	mNotificationManager.notify(NOTIFY_ID, mNotification);
    	}
    	sendProgress();
	}
	
	private void onConnectivityBreak() {
//		Toast.makeText(this, "网络连接中断···", Toast.LENGTH_SHORT).show();
		System.out.println("重连····");
		if (task != null && task.getStatus() == Status.RUNNING) {
			task.cancel(true);
		}
//		mNotificationManager.cancel(NOTIFY_ID);
		
		startUpdate();
		
//		stopSelf();
	}
	
	private void sendProgress() {
		Intent intentDownloading = new Intent(Updater.UPDATER_SERVICE);
    	intentDownloading.putExtra("fileSize", fileSize);
    	intentDownloading.putExtra("hasReadedSize", hasReadedSize);
        sendBroadcast(intentDownloading);
	}
	
	public final class GetLatestTask extends AsyncTask<String, Void, Void> {
		@Override
		protected Void doInBackground(String... strings) {
			File tempFile = null;
			RandomAccessFile accessFile = null;
			HttpURLConnection connection = null;
			try {
				tempFile = new File(ExternalStorageDir, tempFileName);
				if (!tempFile.exists()) {
					tempFile.createNewFile();
				}
				hasReadedSize = tempFile.length();
				System.out.println("hasReadedSize：" + hasReadedSize);
				
				accessFile = new RandomAccessFile(tempFile, "rwd");
				accessFile.seek(hasReadedSize);
				
				URL url = new URL(strings[0]);
				connection = (HttpURLConnection) url.openConnection();
				connection.setConnectTimeout(HTTP.ConnectTimeout);
				connection.setReadTimeout(HTTP.ReadTimeout);
				connection.setRequestProperty("RANGE", "bytes=" + hasReadedSize + "-");
				InputStream input = connection.getInputStream();
				
				long notReadedSize = Long.parseLong(connection.getHeaderField("Content-Length"));
				fileSize = hasReadedSize + notReadedSize;
				
				byte buffer[] = new byte[1024*32];
				int res = -1;
				int timer = 0;
				System.out.println(hasReadedSize + "/" + fileSize + "has downloaded!!!");
				publishProgress();
				while((res = input.read(buffer, 0, buffer.length)) != -1) {
					accessFile.write(buffer, 0, res);
					hasReadedSize = hasReadedSize + res;
					++timer;
					if(timer % 10 == 0) {
						System.out.println(hasReadedSize + "/" + fileSize + "has downloaded!!!");
						publishProgress();
					}
					if (isCancelled()) {
						break;
					}
				}
				System.out.println(hasReadedSize + "/" + fileSize + "has downloaded!!!");
			} catch (IOException e) {
				onConnectivityBreak();
				e.printStackTrace();
			} finally {
				try {
					if(accessFile != null) {
						accessFile.close();
					}
					if(connection != null) {
						connection.disconnect();
					}
					connection = null;
					accessFile = null;
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return null;
		}
		
		@Override
		protected void onProgressUpdate(Void... values) {
			super.onProgressUpdate(values);
			showUpdateProgress();
		}
		
		@Override
		protected void onCancelled() {
			super.onCancelled();
			System.out.println("get latest task canceled");
		}

		@Override
		protected void onPostExecute(Void result) {
			super.onPostExecute(result);
			System.out.println("get latest task post execute");
			showUpdateProgress();
		}
	}
	
	private BroadcastReceiver connectivityChange =  new  BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			if (intent.getAction().equals(ConnectivityManager.CONNECTIVITY_ACTION)) {
				boolean isBreak = intent.getBooleanExtra(ConnectivityManager.EXTRA_NO_CONNECTIVITY, false); 
                System.out.println("net is break?" + isBreak);
                if (isBreak) {
                	onConnectivityBreak();
                } else {
                	startUpdate();
                }
			}
		}
	};
}
