#ifndef _LOG_H_
#define _LOG_H_

#define taidaLogError(msg) taidaLog(TLOGP_ERROR, msg)
#define taidaLogWarn(msg) taidaLog(TLOGP_WARN, msg)
#define taidaLogDebug(msg) taidaLog(TLOGP_DEBUG, msg)
#define taidaLogInfo(msg) taidaLog(TLOGP_INFO, msg)

/* log priorities */
enum taidaPriority {
	TLOGP_ERROR,
	TLOGP_WARN,
	TLOGP_DEBUG,
	TLOGP_INFO,
	TLOGP_GLFW_ERROR,
};

/* taidaLog
 *
 * 	Output a log message according to specific priority
 *
 * @priority: prioriry level
 * @msg: message 
 */
void taidaLog(const int priority, const char *msg);

/* GLFW Error Callback */
void taidaGLFWError(int code, const char *msg);
#endif /* _LOG_H_ */
