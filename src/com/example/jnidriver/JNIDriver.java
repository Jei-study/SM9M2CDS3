package com.example.jnidriver;

public class JNIDriver {

	private boolean mConnectFlag;
	
	static {
		System.loadLibrary("JNIDriver");
	}
	
	private native static int openDriver(String path1, String path2, String path3);
	private native static void closeDriver();
	private native static void writeDriver(byte[] data, int length);
	private native void setPiz(char data);
	private native static void segWrite(byte[] data, int length);
	
	public JNIDriver() {
		mConnectFlag = false;
	}
	
	public int open(String led_driver, String piz_driver, String seg_driver){
		if(mConnectFlag) return -1;
		
		if(openDriver(led_driver, piz_driver, seg_driver)>0){
			mConnectFlag = true;
			return 1;
		} else {
			return -1;
		}
	}
	
	public void close(){
		if(!mConnectFlag) return;
		mConnectFlag = false;
		closeDriver();
	}
	
	protected void finalize() throws Throwable{
		close();
		super.finalize();
	}
	
	public void led_write(byte[] data){
		if(!mConnectFlag) return;
		
		writeDriver(data, data.length);
	}
	
	public void setPiz(int value){
		if(!mConnectFlag){
			return;
		}
		if(value < 1){
			value = 1;
		} else if (value > 22){
			value = 22;
		}
		
		setPiz((char)value);
	}
	
	public void seg_write(byte[] data){
if(!mConnectFlag) return;
		segWrite(data, data.length);
	}
}
