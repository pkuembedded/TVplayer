#ifdef ANDROID
#include <stdio.h>
#include <math.h>
#include <jni.h>
#include <locale.h>
#include "structures.h"
#include "video.h"
#include "audio.h"
#include "sync.h"
#include "event.h"
#include "config.h"

char* video_info[MAX_NAME_LEN];

int main2(JNIEnv* env, jclass cls, jobject obj)
{
    SDL_Surface *screen;
    SDL_Event *event = av_mallocz(sizeof(SDL_Event));;
    Content *content = av_mallocz(sizeof(Content));
    Media *video = av_mallocz(sizeof(Media));
    Media *audio = av_mallocz(sizeof(Media));
    State *state = av_mallocz(sizeof(State));
    SDL_Thread *video_decode_tid;
    SDL_Thread *read_pkt_tid;
    state->content = content;
    state->video = video;
    state->audio = audio;
    init_video(video);
    av_register_all();
    av_strlcpy(content->name, "/mnt/sdcard/avs/720p.ts", sizeof(content->name));
    get_content_info(content);
    LOGI("finding streams");
    find_av_streams(content, video, audio);
    LOGI("finding decoder");
    find_decoder(video);
    video->get_info(video);
    strcpy(video_info, video->info);
    LOGI("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    LOGI("initing screen");
    init_screen(video);
//    LOGI("alloc the frame");
//    alloc_all_frame(video);
    alloc_frame(video);
    LOGI("creating decode thread...");
    video_decode_tid = SDL_CreateThread(decode_video, "decode", video);
    LOGI("start refreshing");
    refresh(state, 50);    
    event_handle(event);
    return 0;
}

/*
char* jstringTostr(JNIEnv* env, jstring jstr)
{
    char* pStr = NULL;
    jclass     jstrObj   = (*env)->FindClass(env, "java/lang/String");
    jstring    encode    = (*env)->NewStringUTF(env, "utf-8");
    jmethodID  methodId  = (*env)->GetMethodID(env, jstrObj, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray byteArray = (jbyteArray)(*env)->CallObjectMethod(env, jstr, methodId, encode);
    jsize      strLen    = (*env)->GetArrayLength(env, byteArray);
    jbyte      *jBuf     = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);

    if (jBuf > 0)
    {
        pStr = (char*)malloc(strLen + 1);
        if (!pStr)
        {
            return NULL;
        }
        memcpy(pStr, jBuf, strLen);
        pStr[strLen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, byteArray, jBuf, 0);
    return pStr;
}
*/

char* w2m(const wchar_t* wcs)
{
    int len;
    char* buf;
    len =wcstombs(NULL,wcs,0);
    if (len == 0)
	return NULL;
    buf = (char *)malloc(sizeof(char)*(len+1));
    memset(buf, 0, sizeof(char) *(len+1));
    len = wcstombs(buf, wcs, len+1);
    return buf;
}


void Java_com_player_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj, jstring path){
    LOGE("Native Init started");
    char* w_buf;//jbyte is unsigned char !!
    char* file_path;
    w_buf = (*env)->GetStringUTFChars(env, path, NULL);
    if(w_buf == NULL) {
	LOGE("file path recv nothing");
    }
    setlocale(LC_ALL,".936");
    file_path = w2m(w_buf);
    LOGE("file path convert : %s", file_path);
    (*env)->ReleaseStringUTFChars(env, path, w_buf);
    SDL_Android_Init(env, cls);
    int status;
    char *argv[2];
    argv[0] = strdup("SDL_app");
    argv[1] = NULL;
    status = main2(env, cls, obj);
    exit(status);
}

void Java_com_player_SDLActivity_nativeQuit(JNIEnv* env, jclass cls){
    Java_org_libsdl_app_SDLActivity_nativeQuit(env, cls);
}

void Java_com_player_SDLActivity_onNativeResize(JNIEnv* env, jclass cls, jobject obj, jint x, jint y, jint format){
    Java_org_libsdl_app_SDLActivity_onNativeResize(env, cls, obj, x, y, format);
}


void Java_com_player_SDLActivity_onNativeAccel(JNIEnv* env, jclass cls, jobject obj, jfloat x, jfloat y, jfloat z){
    Java_org_libsdl_app_SDLActivity_onNativeAccel(env, cls, obj, x, y, z);
}


void Java_com_player_SDLActivity_onNativeKeyDown(JNIEnv* env, jclass cls, jint keycode){
    Java_org_libsdl_app_SDLActivity_onNativeKeyDown(env,cls,keycode);
}

void Java_com_player_SDLActivity_onNativeKeyUp(JNIEnv* env, jclass cls, jint keycode){
    Java_org_libsdl_app_SDLActivity_onNativeKeyUp(env,cls,keycode);
}

void Java_com_player_SDLActivity_onNativeTouch(JNIEnv* env, jclass cls,jint touch_device_id_in, jint pointer_finger_id_in, jint action, jfloat x, jfloat y, jfloat p){
    Java_org_libsdl_app_SDLActivity_onNativeTouch(env,cls,touch_device_id_in, pointer_finger_id_in, action, x, y, p);
}

void Java_com_player_SDLActivity_nativeRunAudioThread(JNIEnv* env, jclass cls){
    Java_org_libsdl_app_SDLActivity_nativeRunAudioThread(env,cls);
}
jstring Java_com_player_SDLActivity_onNativeGetInfo(JNIEnv* env, jobject obj){
    jstring result = (*env)->NewStringUTF(env, video_info);
}
void Java_com_player_SDLActivity_nativePause(JNIEnv* env, jobject obj){
    pause();
    LOGE("PAUSE : %d", stop_flag);
}
#endif ANDROID
