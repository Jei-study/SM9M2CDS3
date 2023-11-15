#include <jni.h>
#include <fcntl.h>

int led_fd = 0;
int piz_fd = 0;
int seg_fd = 0;

JNIEXPORT jint JNICALL Java_com_example_jnidriver_JNIDriver_openDriver(JNIEnv * env, jclass class, jstring path1, jstring path2, jstring path3){
	jboolean iscopy;
	const char *path_utf1 = (*env)->GetStringUTFChars(env, path1, &iscopy);
	const char *path_utf2 = (*env)->GetStringUTFChars(env, path2, &iscopy);
	const char *path_utf3 = (*env)->GetStringUTFChars(env, path3, &iscopy);

	led_fd = open(path_utf1, O_WRONLY);
	piz_fd = open(path_utf2, O_WRONLY);
	seg_fd = open(path_utf3, O_WRONLY);

	(*env)->ReleaseStringUTFChars(env, path1, path_utf1);
	(*env)->ReleaseStringUTFChars(env, path2, path_utf2);
	(*env)->ReleaseStringUTFChars(env, path3, path_utf3);

	if(led_fd<0 || piz_fd<0 || seg_fd<0) return -1;
	else return 1;
}

JNIEXPORT void JNICALL Java_com_example_jnidriver_JNIDriver_closeDriver(JNIEnv * env, jobject obj){
	if(led_fd>0 && piz_fd>0 && seg_fd>0){
		close(led_fd);
		close(piz_fd);
		close(seg_fd);
	}
}

JNIEXPORT void JNICALL Java_com_example_jnidriver_JNIDriver_writeDriver(JNIEnv * env, jobject obj, jbyteArray arr, jint count){
	jbyte* chars = (*env)->GetByteArrayElements(env, arr, 0);
	if(led_fd>0) write(led_fd, (unsigned char*)chars, count);
	(*env)->ReleaseByteArrayElements(env, arr, chars, 0);
}

JNIEXPORT void JNICALL Java_com_example_jnidriver_JNIDriver_setPiz(JNIEnv * env, jobject obj, jchar c){
	int i = (int) c;
	if(piz_fd>0) write(piz_fd, &i, sizeof(i));
}

JNIEXPORT void JNICALL Java_com_example_jnidriver_JNIDriver_segWrite(JNIEnv * env, jobject obj, jbyteArray arr, jint count){
	jbyte* chars = (*env)->GetByteArrayElements(env, arr, 0);
	if(seg_fd>0) write(seg_fd, (unsigned char*)chars, count);
	(*env)->ReleaseByteArrayElements(env, arr, chars, 0);
}
