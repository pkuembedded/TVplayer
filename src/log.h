
#ifndef LOG_H
#define LOG_H

//#ifdef ANDROID_TEST
//#include <android/log.h>
//#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "TVplayer", __VA_ARGS__)
//#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , "TVplayer", __VA_ARGS__)
//#define LOGI(...) __android_log_print(ANDROID_LOG_INFO , "TVplayer", __VA_ARGS__)
//#define LOGW(...) __android_log_print(ANDROID_LOG_WARN , "TVplayer", __VA_ARGS__)
//#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , "TVplayer", __VA_ARGS__)
//#else
#define LOGV(fmt, args...) fprintf(stderr, "VORBOSE : "fmt" \n", ##args)
#define LOGW(fmt, args...) fprintf(stderr, "WARNING : "fmt" \n", ##args)
#define LOGD(fmt, args...) fprintf(stderr, "DEBUG : "fmt" \n", ##args)
#define LOGE(fmt, args...) fprintf(stderr, "ERROR : "fmt" \n", ##args)
#define LOGI(fmt, args...) fprintf(stderr, "INFO : "fmt" \n", ##args)
//#endif //ANDROID_TEST

#endif //LOG_H
