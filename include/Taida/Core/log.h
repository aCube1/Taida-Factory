#ifndef _LOG_H_
#define _LOG_H_

#define taidaLogError(msg) taidaLog(TAIDA_LOGP_ERROR, msg)
#define taidaLogWarn(msg) taidaLog(TAIDA_LOGP_WARN, msg)
#define taidaLogDebug(msg) taidaLog(TAIDA_LOGP_DEBUG, msg)
#define taidaLogInfo(msg) taidaLog(TAIDA_LOGP_INFO, msg)

/* log priorities */
enum {
	TAIDA_LOGP_ERROR,
	TAIDA_LOGP_WARN,
	TAIDA_LOGP_DEBUG,
	TAIDA_LOGP_INFO,
	TAIDA_LOGP_GLFW_ERROR,
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
