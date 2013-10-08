package name.wwd.update;

import java.io.File;
import java.io.IOException;
import java.net.HttpURLConnection;
import java.text.DecimalFormat;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import name.wwd.update.ClientIndex.AndroidCrackers;

import org.apache.commons.lang3.StringUtils;
import org.json.JSONException;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.graphics.drawable.BitmapDrawable;
import android.net.ConnectivityManager;
import android.os.Bundle;
import android.os.Environment;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.itita.dev.R;
import com.itita.wwdz.WW14;

public class Updater extends Activity {
	
	public static final String apkFileName = "erzhanqianxian.apk";
	
	public static final String UPDATER_SERVICE = "WWD_UPDATER_SERVICE";
	
	File ExternalStorageDir;
	int versionCode;
	String packageName;
	String ititaChannel = "local";
	
	protected RelativeLayout rlUpdater;
	
	protected RelativeLayout rlDownloading;
	protected TextView tvInstrunciton;
	protected TextView tvTitle;
	protected ProgressBar pbDownloading;
	
	UpdaterReceiver mUpdaterReceiver = null;
	
	AlertDialog.Builder updateDialog = null;

    @Override
    public void onCreate(Bundle savedInstanceState) {
    	setContentView(R.layout.activity_updater);
        super.onCreate(savedInstanceState);
        
        initView();
        
        getInfo();
        
        mUpdaterReceiver = new UpdaterReceiver();
		IntentFilter mFilter = new IntentFilter(UPDATER_SERVICE);
		registerReceiver(mUpdaterReceiver, mFilter);
		IntentFilter filter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
	    registerReceiver(connectivityChange, filter);
	    // TODO 先不用记录设备信息
//		new AddingDevice(this).execute();
    }
    
    @Override
    protected void onResume() {
    	super.onResume();
    	if (!UpdaterContext.isExternalStorageAvailable() && UpdaterContext.isNetworkAvailable(this)) {
    		System.out.println("---external storage is not available---");
    		onClientIndex();
    	} else if(hasLocalLatest()) {//本地存在最新安装包，先提示安装
    		System.out.println("---has local latest---");
    		showInstallDialog();
    	} else if(UpdaterContext.isNetworkAvailable(this)) {//网络连接可用
    		System.out.println("---network is available---");
    		if (ClientIndex.isUpdating) {
    			System.out.println("---continue to the last update---");
    			startUpdate(true);
    		} else {
    			onClientIndex();
    		}
    	} else {
    		startGame();
    	}
    }
    
    private void onClientIndex() {
    	HashMap<String, String> httpParams = new HashMap<String, String>();
		httpParams.put("source", "android");
        httpParams.put("channlePackageName", packageName);
        httpParams.put("versionCode", Integer.toString(versionCode));
        httpParams.put("ititaChannel", ititaChannel);
        new ClientIndexTask(UpdaterContext.CLIENT_INDEX, httpParams).execute();
    }
    
    @Override
    protected void onDestroy() {
    	super.onDestroy();
    	unregisterReceiver(mUpdaterReceiver);
    	unregisterReceiver(connectivityChange);
    }
    
    private void initView() {
    	 rlUpdater = (RelativeLayout) findViewById(R.id.rlUpdater);
         BitmapDrawable drawable = null;
 		 try {
 			drawable = new BitmapDrawable(getAssets().open("loading.jpg"));
 			rlUpdater.setBackgroundDrawable(drawable);
 		 } catch (IOException e) {
 			e.printStackTrace();
 		 }
         rlDownloading = (RelativeLayout) findViewById(R.id.rlDownloading);
         tvInstrunciton = (TextView) findViewById(R.id.tvInstrunciton);
         tvInstrunciton.setMovementMethod(ScrollingMovementMethod.getInstance());
         tvInstrunciton.setScrollbarFadingEnabled(false);
         tvTitle = (TextView) findViewById(R.id.tvTitle);
         pbDownloading = (ProgressBar) findViewById(R.id.pbDownloading);
    }

    private void getInfo() {
    	packageName = getPackageName();
		versionCode = UpdaterContext.getVersionCode(this);
		System.out.println("packageName:" + packageName);
		System.out.println("versionCode:" + versionCode);
		ExternalStorageDir = Environment.getExternalStorageDirectory();
		System.out.println("ExternalStorageDir:" + ExternalStorageDir.getPath());
		
		getItitaChanael();
		System.out.println("ititaChannel:" + ititaChannel);
    }
    
    private void getItitaChanael() {
		ApplicationInfo appi = null;
		try {
			appi = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
			String value = appi.metaData.getString("ititaChannel");
			if(StringUtils.isNotEmpty(value)) {
				ititaChannel =  value;
			}
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
	}
    
    private void startUpdate(boolean isNecessary) {
    	if (isNecessary) {
    		if(UpdaterContext.isWIFIAvailable(this)) {
    			Intent intentService = new Intent(Updater.this, UpdaterService.class);
    			startService(intentService);
        	} else {
        		showUpdateDialog(isNecessary, ClientIndex.getInstance().updateContent.instrunciton);
        	}
    	} else {
    		showUpdateDialog(isNecessary, ClientIndex.getInstance().updateContent.instrunciton);
    	}
    }
    
    private void showErrorDialog(String message) {
    	AlertDialog.Builder	dialog = new AlertDialog.Builder(this); 
    	dialog.setTitle("程序提醒");
    	dialog.setMessage(message);
    	DialogInterface.OnClickListener cancelListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
					dialog.dismiss();
					finish();
			}
		};
		dialog.setNegativeButton("退出程序", cancelListener);
    	DialogInterface.OnClickListener confirmListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				dialog.dismiss();
				onClientIndex();
			}
		};
		dialog.setPositiveButton("再试一次", confirmListener);
		dialog.setCancelable(false);
		dialog.show();
    }
    
    private void showUpdateDialog(final boolean isNecessary, final String instrunciton) {
    	if (updateDialog == null) {
    		updateDialog = new AlertDialog.Builder(this); 
    	}
    	updateDialog.setTitle("更新提醒");
    	if (isNecessary) {
    		updateDialog.setMessage(instrunciton + "\n（本轮更新不能跳过）\n");
    	} else {
    		updateDialog.setMessage(instrunciton + "\n（可以跳过本次更新）\n");
    	}
    	
    	DialogInterface.OnClickListener cancelListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				if (isNecessary) {
					dialog.dismiss();
					finish();
				} else {
					checkApp();
				}
			}
		};
		updateDialog.setNegativeButton("取消更新", cancelListener);
    	DialogInterface.OnClickListener confirmListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				dialog.dismiss();
				Intent intentService = new Intent(Updater.this, UpdaterService.class);
				startService(intentService);
			}
		};
		updateDialog.setPositiveButton("开始更新", confirmListener);
		updateDialog.setCancelable(false);
		updateDialog.setOnCancelListener(new OnCancelListener() {
			@Override
			public void onCancel(DialogInterface dialog) {
				finish();
			}
		});
		updateDialog.show();
    }
    
    private void showInstallDialog() {
    	AlertDialog.Builder dialog = new AlertDialog.Builder(this);
    	dialog.setTitle("更新提醒");
    	dialog.setMessage("最新的更新包已存在，请先安装！");
    	DialogInterface.OnClickListener cancelListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				finish();
			}
		};
    	dialog.setNegativeButton("取消", cancelListener);
    	DialogInterface.OnClickListener confirmListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				UpdaterContext.openAPKFileIntent(Updater.this);
			}
		};
		dialog.setPositiveButton("现在安装", confirmListener);
		dialog.setCancelable(false);
		dialog.setOnCancelListener(new OnCancelListener() {
			@Override
			public void onCancel(DialogInterface dialog) {
				finish();
			}
		});
		dialog.show();
    }
    
    private void showBlackAppDialog(String appName) {
    	AlertDialog.Builder dialog = new AlertDialog.Builder(this);
    	dialog.setTitle("手机环境提示");
    	dialog.setMessage("你的手机安装有游戏修改器：" + appName + "，请先卸载。谢谢合作！！！");
    	DialogInterface.OnClickListener confirmListener = new DialogInterface.OnClickListener() {
			@Override
			public void onClick(DialogInterface dialog, int which) {
				finish();
			}
		};
		dialog.setCancelable(false);
		dialog.setPositiveButton("确定", confirmListener);
		dialog.show();
    }
    
    private void startGame() {
    	if (UpdaterContext.isExternalStorageAvailable()) {
    		ExternalStorageDir = Environment.getExternalStorageDirectory();
    		String archiveFilePath = ExternalStorageDir + File.separator + Updater.apkFileName;
        	File archiveFile = new File(archiveFilePath);
        	if(archiveFile.exists()) {
        		archiveFile.delete();
        	}
    	}
		Intent intentGame = new Intent(this,WW14.class);
		startActivity(intentGame);
		finish();
	}
    
    /**
     * 本地是否有新版本的APK文件
     * @return
     */
    private boolean hasLocalLatest() {
    	System.out.println("check has local latest APK");
    	String archiveFilePath = ExternalStorageDir + File.separator + Updater.apkFileName;
    	File archiveFile = new File(archiveFilePath);
    	if(!archiveFile.exists()) {//没有APK文件
    		return false;
    	}
    	PackageInfo pInfo = null;
		try {
			PackageManager pManager = getPackageManager();
			pInfo = pManager.getPackageArchiveInfo(archiveFilePath, PackageManager.GET_CONFIGURATIONS);
			if(pInfo == null) {
				return false;
			}
		} catch (Exception e) {
			return false;
		}
		
    	String aFilePName = pInfo.packageName;//本地APK文件的包名
    	System.out.println("aFilePName："+aFilePName);
    	int aFileVCode = pInfo.versionCode;//本地APK文件的版本号
    	System.out.println("aFileVCode："+aFileVCode);
    	if(aFilePName != null && aFilePName.equals(packageName) && aFileVCode > versionCode) {
    		System.out.println("has local APK");
    		return true;
    	}
    	return false;
    }
    
    private void checkApp() {
    	tvTitle.setText("正在检测系统配置···");
    	String appName = null;
    	List<AndroidCrackers> crackers = ClientIndex.getInstance().crackers;
		List<ApplicationInfo> applicationInfos = getPackageManager().getInstalledApplications(0);
        for (ApplicationInfo applicationInfo : applicationInfos) {
        	//只监测非系统应用
        	if ((applicationInfo.flags & ApplicationInfo.FLAG_SYSTEM) == 0) {
        		String _packageName = applicationInfo.packageName;
            	String _appName = applicationInfo.loadLabel(getPackageManager()) + "";
            	for (AndroidCrackers cracker : crackers) {
            		if (_packageName.equals(cracker.packageName)) {
            			appName = _appName;
            		}
            	}
        	}
        }
        if (appName != null) {
			showBlackAppDialog(appName);
		} else {
			startGame();
		}
	}
    
    private final class ClientIndexTask extends DoGetTask {
    	public ClientIndexTask(String uri, Map<String, String> httpParams) {
			super(uri, httpParams);
		}
		@Override
		protected void onPreExecute() {
			super.onPreExecute();
			System.out.println("---begin check update---");
			tvTitle.setText("正在检测更新···");
			tvTitle.setVisibility(View.VISIBLE);
		}
		@Override
		protected void onPostExecute(Object[] objects) {
			super.onPostExecute(objects);
			if (objects == null || objects.length != 2 || objects[1] == null) {
				showErrorDialog("应用程序发生错误");
			} else if ((Integer)objects[0] != HttpURLConnection.HTTP_OK) {
				showErrorDialog((String)objects[1]);
			} else {
				String json = (String)objects[1];
				try {
					ClientIndex.initInstance(json);
//					Log.e("进入要看的东东", json);
				} catch (JSONException e) {
					showErrorDialog("应用程序发生错误");
					e.printStackTrace();
					return;
				}
				if (ClientIndex.getInstance().updateContent.needUpdate) {//有最新版，开始更新
					System.out.println("---has network latest---");
					startUpdate(ClientIndex.getInstance().updateContent.mustUpdate);
				} else {
					System.out.println("---has no network latest---");
					checkApp();
				}
			}
		}
    }
    
    private BroadcastReceiver connectivityChange =  new  BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {
			if (intent.getAction().equals(ConnectivityManager.CONNECTIVITY_ACTION)) {
				boolean isBreak = intent.getBooleanExtra(ConnectivityManager.EXTRA_NO_CONNECTIVITY, false); 
                if (isBreak) {
                	tvTitle.setText("网络连接中断");
                }
			}
		}
	};
    
    private void showUpdateProgress(int hasReadedSize, int fileSize) {
    	if (fileSize == hasReadedSize) {
    		tvTitle.setText("更新完成");
    	} else {
    		float percent = hasReadedSize / (float) fileSize;
    		String percentStr = new DecimalFormat("0.00%").format(percent);
        	tvTitle.setText("更新中···（" + percentStr + "）");
    	}
    	rlDownloading.setVisibility(View.VISIBLE);
    	pbDownloading.setVisibility(View.VISIBLE);
    	tvInstrunciton.setVisibility(View.VISIBLE);
    	tvTitle.setVisibility(View.VISIBLE);
    	tvInstrunciton.setText(ClientIndex.getInstance().updateContent.instrunciton);
    	pbDownloading.setMax(fileSize);
    	pbDownloading.setProgress(hasReadedSize);
    }
 
    private class UpdaterReceiver extends BroadcastReceiver {
		@Override
		public void onReceive(Context context, Intent intent) {
			long fileSize = intent.getLongExtra("fileSize", Integer.MAX_VALUE);
			long hasReadedSize = intent.getLongExtra("hasReadedSize", 0L);
			showUpdateProgress((int)hasReadedSize, (int)fileSize);
		}
	}
}

