#ifndef CONFIG_H
#define CONFIG_H

#include "../include/toml.h"

typedef struct {
    Goblin goblin;
    Database database;
    Machine machine;
} Main;

typedef struct {
    int enabled;
    int is_scheduled;
    int is_safe;
    const char* level;
    const char* crontab;
} Goblin;

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
    int docker;
    const char* level;
} Machine;

#endif