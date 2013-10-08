package name.wwd.update;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.SocketTimeoutException;
import java.net.URL;
import java.net.URLEncoder;
import java.util.HashMap;
import java.util.Map;

import org.apache.commons.io.IOUtils;

public final class HTTP {
	
	public static final int ConnectTimeout = 30 * 1000;
	public static final int ReadTimeout = 30 * 1000;
	
	private static final String UTF8 = "UTF-8";
	
	public static String getURL(String uri, Map<String, String> httpParams) throws UnsupportedEncodingException {
		StringBuilder stringBuilder = new StringBuilder(uri);
		if (httpParams != null && !httpParams.isEmpty()) {
			stringBuilder.append("?");
			for (Map.Entry<String, String> entry : httpParams.entrySet()) {
				stringBuilder.append(entry.getKey()).append("=")
						.append(URLEncoder.encode(entry.getValue(), UTF8))
						.append("&");
			}
			stringBuilder.deleteCharAt(stringBuilder.length() - 1);
		}
		return stringBuilder.toString();
	}

	public static Object[] GET(String uri, Map<String, String> httpParams) {
		HttpURLConnection connection = null;
		long begin = System.currentTimeMillis();
		System.out.println("begin：" + begin);
		Object[] objects = { HttpURLConnection.HTTP_OK, null };
		try {
			String spec = getURL(uri, httpParams);
			URL url = new URL(spec);
			connection = (HttpURLConnection) url.openConnection();
			connection.setConnectTimeout(ConnectTimeout);
			connection.setReadTimeout(ReadTimeout);
			objects[0] = connection.getResponseCode();
			objects[1] = IOUtils.toString(connection.getInputStream());
			return objects;
		} catch (IOException e) {
			objects[1] = "连接错误";
			if ((Integer) objects[0] == HttpURLConnection.HTTP_OK) {
				objects[0] = HttpURLConnection.HTTP_BAD_REQUEST;
			}
			if ((Integer) objects[0] == HttpURLConnection.HTTP_CLIENT_TIMEOUT) {
				objects[1] = "连接超时";
			}
			if (e instanceof SocketTimeoutException) {
				objects[0] = HttpURLConnection.HTTP_REQ_TOO_LONG;
				objects[1] = "连接超时";
			}
			e.printStackTrace();
			return objects;
		} finally {
			if (connection != null) {
				connection.disconnect();
			}
			long end = System.currentTimeMillis();
			System.out.println("end：" + end);
			System.out.println("total：" + (end - begin));
		}
	}

	
	public static String POST(String spec, HashMap<String, String> httpParams) {
		StringBuilder stringBuilder = new StringBuilder();
		if(httpParams != null && !httpParams.isEmpty()){
			for (Map.Entry<String, String> entry : httpParams.entrySet()) {
				stringBuilder.append(entry.getKey()).append("=").append(entry.getValue()).append("&");
			}
			stringBuilder.deleteCharAt(stringBuilder.length()-1);
		}
		byte[] entityData = stringBuilder.toString().getBytes();
		
		HttpURLConnection conn = null;
		OutputStream output = null;
		InputStream input = null;
		
		try {
			URL url = new URL(spec);
			conn = (HttpURLConnection) url.openConnection();
			conn.setRequestMethod("POST");
			conn.setReadTimeout(10*1000);
			conn.setDoOutput(true);
			conn.setRequestProperty("Content-Type","application/x-www-form-urlencoded");
			conn.setRequestProperty("Content-Length", Integer.toString(entityData.length));
			output = conn.getOutputStream();
			output.write(entityData);
			output.flush();
			input = conn.getInputStream();
			return IOUtils.toString(input);
		} catch (MalformedURLException e) {
			e.printStackTrace();
			return null;
		} catch (ProtocolException e) {
			e.printStackTrace();
			return null;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		} finally {
			if (output != null) {
				try {
					output.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			IOUtils.closeQuietly(input);
			if (conn != null) {
				conn.disconnect();
			}
		}
	}
	
}
