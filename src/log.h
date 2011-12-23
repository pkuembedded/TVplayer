
#ifndef LOG_H
#define LOG_H

#ifdef ANDROID
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "TVplayer", __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , "TVplayer", __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO , "TVplayer", __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN , "TVplayer", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , "TVplayer", __VA_ARGS__)
#else
#define LOGV(fmt, args...) printf("VORBOSE : "fmt" \n", ##args)
#define LOGW(fmt, args...) printf("WARNING : "fmt" \n", ##args)
#define LOGD(fmt, args...) printf("DEBUG : "fmt" \n", ##args)
#define LOGE(fmt, args...) printf("ERROR : "fmt" \n", ##args)
#define LOGI(fmt, args...) printf("INFO : "fmt" \n", ##args)
#endif //ANDROID

#endif //LOG_H
