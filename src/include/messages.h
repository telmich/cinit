/*
 * (c) 2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * All messages
 */

#ifndef _CINIT_MSG_H
#define _CINIT_MSG_H

/* version */
#define CINIT_VERSION      "cinit-" VERSION
#define MSG_BOOTING        CINIT_VERSION ": Booting from "

#define MSG_DP    ": "

/* Messages to the outside */
#define MSG_BIND           "bind"
#define MSG_CONNECT        "connect"
#define MSG_FCNTL          "fcntl"
#define MSG_KILLBILL       "sigkill"
#define MSG_LISTEN         "listen"
#define MSG_SOCKET         "socket"
#define MSG_TERMKILL       "sigterm"
#define MSG_USAGE_1        ": fast executing, small and simple init "
#define MSG_USAGE_2        "with support for profiles\n"
#define MSG_USAGE_3        "\nError: cinit must be started as PID 1.\n"
#define MSG_USAGE          MSG_USAGE_1 MSG_USAGE_2 MSG_USAGE_3
#define MSG_ERR_FORK       "fork"
#define MSG_ERR_IO         "i/o"
#define MSG_ERR_OPEN       "open"
#define MSG_ERR_PIPE       "pipe"
#define MSG_ERR_READ       "read"
#define MSG_ERR_EXECVE     "execve"
#define MSG_ERR_ALLOC      "memory allocation"
#define MSG_ERR_UMOUNT     "umount"
#define MSG_ERR_MOUNT      "mount"
#define MSG_NOT_DIR        "not a directory"
#define MSG_CHDIR          "chdir"
#define MSG_READLINK       "readlink"
#define MSG_ERR_ADD_SVC    "Adding service failed"
#define MSG_CMD_UNKNOWN    "Unknown command"

#define MSG_ERR_DEPS       "Too many dependencies"
#define MSG_ERR_ACCEPT     "accept"
#define MSG_ERR_WAITPID    "waitpid"
#define MSG_ERR_POLL       "poll"
#define MSG_ERR_MODIFY     "modify list failed"
#define MSG_ERR_COMM       "Communication failed"

#define MSG_ERR_LESS_ARGS  "Too less arguments!"
#define MSG_ERR_BAD_ARGS   "Wrong arguments / parameter"
#define MSG_ERR_ARGS_LEN   "Wrong parameter length"

#define LOG_SVC_STOPED     "Service stoped"
#define LOG_SVC_ONCE       "Started once"
#define LOG_SVC_RESPAWN    "Respawns now"
#define LOG_NEED_FAIL      "One or more need failed"
#define LOG_SVC_FAILED     "Service already failed, not starting."
#define LOG_SVC_NOTEXIST   "Service does not exist"

#define MSG_EXEC_FAILED    "Failed to execute "

#define MSG_RESCUE         "Switching to rescue mode ..."
#define MSG_UPDATE         "Updating cinit ..."
#define MSG_HOT_REBOOT     "Hot reboot in progress ..."

#define MSG_SHOULD_NOT_HAPPEN "This should not happen, I do not know what todo!"

/* DEBUG */
#ifdef DEBUG
# define D_PRINTF(x)  ( printf("[%s:%d]: %s\n",__FILE__,__LINE__,x) )
#else 
# define D_PRINTF(x)  if(0)
#endif

/* macros */
#define SERVICE_LOG(svc,message) {  \
   mini_printf(svc,1);              \
   mini_printf(MSG_DP,1);           \
   mini_printf(message,1);          \
   mini_printf("\n",1);             \
}
#define LOG(s) {                    \
   mini_printf(s,1);                \
   mini_printf("\n",1);             \
}
#define P_START_SERVICE(name) { mini_printf(MSG_START_SVC,1); mini_printf(name,1); mini_printf("\n",1); }
#define P_EXEC_FAILED(name) { mini_printf(MSG_EXEC_FAILED,1); mini_printf(name,1); mini_printf("\n",1); }

/* NEW (clean) Service status: Messages to the outside */

/* services: how they should be printed
 * /etc/cinit/svc/long/name: started once
 * /etc/cinit/svc/long/name: is respawning
 * /etc/cinit/svc/long/name: FAILED (why it happened)
 */

#define MSG_INTRO_CINIT    "ct/"
#define MSG_INTRO_SVC      MSG_INTRO_CINIT   "service:"
#define MSG_INTRO_STOP     MSG_INTRO_CINIT   "stop: "

/* FIXME: remove/append, but no intro! */
#define MSG_INTRO_FAIL     "FAILED "
#define MSG_INTRO_RESPAWN  MSG_INTRO_CINIT   "respawn: "
#define MSG_INTRO_OK       MSG_INTRO_CINIT   "ok:  "

#define MSG_SVC_FORK       "fork() failed"
#define MSG_SVC_NEED_FAIL  MSG_INTRO_FAIL "Needs failed for service"
#define MSG_SVC_FAIL       MSG_INTRO_FAIL "Service failed!"



#define MSG_TREE_EXEC      MSG_INTRO_CINIT "Execution of reverse service tree\n"

/* general errors */
#define MSG_GETCWD         "Getcwd failed! Your system is most likely broken!"
#define MSG_GEN_SLEEP      "sleep"
#define MSG_FATAL_PANIC    MSG_INTRO_CINIT "I tried everything, but even panic() failed: "

/* Service messages */
#define MSG_SVC_START      "Starting... "
#define MSG_SVC_STOP       "Stoping... "
#define MSG_SVC_RESTART    "Restarted."
#define MSG_SVC_OK_ONCE    "Started once."
#define MSG_SVC_OK_RESPAWN "Is respawning."

/* Status messages */
#define MSG_SHUTDOWN_START    MSG_INTRO_STOP    "Beginning the shutdown process..."
#define MSG_SHUTDOWN_SVC      MSG_INTRO_STOP    "Shutting down services now..."
#define MSG_SHUTDOWN_KILL     MSG_INTRO_STOP    "Killing remaining processes..."
#define MSG_SHUTDOWN_LAST     MSG_INTRO_STOP    "Executing final service..."
#define MSG_POWER_OFF         MSG_INTRO_STOP    "Powering off..."
#define MSG_HALT              MSG_INTRO_STOP    "Halting system ..."
#define MSG_REBOOT            MSG_INTRO_STOP    "Rebooting ..."

#endif   /* _CINIT_MSG_H */
