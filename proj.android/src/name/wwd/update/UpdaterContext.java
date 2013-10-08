package name.wwd.update;

import java.io.File;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Environment;

public final class UpdaterContext {
	
	public static final String CLIENT_INDEX = "http://121.199.27.213:81//Master/client/index";
	
	public static final String DEVICE_ACTION = "http://106.187.52.13:8080/WWLAST/update/DeviceAction";

	 /**
     * 网络是否可用
     * @return
     */
    public static boolean isNetworkAvailable(Context context) {
    	ConnectivityManager cManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
    	NetworkInfo nInfo = cManager.getActiveNetworkInfo();
    	if(nInfo != null) {
    		return nInfo.isAvailable();
    	}
    	return false;
    }
    
    /**
     * 外部存储是否可用
     * @return
     */
    public static boolean isExternalStorageAvailable() {
    	String state = Environment.getExternalStorageState();
    	if (Environment.MEDIA_MOUNTED.equals(state) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
            return true;
        } else {
            return false;
        }
    }
    
    /**
     * WIFI是否可用
     * @param context
     * @return
     */
    public static boolean isWIFIAvailable(Context context) { 
    	ConnectivityManager mConnectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE); 
    	NetworkInfo mWiFiNetworkInfo = mConnectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI); 
    	if (mWiFiNetworkInfo != null) { 
    		return mWiFiNetworkInfo.isAvailable(); 
    	} 
    	return false;
    }
    
    public static String getNetworkInfo(Context context) {
    	 ConnectivityManager cManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
         NetworkInfo networkInfo = cManager.getActiveNetworkInfo();
         if (networkInfo != null) {
         	String connectivityType = networkInfo.getTypeName();
         	String extraInfo = networkInfo.getExtraInfo();
            return connectivityType + "--" + extraInfo;
         } else {
 			return "null networkInfo";
 		}
    }
    
    /**
     * 打开本地安装文件
     * @param context
     */
    public static void openAPKFileIntent(Context context) {
    	Intent intent = new Intent();
		intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		intent.setAction(android.content.Intent.ACTION_VIEW);
		File SDDir = Environment.getExternalStorageDirectory();
		File apkFile = new File(SDDir, Updater.apkFileName);
		intent.setDataAndType(Uri.fromFile(apkFile), "application/vnd.android.package-archive");
		context.startActivity(intent);
    }
    
    public static int getVersionCode(Context context) {
    	PackageManager packageManager = context.getPackageManager();
    	String packageName = context.getPackageName();
    	try {
			PackageInfo packageInfo = packageManager.getPackageInfo(packageName, PackageManager.GET_CONFIGURATIONS);
			return packageInfo.versionCode;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return 0;
    }
    
    public static String getVersionName(Context context) {
    	PackageManager packageManager = context.getPackageManager();
    	String packageName = context.getPackageName();
    	try {
			PackageInfo packageInfo = packageManager.getPackageInfo(packageName, PackageManager.GET_CONFIGURATIONS);
			return packageInfo.versionName;
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return "";
    }
//    
//    public static boolean isUpdating(Context context) {
//    	SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//    	return preferences.getBoolean("isUpdating", false);
//    }
//    
//    public static void saveIsUpdating(Context context, boolean isUpdating) {
//    	SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//    	preferences.edit().putBoolean("isUpdating", isUpdating).commit();
//    }
    
//    public static int getHasReadedSize(Context context) {
//		SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//		return preferences.getInt("hasReadedSize", 0);
//	}
//	
//    public static void saveHasReadedSize(Context context, int hasReadedSize) {
//		SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//		preferences.edit().putInt("hasReadedSize", hasReadedSize).commit();
//	}
//    
//    public static int getFileSize(Context context) {
//    	SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//		return preferences.getInt("fileSize", 0);
//    }
//    
//    public static void saveFileSize(Context context, int fileSize) {
//		SharedPreferences preferences = context.getSharedPreferences("update", Context.MODE_PRIVATE);
//		preferences.edit().putInt("fileSize", fileSize).commit();
//	}
}
