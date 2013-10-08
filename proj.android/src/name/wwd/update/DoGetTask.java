package name.wwd.update;

import java.util.Map;

import android.os.AsyncTask;

public class DoGetTask extends AsyncTask<Void, Void, Object[]> {

	private String uri;
	private Map<String, String> httpParams;
	
	public DoGetTask(String uri, Map<String, String> httpParams) {
		this.uri = uri;
		this.httpParams = httpParams;
	}
	@Override
	protected Object[] doInBackground(Void... params) {
		return HTTP.GET(uri, httpParams);
	}

}
