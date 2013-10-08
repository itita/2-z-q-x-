package com.itita.ww2;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.UUID;

import name.wwd.update.PurchaseActivity;

import org.apache.commons.lang3.StringUtils;
import org.apache.http.protocol.HTTP;
import org.apache.http.util.ByteArrayBuffer;
import org.apache.http.util.EncodingUtils;
import org.cocos2dx.lib.Cocos2dxActivity;

import com.itita.ww.javatoc;
//import com.itita.gamealipay.MainActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.widget.Toast;

public class Util {

	public static String deviceId = "";

	public static Activity context;

	public static Handler publicHand;

	public static void moveAssetsFile2SDCard(Context context, String fileName)
			throws IOException {
		String sdCardRoot = Environment.getExternalStorageDirectory() + "/";
		String sdCardFileName = sdCardRoot + fileName;

		InputStream inputStream = context.getAssets().open(fileName);

		File sdCardFile = new File(sdCardFileName);
		if (!sdCardFile.exists()) {
			sdCardFile.createNewFile();
		} else {
			return;
		}
		OutputStream outputStream = new FileOutputStream(sdCardFile);
		int bytesRead = 0;
		byte[] buffer = new byte[8192];
		while ((bytesRead = inputStream.read(buffer, 0, 8192)) != -1) {
			outputStream.write(buffer, 0, bytesRead);
		}
		outputStream.close();
		inputStream.close();
	}

	public static String getDeviceId() {
		Log.i(deviceId, "第一次亲密接触" + deviceId);
		if (deviceId != null) {
			return deviceId;
		}
		return "deviceNotFound";
	}

	public static void showMessage() {

		publicHand.post(new Runnable() {
			public void run() {
				Toast.makeText(context, "再次点击返回登陆界面", Toast.LENGTH_SHORT).show();
			}
		});
	}

	public static void toShow() {
		// Intent intent = new Intent(context, Comments.class);
		// context.startActivity(intent);
		Intent it = new Intent(Intent.ACTION_VIEW,
				Uri.parse("http://17erzhan.com"));
		it.setClassName("com.android.browser",
				"com.android.browser.BrowserActivity");
		context.startActivity(it);
	}

	public static void toSetting() {
		context.startActivity(new Intent(Settings.ACTION_WIRELESS_SETTINGS));
	}

	public static String getResponse(String urlString) {
		try {
			URL url = new URL(urlString);
			URLConnection connection = url.openConnection();
			InputStream is = connection.getInputStream();
			BufferedInputStream bis = new BufferedInputStream(is);
			ByteArrayBuffer buffer = new ByteArrayBuffer(32);
			int read = 0;
			while ((read = bis.read()) != -1) {
				buffer.append((char) read);
			}
			return EncodingUtils.getString(buffer.toByteArray(), HTTP.UTF_8);
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return "connect error";
	}

	public static String getItitaChanael() {
		ApplicationInfo appi = null;
		try {
			appi = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);
			String value = appi.metaData.getString("ititaChannel");
			if (StringUtils.isNotEmpty(value)) {
				Log.e("ititaChannel", "ititaChannel:" + value);
				return value;
			}
			return "local";
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		return "local";
	}

	public static void toHome() {
		Intent intent = new Intent(Intent.ACTION_MAIN);
		intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);// 注意
		intent.addCategory(Intent.CATEGORY_HOME);
		context.startActivity(intent);
		Log.e("ww2", "返回桌面了");
	}

	public static void toPuchase(int userId, int serverId, int channelId) {
		// Intent intent = new Intent(context, MainActivity.class);
		// //Bundle类用作携带数据，它类似于Map，用于存放key-value名值对形式的值
		// Bundle b = new Bundle();
		// b.putString("userId", userId+"");
		// b.putString("serverId", serverId+"");
		// b.putString("channelId", channelId+"");
		// //此处使用putExtras，接受方就响应的使用getExtra
		// intent.putExtras( b );
		// context.startActivity(intent);
		// System.out.println("userId:"+userId+"serverId:"+serverId+"channelId:"+channelId);

	}

	public static String getDisplayWidth() {
		DisplayMetrics dm = new DisplayMetrics();
		context.getWindowManager().getDefaultDisplay().getMetrics(dm);
		// 得到手机屏幕高度：
		if (dm.heightPixels > dm.widthPixels) {
			return dm.heightPixels + "";
		} else {
			return dm.widthPixels + "";
		}
	}

	public static String getDisplayHeight() {
		DisplayMetrics dm = new DisplayMetrics();
		context.getWindowManager().getDefaultDisplay().getMetrics(dm);
		// 得到手机屏幕高度：
		if (dm.heightPixels < dm.widthPixels) {
			return dm.heightPixels + "";
		} else {
			return dm.widthPixels + "";
		}
	}

	public static void init() {
//		initSDK();
//		NdToolBar toolBar = NdToolBar.create(context,
//				NdToolBarPlace.NdToolBarTopRight);
//		toolBar.show();
	}

	// public static final int appID_91Bean = 101677;//91豆的测试appID
	// public static final String appKEY_91Bean =
	// "dc5deaed07fc48e11e5ec1828d2d1f5308ff2d87ffed47b3";

	/**
	 * 初始化91SDK
	 */
	private static void initSDK() {
//		if (isDebugMode(context)) {
//			NdCommplatform.getInstance().ndSetDebugMode(0);// 设置调试模式
//		}
//
//		NdCommplatform.getInstance().ndSetScreenOrientation(
//				NdCommplatform.SCREEN_ORIENTATION_AUTO);
//
//		// mOnInitCompleteListener =
//
//		NdAppInfo appInfo = new NdAppInfo();
//		appInfo.setCtx(context);
//		appInfo.setAppId(101677);// 应用ID
//		appInfo.setAppKey("dc5deaed07fc48e11e5ec1828d2d1f5308ff2d87ffed47b3");// 应用Key
//		/*
//		 * NdVersionCheckLevelNormal 版本检查失败可以继续进行游戏 NdVersionCheckLevelStrict
//		 * 版本检查失败则不能进入游戏 默认取值为NdVersionCheckLevelStrict
//		 */
//		appInfo.setNdVersionCheckStatus(NdAppInfo.ND_VERSION_CHECK_LEVEL_STRICT);
//
//		// 初始化91SDK
//		NdCommplatform.getInstance().ndInit(context, appInfo,
//				new OnInitCompleteListener() {
//
//					@Override
//					protected void onComplete(int ndFlag) {
//						switch (ndFlag) {
//						case OnInitCompleteListener.FLAG_NORMAL:
//							// initActivity(); // 初始化自己的游戏
//							break;
//						case OnInitCompleteListener.FLAG_FORCE_CLOSE:
//						default:
//							// 如果还有别的Activity或资源要关闭的在这里处理
//							break;
//						}
//					}
//
//				});

	}

	/**
	 * 91帐号登录
	 * 
	 */
	private static void accountLogin() {

//		publicHand.post(new Runnable() {
//			public void run() {
//				NdCommplatform.getInstance().ndLogin(context,
//						new NdMiscCallbackListener.OnLoginProcessListener() {
//
//							@Override
//							public void finishLoginProcess(int code) {
//								String tip = "";
//								int userId = -1;
//								// 登录的返回码检查
//								if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
//									tip = "登录成功";
//									// 账号登录成功，测试可用初始化玩家游戏数据
//									userId = Integer.parseInt(NdCommplatform
//											.getInstance().getLoginUin());
//									// 有购买漏单的此时可向玩家补发相关的道具
//								} else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL) {
//									tip = "取消登录";
//									userId = -2;
//								} else {
//									tip = "登录失败";
//								}
//								new javatoc().thirdlogincallback(userId);
//								// Log.e("userid", ""+userId);
//								Toast.makeText(context, tip, Toast.LENGTH_SHORT)
//										.show();
//							}
//						});
//			}
//		});
	}

	/**
	 * 游客登录
	 * 
	 */
	private static void guestLogin() {
//		publicHand.post(new Runnable() {
//			public void run() {
//				NdCommplatform.getInstance().ndLoginEx(context,
//						new NdMiscCallbackListener.OnLoginProcessListener() {
//
//							@Override
//							public void finishLoginProcess(int code) {
//								String tip = "";
//								int userId = -1;
//								// 登录的返回码检查
//								if (code == NdErrorCode.ND_COM_PLATFORM_SUCCESS) {
//									if (NdCommplatform.getInstance()
//											.ndGetLoginStatus() == NdLoginStatus.AccountLogin) {// 账号登录
//										// 账号登录成功，此时可用初始化玩家游戏数据
//										tip = "账号登录成功";
//										userId = Integer
//												.parseInt(NdCommplatform
//														.getInstance()
//														.getLoginUin());
//									} else if (NdCommplatform.getInstance()
//											.ndGetLoginStatus() == NdLoginStatus.GuestLogin) {// 游客登录
//										// 游客登录成功，此时可获取玩家的游客UIN做为保存游戏数据的标识，玩家游客账号转正后该UIN不变。
//										tip = "游客登录成功";
//										userId = Integer
//												.parseInt(NdCommplatform
//														.getInstance()
//														.getLoginUin());
//									}
//
//								} else if (code == NdErrorCode.ND_COM_PLATFORM_ERROR_CANCEL) {
//									tip = "取消账号登录";
//									userId = -2;
//								} else if (code == NdErrorCode.ND_COM_GUEST_OFFICIAL_SUCCESS) {
//									tip = "游客转正成功";
//								} else {
//									tip = "登录失败";
//								}
//								new javatoc().thirdlogincallback(userId);
//								Toast.makeText(context, tip, Toast.LENGTH_SHORT)
//										.show();
//							}
//						});
//			}
//		});

	}

	private static void accountloginout() {
//		publicHand.post(new Runnable() {
//			public void run() {
//				NdCommplatform.getInstance().ndLogout(
//						NdCommplatform.LOGOUT_TO_RESET_AUTO_LOGIN_CONFIG,
//						context);
//			}
//		});
	}
	
	private static void showexit() {

//		publicHand.post(new Runnable() {
//			public void run() {
//
//				NdCommplatform.getInstance().ndExit(
//						new OnExitCompleteListener(context) {
//							@Override
//							public void onComplete() {
//								// TODO Auto-generated method stub
//								Toast.makeText(context, "退出二战前线",
//										Toast.LENGTH_LONG).show();
//								context.finish();
//							}
//						});
//			}
//		});
	}

	/**
	 * 进入代币充值界面
	 */
	// private void recharge() {
	// String coin = "0";
	// UUID guid = UUID.randomUUID();
	// String cooOrderSerial = guid.toString();
	// cooOrderSerial = cooOrderSerial.replace("-", "".trim());
	// NdCommplatform.getInstance().ndUniPayForCoin(cooOrderSerial,
	// Integer.parseInt(coin), null, context);
	// }
	//
	
	// 退出提示

	public static void QuitShow() {
		showexit();
	}

	// 快速登陆

	public static void QuickLogin() {
		guestLogin();
	}

	// 登陆
	public static void Loginin() {
		accountLogin();
	}

	// 注销
	public static void Loginout() {
		accountloginout();
	}

	// 支付
	public static void Payout() {
		// ctx.recharge();
	}

	private static final int MODE = Context.MODE_APPEND;// _PRIVATE;
	private static final String fileName = "91erzhan";

	private static SharedPreferences readPreferences(Context ctx) {
		return ctx.getSharedPreferences(fileName, MODE);
	}

	private static SharedPreferences.Editor editPreferences(Context ctx) {
		SharedPreferences settings = readPreferences(ctx);
		return settings.edit();
	}

	/**
	 * 保存需要初始化的应用类型
	 * 
	 * @param ctx
	 * @param md5Code
	 * @return
	 */
	public static boolean setAppType(Context ctx, int app) {
		try {
			SharedPreferences.Editor editor = editPreferences(ctx);
			editor.putInt("app", app);
			editor.commit();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}

	/**
	 * 获取需要初始化的应用类型
	 * 
	 * @param ctx
	 * @return
	 */
	public static int getAppType(Context ctx) {
		return readPreferences(ctx).getInt("app", 0);
	}

	/**
	 * 保存DEBUG模式类型
	 * 
	 * @param ctx
	 * @param md5Code
	 * @return
	 */
	public static boolean setDebugMode(Context ctx, boolean debugMode) {
		try {
			SharedPreferences.Editor editor = editPreferences(ctx);
			editor.putBoolean("debugMode", debugMode);
			editor.commit();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return false;
	}

	/**
	 * 获取需要初始化的应用类型
	 * 
	 * @param ctx
	 * @return
	 */
	public static boolean isDebugMode(Context ctx) {
		return readPreferences(ctx).getBoolean("debugMode", false);
	}

}
