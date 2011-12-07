#ifndef LOG_H
#define LOG_H

#define LOGV(fmt, args...) fprintf(stderr, "VORBOSE : "fmt" \n", ##args)
#define LOGW(fmt, args...) fprintf(stderr, "WARNING : "fmt" \n", ##args)
#define LOGD(fmt, args...) fprintf(stderr, "DEBUG : "fmt" \n", ##args)
#define LOGE(fmt, args...) fprintf(stderr, "ERROR : "fmt" \n", ##args)
#define LOGI(fmt, args...) fprintf(stderr, "INFO : "fmt" \n", ##args)

#endif //LOG_H
