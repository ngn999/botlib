#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "botlib.h"

/* For each bot command, private message or group message (but this only works
 * if the bot is set as group admin), this function is called in a new thread,
 * with its private state, sqlite database handle and so forth.
 *
 * For group messages, this function is ONLY called if one of the patterns
 * specified as "triggers" in startBot() matched the message. Otherwise we
 * would spawn threads too often :) */
void handleRequest(sqlite3 *dbhandle, BotRequest *br) {
    UNUSED(dbhandle);
    sds empty = sdsempty();
    if ((br->type == TB_TYPE_GROUP || br->type == TB_TYPE_SUPERGROUP) && sdscmp(br->request, empty)) {
        botDeleteMessage(br->target, br->msg_id);
    }
    sdsfree(empty);
}

// This is just called every 1 or 2 seconds.
void cron(sqlite3 *dbhandle) {
    UNUSED(dbhandle);
    printf("."); fflush(stdout);
}

int main(int argc, char **argv) {
    static char *triggers[] = {
        "*weibo.com*",
        "*.qq.com*",
        "*xhslink.com*",
        NULL,
    };
    startBot(TB_CREATE_KV_STORE, argc, argv, TB_FLAGS_NONE, handleRequest, cron, triggers);
    return 0; /* Never reached. */
}
