package name.wwd.update;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;


public class ClientIndex {
	
	public static boolean isUpdating = false;

	public int channelId;
	public UpdateCotent updateContent;
	public List<AndroidCrackers> crackers;
	public List<ServerItems> servers = new ArrayList<ClientIndex.ServerItems>();
	
	private static ClientIndex instance;
	private static String serverInfoStr = null;
	
	public static ClientIndex getInstance() {
		return instance;
	}
	
	public static void initInstance(String json) throws JSONException {
		JSONObject jsonObject = new JSONObject(json);
		instance = new ClientIndex();
		if (jsonObject.has("channelId")) {
			instance.channelId = jsonObject.getInt("channelId");
		}
		if (jsonObject.has("update")) {
			JSONObject jsonUpdate = jsonObject.getJSONObject("update");
			UpdateCotent updateContent = instance.new UpdateCotent();
			if (jsonUpdate.has("needUpdate")) {
				updateContent.needUpdate = jsonUpdate.getBoolean("needUpdate");
			}
			if (jsonUpdate.has("mustUpdate")) {
				updateContent.mustUpdate = jsonUpdate.getBoolean("mustUpdate");
			}
			if (jsonUpdate.has("lastestVersion")) {
				updateContent.lastestVersion = jsonUpdate.getInt("lastestVersion");
			}
			if (jsonUpdate.has("latestApkUrl")) {
				updateContent.latestApkUrl = jsonUpdate.getString("latestApkUrl");
			}
			if (jsonUpdate.has("instrunciton")) {
				updateContent.instrunciton = jsonUpdate.getString("instrunciton");
			}
			instance.updateContent = updateContent;
		}
		if (jsonObject.has("androidCrackers")) {
			JSONArray arrayCracker = jsonObject.getJSONArray("androidCrackers");
			List<AndroidCrackers> crackers = new ArrayList<ClientIndex.AndroidCrackers>();
			for (int i = 0; i < arrayCracker.length(); i++) {
				JSONObject jsonCrackers = arrayCracker.getJSONObject(i);
				AndroidCrackers androidCrackers = instance.new AndroidCrackers();
				if (jsonCrackers.has("packageName")) {
					androidCrackers.packageName = jsonCrackers.getString("packageName");
				}
				if (jsonCrackers.has("name")) {
					androidCrackers.name = jsonCrackers.getString("name");
				}
				crackers.add(androidCrackers);
			}
			instance.crackers = crackers;
		}
		if (jsonObject.has("serverItems")) {
			JSONArray arrayServer = jsonObject.getJSONArray("serverItems");
//			List<ServerItems> servers = new ArrayList<ClientIndex.ServerItems>();
			for (int i = 0; i <arrayServer.length(); i++) {
				JSONObject jsonServer = arrayServer.getJSONObject(i);
				ServerItems serverItems = instance.new ServerItems();
				if (jsonServer.has("serverId")) {
					serverItems.serverId = jsonServer.getInt("serverId");
				}
				if (jsonServer.has("serverName")) {
					serverItems.serverName = jsonServer.getString("serverName");
				}
				if (jsonServer.has("serverStatusId")) {
					serverItems.serverStatusId = jsonServer.getInt("serverStatusId");
				}
				if (jsonServer.has("serverStatus")) {
					serverItems.serverStatus = jsonServer.getString("serverStatus");
				}
				if (jsonServer.has("hostUrl")) {
					serverItems.hostUrl = jsonServer.getString("hostUrl");
				}
				if (jsonServer.has("chatServerUrl")) {
					serverItems.chatServerUrl = jsonServer.getString("chatServerUrl");
				}
				getInstance().servers.add(serverItems);
			}
//			instance.servers = servers;
		}
	}
	
	public static String getServerItems() {
//		System.out.println("我来了行不行啊");
		if (instance == null) {
			return "{}";
		}
		if (serverInfoStr == null) {
			StringBuilder buff = new StringBuilder();
			buff.append("[");

			for (int i = 0; i < getInstance().servers.size(); i++) {
				buff.append("{\"serverId\":")
						.append(instance.servers.get(i).serverId)
						.append(",\"serverStatusId\":")
						.append(instance.servers.get(i).serverStatusId)
						.append(",\"serverName\":\"")
						.append(instance.servers.get(i).serverName)
						.append("\",\"serverStatus\":\"")
						.append(instance.servers.get(i).serverStatus)
						.append("\",\"hostUrl\":\"")
						.append(instance.servers.get(i).hostUrl)
						.append("\",\"chatServerUrl\":\"")
						.append(instance.servers.get(i).chatServerUrl)
						.append("\"}");
				if (i < instance.servers.size() - 1) {
					buff.append(",");
				}
			}
			buff.append("]");
			serverInfoStr = buff.toString();
		}
		System.out.println("服务器选择列表是："+serverInfoStr);
		return serverInfoStr;
	}
	
	public class UpdateCotent {
		public boolean needUpdate;
		public boolean mustUpdate;
		public int lastestVersion;
		public String latestApkUrl;
		public String instrunciton;
	}
	public class AndroidCrackers {
		public String packageName;
		public String name;
	}
	public class ServerItems {
		public int serverId;
		public String serverName;
		public int serverStatusId;
		public String serverStatus;
		public String hostUrl;
		public String chatServerUrl;
	}
}
