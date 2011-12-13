#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "video.h"
#include "audio.h"
#include "sync.h"
#include "event.h"
#include "config.h"

int main(int argc, char **argv)
{
    SDL_Event event;
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
    if(argc < 2) {
	LOGE("Usage : play <content>");
	exit(1);
    }
    av_register_all();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
	LOGE("fail to initialize SDL");
	exit(1);
    }
    av_strlcpy(content->name, argv[1], sizeof(content->name));
    get_content_info(content);
    LOGI("finding streams");
    find_av_streams(content, video, audio);
    LOGI("finding decoder");
    find_decoder(video);
    video->get_info(video);

    LOGI("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    LOGI("creating decode thread...");
    video_decode_tid = SDL_CreateThread(decode_video, "decode", video);
    LOGI("initing screen");
    init_screen(video);
    LOGI("schedule refreshing");
    schedule_refresh(state, 100);
    av_init_packet(&flush_pkt);
    flush_pkt.data = "FLUSH";
    while(true) {
	event_handle();
    }
    return 0;
}

#ifdef ANDROID_TEST
void Java_com_player_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj, jstring arg){
    /* This interface could expand with ABI negotiation, calbacks, etc. */
    const char *file_path = (*env)->GetStringUTFChars(env, arg, 0);
    LOGE("file path recv : %s", file_path);
    SDL_Android_Init(env, cls);
    /* Run the application code! */
    int status;
    char *argv[2];
    argv[0] = strdup("SDL_app");
    argv[1] = NULL;
    status = main2(env, cls, obj, arg);
    /* We exit here for consistency with other platforms. */
    exit(status);

//	Java_org_libsdl_app_SDLActivity_nativeInit(env, cls, obj);
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
#endif //ANDROID_TEST
