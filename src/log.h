#ifndef LOG_H
#define LOG_H

#define LOG_FILE "log.txt"
#define LOGV(error) fprintf(fp, "%s\n", error);
#define LOGW(error) fprintf(stderr, "%s\n", error);
#define LOGD()
#define LOGE()
#define LOGI()


#endif //LOG_H
