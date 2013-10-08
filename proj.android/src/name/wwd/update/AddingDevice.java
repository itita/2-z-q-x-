package name.wwd.update;

import java.util.HashMap;

import android.app.Activity;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;

/**
 * 向服务器发送设备信息
 * @author WangWeiDang
 *
 */
public class AddingDevice extends AsyncTask<Void, Void, Void> {
	
	private Activity mActivity;
	public AddingDevice(Activity pActivity) {
		super();
		this.mActivity = pActivity;
	}

	@Override
	protected Void doInBackground(Void... params) {
		
		HashMap<String, String> httpParams = new HashMap<String, String>();
		
		TelephonyManager telephonyManager = (TelephonyManager) mActivity.getSystemService(Context.TELEPHONY_SERVICE);
		httpParams.put("deviceId", telephonyManager.getDeviceId());
		httpParams.put("phoneNumber", telephonyManager.getLine1Number());
		
		DisplayMetrics metrics = new DisplayMetrics();
		mActivity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
        httpParams.put("resolution", metrics.widthPixels + "*" + metrics.heightPixels);
        
        httpParams.put("model", Build.MODEL);
        httpParams.put("release", Build.VERSION.RELEASE);
        
        httpParams.put("board", Build.BOARD);
        httpParams.put("brand", Build.BRAND);
        httpParams.put("cpuabi", Build.CPU_ABI);
        httpParams.put("device", Build.DEVICE);
        httpParams.put("display", Build.DISPLAY);
        httpParams.put("fingerprint", Build.FINGERPRINT);
        httpParams.put("host", Build.HOST);
        httpParams.put("id", Build.ID);
        httpParams.put("manufacturer", Build.MANUFACTURER);
        httpParams.put("product", Build.PRODUCT);
        httpParams.put("tags", Build.TAGS);
        httpParams.put("type", Build.TYPE);
        httpParams.put("user", Build.USER);
        httpParams.put("codename", Build.VERSION.CODENAME);
        httpParams.put("incremental", Build.VERSION.INCREMENTAL);
        httpParams.put("sdk", Build.VERSION.SDK);
        httpParams.put("sdkInt", Build.VERSION.SDK_INT+"");
        
        httpParams.put("versionCode", UpdaterContext.getVersionCode(mActivity)+"");
        httpParams.put("versionName", UpdaterContext.getVersionName(mActivity));
        httpParams.put("networkInfo", UpdaterContext.getNetworkInfo(mActivity));
		HTTP.POST(UpdaterContext.DEVICE_ACTION, httpParams);
		return null;
	}
}
