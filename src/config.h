#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "../include/toml.h"

typedef struct {
    int enabled;
    int is_scheduled;
    int is_safe;
    const char* level;
    const char* crontab;
} Gremlin;

typedef struct {
    const char* host;
    const char* name;
    const char* user;
    const char* password;
    const char* level;
} Database;

typedef struct {
    const char* ip;
    const char* user;
    const char* password;
    const char* level;
    int docker;
} Machine;

typedef struct {
    Gremlin gremlin;
    Database database;
    Machine machine;
} Main;

Main* read_config();

#endif